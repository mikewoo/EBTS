#include "api/myapp.h"
#include <QSettings>
#include <QTextCodec>

QTextCodec *codec = QTextCodec::codecForName("utf-8");

//存储当前登录用户信息,方便用户密码修改和用户退出操作
QString myApp::CurrentUserName="admin";
QString myApp::CurrentUserPwd="admin";
QString myApp::CurrentUserType=codec->toUnicode("管理员");

//存储全局配置信息,程序启动时加载,关闭时保存
QString myApp::SoftTitle=codec->toUnicode("***软件缺陷检测系统");
QString myApp::SoftVersion="V2.0";
QString myApp::CompanyName=codec->toUnicode("****大学");
QString myApp::ContactName=codec->toUnicode("张三");
QString myApp::ContactTel="13800000000";
QString myApp::LastLoginer="admin";
