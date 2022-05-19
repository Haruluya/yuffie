
/*
    @license:
    MIT License

    Copyright (c) 2022 Haruluya

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.   //MIT证书声明，为固定部分。

    @version:0.0.1
    @date:2022/5/13
    @author:haruluya
    @model_function:"对用户表相关操作函数和全局变量。".
    @include:global.h    
    @work:[user.c,yuffie.h]       
    @log:user.log     

*/

#pragma once
#include"global.h"

/*
    @value:user表每列最大长度。
*/
#define INFO_MAXSIZE 50

/*
    @value:"user表最大元组数。"
*/
#define USER_LIST_MAX_SIZE 199
#pragma warning(disable : 4996)


/*
    @function:"登录状态的封装。"
    @value:{
        Status:"登录状态.",
        String:"登录消息"
    }
*/
typedef struct LoginMessage {
    Status status;
    String message;
}LoginMessage;


/*
    @function:"用户身份枚举。"
    @value:{
        ADMIN:"管理员"，
        SUPPLIER:"供应商",
        TEACHER:"老师",
        NONE:"未登录"
    }
*/
typedef enum IDENTITY
{
    ADMIN,
    SUPPLIER,
    TEACHER,
    NONE,
}IDENTITY;

/*
    @function:"用户实体。"
    @value:{
        userName:"用户名称",
        password:"用户密码",
        identity:"用户身份",
        id:"当前身份id"
    }
*/
typedef struct User {
    String userName;
    String password;
    IDENTITY identity;
    int    id;
}User;



/*
    @function:"全局储存的所有用户数据，避免多次读取文件。"
    @range:[0,USER_LIST_MAX_SIZE]
*/
User userList[USER_LIST_MAX_SIZE];

/*
    @function:"用户数据长度。"
    @range:[0,USER_LIST_MAX_SIZE]
*/
int userListLen;

/*
    @function:"当前用户。"
    @range:[NULL|user]
*/
User presentUser;

/*
    @function:"登录验证。"
*/
LoginMessage loginValidate(String,String);

/*
    @function:"设置当前用户。"
*/
Status setPresentUser(String userName);


/*
    @function:"载入user数据。"
*/
Status initUserList();


/*
    @function:"自定义的split函数。"
*/
String* yuffieSplit(String);

/*
    @function:"获取身份信息。"
*/
String getIdentity(IDENTITY);


/*
    @function:"添加新用户。"
*/
Status addUser(User);

/*
    @function:"删除指定用户。"
*/
Status deleteUser(int);

Status printUser();