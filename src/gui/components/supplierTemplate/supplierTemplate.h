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
    @model_function:"suppler身份的事物处理窗口".
    @include:[globalConst.h]    
    @work:[supplerTemplate.c,yuffie.h]       
    @log:interfaces.log    

*/

#include"globalConst.h"


/*
    @value:supplierlist组件id。
*/
#define ID_SUPPLIER_LIST 601

/*
    @value:supplierCountLabel组件id。
*/
#define ID_YUFFIE_SUPPLIPER_COUNT_LAB 602

/*
    @value:supplierOfferButton组件id。
*/
#define ID_YUFFIE_OFFER_BUTTON 603

/*
    @value:supplierCommitButton组件id。
*/
#define ID_YUFFIE_COMMIT_BUTTON 604

/*
    @value:supplierOfferPriceEdit组件id。
*/
#define ID_YUFFIE_OFFER_PRICE_EDIT 605


/*
    @function:窗口过程。
*/
LRESULT CALLBACK HelloWndProc(HWND, UINT, WPARAM, LPARAM);