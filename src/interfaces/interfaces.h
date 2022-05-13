/*
①命名规范：驼峰式：
            变量：struct List   int studentStack[]
            布尔：isBigger
            常量：YUFFIE_MAX_INT   YUFFIE_ARRAY_LENGTH  //宏定义避免与win32 api重合以YUFFIE开头。 
            函数：addItemToList()  
            头文件：student.h   

*/

/*
②.h头文件接口规范。
*/
// #include"a.h";
// #include"b.h";
// #include"c.h";

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
    @date:2022/5/9
    @author:haruluya
    @model_function:"This is a file for test".  
    @include:[a.h,b.h,c.h]    //包含的头文件。
    @work:interface.c       //包含此头文件的源程序。
    @log:interfaces.log     //更新日志。

*/


/*
③函数接口规范。
*/
typedef int Student;
/*
    @author:haruluya
    @date:2022/5/9
    @function:"For test"
    @input:{
        a:"A student id",
        b:"A student"
    }
    @output:{
        c:"The ptr will be delete" //输出参数，即函数内改变的引用或引用的值。
    }
    @execute:[interfaces.a,interfaces.b,interfaces.main] //调用关系,调用此函数的函数[file_name][function)name]。
    @return:none
*/
void test(int a,Student b){

}

/*
    @function:"For test"
*/
void test(int,Student);


/*
④源程序接口规范。
interfaces.c
*/

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
    @date:2022/5/9
    @author:haruluya
    @model_function:"This is a file for test".  
    @include:a.h,b.h,c.h    //包含的头文件。
    @log:interfaces.log     //更新日志。
    @functions:{
        testa:"This is a function for test.",
        testb:"This is a function for test." //源程序函数功能声明。
    }
*/

/*
⑤数据结构接口规范。
*/

/*
    @function:"Abstraction of student."
    @value:{
        name:"Student's name.",
        id:"Student's id"
    }
*/
typedef struct Student{
    char* name;
    int id;
}Student;



/*
⑥全局变量接口规范。
*/

/*
    @function:"Value for test."
    @range:[-1,infinite]
*/
int value;


/*
⑦变量定义（属性注释）接口规范。
*/
typedef int boolean;

/*
    @value:"if input is over."
*/
boolean isInputOver;

/*
    @value:"A temp value of student for test."
*/
Student studentTempForTest;


/*
⑧分支语句接口规范。（语句注释使用//）
*/


//  @Check:"If a is greater than b then a is equal to b otherwise a doesn't change. "
if (a > b){
    a = b;
}


//  @Check:"If a is equal to 1, then... equal to 2, then..., otherwise..."
switch (a){
    case 1:
        break;
    //  @no_break   //没有break的必须标注。
    case 2:
    case 3:
        break;
    default:
        break;
}


/*
⑨断言接口规范。
*/

// @Check:"Check whether ex is 0."
assert(ex);


/*
⑩宏定义接口规范。
*/
#define RECTANGLE_AREA3(a, b) (a) * (b) //完备的括号。





