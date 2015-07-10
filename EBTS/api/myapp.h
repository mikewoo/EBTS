#ifndef MYAPP_H
#define MYAPP_H

#include <QString>

class myApp
{
public:
    static QString AppPath;             //应用程序路径

    static bool IsMove;                 //图片是否可以移动
    static int DeskWidth;               //桌面宽度
    static int DeskHeigth;              //桌面高度

    static QString CurrentUserName;     //当前用户名
    static QString CurrentUserPwd;      //当前用户密码
    static QString CurrentUserType;     //当前用户类型（值班员、管理员）

    static QString SoftTitle ;          //软件标题
    static QString SoftVersion;         //软件版本
    static QString CompanyName;         //开发商名称
    static QString ContactName;         //联系人
    static QString ContactTel;          //联系电话
    static QString LastLoginer;         //最后一次登录用户名,用来自动登录时需要加载的用户信息
};

#endif // MYAPP_H
