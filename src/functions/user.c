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

