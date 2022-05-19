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
    @model_function:"登录界面窗口".
    @include:[globalConst.h，user.h]    
    @work:loginDialog.c       
    @log:loginDialog.log     

*/

#include"globalConst.h"
#include"user.h"


/*
    @function:"定义String类."
    @value:{
    }
*/
typedef char* String;

/*
    @value:"账号输入edit组件id。"
*/
#define ID_YUFFIE_USERNAME_EDIT 500

/*
    @value:"密码输入edit组件id。"
*/
#define ID_YUFFIE_PASSWORD_EDIT 501

/*
    @value:"账号输入label组件id。"
*/
#define ID_YUFFIE_USERNAME_LAB 502

/*
    @value:"密码输入label组件id。"
*/
#define ID_YUFFIE_PASSWORD_LAB 503



/*
    @function:"窗口过程。"
*/
BOOL CALLBACK loginDlgProc(HWND, UINT,WPARAM, LPARAM);

/*
    @function:"账号输入验证"
*/
BOOL validateUserName(String);

/*
    @function:"密码输入label组件id。"
*/
BOOL validatePassword(String);


/*
    @function:"登录验证。"
*/
LoginMessage validateUser(String, String);
