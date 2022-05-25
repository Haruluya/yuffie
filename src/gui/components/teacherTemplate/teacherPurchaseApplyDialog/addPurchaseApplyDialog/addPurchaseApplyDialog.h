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

    @version:0.0.2
    @date:2022/5/15
    @author:haruluya
    @model_function:"teacher视图中的添加采购申请选项dialog".
    @include:globalConst.h   
    @work:addPurchaseApplyDialog.c       
    @log:addPurchaseApplyDialog.log    

*/

#include"globalConst.h"

#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_LAB 2101
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENAME_LAB 2102
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENAME_EDIT 2103
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_REID_LAB 2104
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_REID_EDIT 2105
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENUM_LAB 2106
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_RENUM_EDIT 2107
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_RECLASS_LAB 2108
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_GEN_RADIO_BUTTON 2109
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_SPE_RADIO_BUTTON 2110
#define ID_YUFFIE_TEACHER_PURCHASE_APPLY_FINISH_BUTTON 2111


BOOL CALLBACK PurchaseApplyAddDlgProc(HWND, UINT, WPARAM, LPARAM);