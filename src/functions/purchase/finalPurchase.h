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
    @model_function:"对订购相关操作函数和全局变量。".
    @include:[purchaseTableStruct.h,user.h]
    @work:[purchaseTable.c,yuffie.h]
    @log:purchaseTable.log

*/

#include"finalPurchaseStruct.h"
#include"user.h"


/*
    @function:"载入最终订购表数据。"
*/
Status initFinalPurchaseList(String,int);

/*
    @function:"获取所有的供应商报价文件"
*/
Status initOfferApply();
/*
    @function:"载入每个药品对应的所有供应商报价数据。"
*/
Status initPrice();

/*
    @function:"对每个药品对应的所有供应商报价数据选择报价最少的。"
*/
Status selectPrice();

/*
    @function:"载入每个药品最终选择的报价和供应商数据。"
*/
Status finalPrice();

/*
    @function:"完成比价并创建最终的购买表。"
*/
Status createFinalPrice();
