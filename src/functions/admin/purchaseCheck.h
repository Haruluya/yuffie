 /*
    @license:
    MIT License

    Copyright (c) 2022

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
    SOFTWARE.   //MIT֤��������Ϊ�̶����֡�

    @version:0.0.1
    @date:2022/5/9
    @author:haruluya
    @model_function:"�Բɹ����������ز���������ȫ�ֱ�����".
    @include:[purchaseApplyTableStruct.h,user.h]
    @work:[purchaseApplyTable.c,yuffie.c]
    @log:purchaseApplyTable.log

*/
#include "purchaseCheckStruct.h"

/*
    @function:"��ʼ���ɹ����뵥����"
*/
Status initList();

/*
    @function:"�������еĲɹ������ļ���"
*/
String fileName[50];

/*
    @function:"�������еĲɹ������ļ�����"
*/
int fileLen;

/*
    @function:"��ȡ���еĲɹ������ļ�"
*/
Status initApply();

/*
    @function:"�������вɹ������ļ�����ȡ������������ʦ�ύ�Ĳɹ�����"
*/
Status createPurchaseApply();

/*
    @function:"����ɹ����뵥�����ĳ���"
*/
int lengthList();

/*
    @function:"ɾ��ָ��id��ͨ���Լ�"
*/
Status deleteGPurchaseTable(int id);

/*
    @function:"ɾ��ָ��id��ר���Լ�"
*/
Status deleteSPurchaseTable(int id);

/*
    @function:"ɾ��ָ�����Լ�"
*/
Status deletePurchaseTable(int id);

/*
    @function:"������Ԫ�ص�������������ҩƷ�ı�Ž���ð������Ϊ����ɾ���ظ�Ԫ����׼��"
*/
Status sortList();

/*
    @function:"ɾ�������������ظ������ҩ��Ԫ��"
*/
Status deleteSameList();

/*
    @function:"�������յĲɹ�������ͨ���Լ��ɹ�����ר��ʵ�ʲɹ������ɹ����۱�"
*/
Status initPurchaseTable();

/*
    @function:"�������յĲɹ�������ͨ���Լ��ɹ��ļ�"
*/
Status createGPurchaseTable();

/*
    @function:"�������յĲɹ�������ר��ʵ�ʲɹ��ļ�"
*/
Status createSPurchaseTable();

/*
    @function:"�������յĲɹ��������ɹ������ļ�"
*/
Status createPurchaseTable();

