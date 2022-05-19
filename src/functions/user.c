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
    SOFTWARE.

    @version:0.0.1
    @date:2022/5/13
    @author:haruluya
    @model_function:"用户表操作函数".
    @include:user.h    
    @log:user.log     
    @functions:{
        yuffieSplit:"自定义的字符串切分函数(以空格)",
        initUserList:"载入用户表" ,
        setPresentUser:"设置当前用户",
        loginValidate:"登录验证"
    }
*/
#pragma once
#include"user.h"
#pragma warning(disable : 4996)


/*
    @author:haruluya
    @date:2022/5/13
    @function:"自定义的字符串切分函数(以空格)"
    @input:{
        buff:"缓存区".
    }
    @output:{
    }
    @execute:[loginDialog.loginDialogProc] 
    @return:"切分后的字符串数组"
*/
String* yuffieSplit(String buff) {
    String info = strtok(buff, " ");
    String* infoArray = (String*)malloc(sizeof(String) * INFO_MAXSIZE);
    int len = 0;
    while (info) {
        infoArray[len++] = info;
        info = strtok(NULL, " ");
    }
    return infoArray;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"载入用户数据"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status initUserList() {
    FILE* fp;

    /*
        @value:"文件打开错误处理".
    */
    if (!(fp = fopen("user.txt", "r"))) {
        return ERROR;
    }

    while (!feof(fp)) {
        fgets(BUFF, sizeof(BUFF), fp);
        if (!strcmp(BUFF, "\0")) {
            break;
        }
        String* userInfo = yuffieSplit(BUFF);

        //初始化user项.
        User user;
        user.userName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        user.password = (String)malloc(sizeof(char) * INFO_MAXSIZE);
        user.userName = strcpy(user.userName, userInfo[0]);
        user.password = strcpy(user.password, userInfo[1]);
        user.identity = atoi(userInfo[2]);
        user.id = atoi(userInfo[3]);

        //插入list。
        userList[userListLen++] = user;
        BUFF[0] = '\0';
    }
    fclose(fp);
    return OK;
}


/*
    @author:haruluya
    @date:2022/5/13
    @function:"设置当前用户"
    @input:{
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"执行状态"
*/
Status setPresentUser(String userName) {

    /*
        @check:"传入是否错误"。
    */
    if (!userName) {
        return INFASIBLE;
    }
    for (int i = 0; i < userListLen; i++) {

        /*
            @check:"usernam找到返回"。
        */
        if (strcmp(userList[i].userName, userName) == 0) {
            presentUser = userList[i];
            return OK;
        }
    }
    return NOT_FOUND;
}



/*
    @author:haruluya
    @date:2022/5/13
    @function:"登录验证"
    @input:{
        userName:"用户名"，
        password:"用户密码"
    }
    @output:{
    }
    @execute:[yuffie.WinMain]
    @return:"登录状态"
*/
LoginMessage loginValidate(String userName, String password) {
    LoginMessage message;

    /*
        @check:"username输入为空"。
    */
    if (!userName) {
        message.status = INFASIBLE; message.message = "Input error!";
        return message;
    }

    //用户不存在。
    message.status = NOT_FOUND; message.message = "User not found!";

    for (int i = 0; i < userListLen; i++) {

        /*
            @check:"用户存在"。
        */
        if (strcmp(userList[i].userName, userName) == 0) {

            /*
                @check:"用户密码正确"。
            */
            if (strcmp(userList[i].password, password) == 0) {
                message.status = OK; message.message = "Login success!";
            }
            else {
                message.status = ERROR; message.message = "Password wrong!";
            }
            break;
        }
    }
    return message;
}


String getIdentity(IDENTITY identity) {
    switch (identity)
    {
    case ADMIN:return "admin";
    case TEACHER:return "teacher";
    case SUPPLIER:return "supplier";
    default:
        return INFASIBLE;
    }
}



/*
    @author:haruluya
    @date:2022/5/13
    @function:"添加新用户"
    @input:{
        User:"用户结构体"
    }
    @output:{
    }
    @return:"添加状态"
*/
Status addUser(User u)
{
    //插入list。
    userList[userListLen++] = u;
    printUser();
    return OK;
}


Status printUser() {
    FILE* fp;

    /*
        @check:"文件打开错误处理."
    */
    if (!(fp = fopen("user.txt", "w")))
    {
        return ERROR;
    }

    for (int i = 0; i < userListLen; i++)
    {

        fprintf(fp,
            "%s %s %d %d\n",
            userList[i].userName,
            userList[i].password,
            userList[i].identity,
            userList[i].id);
    }
    fclose(fp);
    return OK;
}

/*
    @author:haruluya
    @date:2022/5/13
    @function:"删除指定用户新用户"
    @input:{
        id:"用户编号"
    }
    @output:{
    }
    @return:"删除状态"
*/
Status deleteUser(int id)
{
    for (int i = 0; i < userListLen; i++)
    {
        if (userList[i].id == id)
        {
            for (int j = userListLen - 1; j > i; j--)
            {
                userList[j - 1].userName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                userList[j - 1].password = (String)malloc(sizeof(char) * INFO_MAXSIZE);
                strcpy(userList[j - 1].userName, userList[i].userName);
                strcpy(userList[j - 1].password, userList[i].password);
                userList[j - 1].id = userList[i].id;
                userList[j - 1].identity = userList[i].identity;
            }
            userListLen--;
            userList[userListLen - 1];
        }
    }
    printUser();

    return OK;
}