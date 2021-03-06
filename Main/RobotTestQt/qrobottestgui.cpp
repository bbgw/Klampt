#include "qrobottestgui.h"

#include <QSettings>
#include <QtGui/QApplication>

QRobotTestGUI::QRobotTestGUI(GenericBackendBase *_backend,QKlamptDisplay* _display) :
  QtGUIBase(_backend),display(_display),
    col_out(new CollisionOutput)

{
  const char* rules = "[ \
[{type:key_down,key:c}, {type:command,cmd:constrain_current_link,args:\"\"}],	\
[{type:key_down,key:d}, {type:command,cmd:delete_current_constraint,args:\"\"}], \
[{type:key_down,key:p}, {type:command,cmd:print_pose,args:\"\"}],	\
[{type:button_press,button:print_config}, {type:command,cmd:print_pose,args:_0}], \
[{type:widget_value,widget:link,value:_0}, {type:command,cmd:set_link,args:_0}], \
[{type:widget_value,widget:link_value,value:_0}, {type:command,cmd:set_link_value,args:_0}], \
[{type:widget_value,widget:driver,value:_0}, {type:command,cmd:set_driver,args:_0}], \
[{type:widget_value,widget:driver_value,value:_0}, {type:command,cmd:set_driver_value,args:_0}] \
]";
  stringstream ss(rules);
  bool res=LoadRules(ss);
  assert(res==true);
  driver_index=0;
  link_index=0;
}

QRobotTestGUI::~QRobotTestGUI()
{
  delete col_out;
}

void QRobotTestGUI::SetDriver(int index){
    driver_index=index;
    SendCommand("set_driver",index);
    emit UpdateDriverValue();
    emit UpdateDriverParameters();
}

void QRobotTestGUI::SetDriverValue(double val){
    SendCommand("set_driver",driver_index);
    SendCommand("set_driver_value",val);

  connect(&idle_timer, SIGNAL(timeout()),this,SLOT(OnIdleTimer()));
  idle_timer.start(0);
}


void QRobotTestGUI::OnIdleTimer()
{
  SendIdle();
}

bool QRobotTestGUI::OnPauseIdle(double secs) 
{
  if(secs > 10000000)
    idle_timer.stop();
  else
    idle_timer.start(int(secs*1000));
  return true;
}


void QRobotTestGUI::SetLink(int index){
    link_index=index;
    SendCommand("set_link",index);
    emit UpdateLinkValue();
    emit UpdateLinkParameters();
}

void QRobotTestGUI::SetLinkValue(double val){
    SendCommand("set_link",link_index);
    SendCommand("set_link_value",val);
}

bool QRobotTestGUI::OnRefresh()
{
  display->updateGL();
  return true;
}

bool QRobotTestGUI::OnCommand(const string &cmd, const string &args){
  if(cmd=="update_config"){
        UpdateGUI();
        return true;
    }
    else if(cmd=="return_self_collisions"){
        string str=&(args[0]);
        col_out->SetText(QString::fromStdString(str));
        col_out->show();
		return true;
    }
    else return QtGUIBase::OnCommand(cmd,args);
}

void QRobotTestGUI::UpdateGUI(){

    emit UpdateLinkValue();
    emit UpdateLinkParameters();
    emit UpdateDriverValue();
    emit UpdateDriverParameters();
}

void QRobotTestGUI::LoadFile(QString filename){
  QSettings ini(QSettings::IniFormat, QSettings::UserScope,
		QCoreApplication::organizationName(),
		QCoreApplication::applicationName());
  if(filename.isEmpty()){
    QString openDir = ini.value("last_open_resource_directory",".").toString();
    QFileDialog f;
    filename = f.getOpenFileName(0,"Open File",openDir,"");
    if(!filename.isEmpty())
      ini.setValue("last_open_resource_directory",f.directory().absolutePath());
    }
  if(!filename.isEmpty())
    SendCommand("load_file",filename.toStdString());
}
