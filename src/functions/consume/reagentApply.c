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
    @date:2022/5/18
    @author:deng
    @model_function:"实验室试剂申领相关函数".
    @include:[reagentApply.h]
    @work:reagentApply.c
    @log:mainReagent.log

*/

#include"reagentApply.h"

/*
    @author:deng
    @date:2022/5/31
    @function:"载入所有申请表"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status initReagentApply() {
	reagentApplyList = (ReagentApplyLinkList)malloc(sizeof(RNode));
	if (!reagentApplyList)
	{
		return ERROR;
	}
	reagentApplyList->next = NULL; 
	return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"添加请求项"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status addReagentApplyItem(ReagentApplyItem item) {
	if (!item.reagentName) {
		return INFASIBLE;
	}
	ReagentApplyLinkList ptr = reagentApplyList;
	while (ptr->next) {
		ptr = reagentApplyList->next;
	}
	RNode* node = (RNode*)malloc(sizeof(RNode));
	node->data.reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
	strcpy(node->data.reagentName, item.reagentName);
	node->data.reagentId = item.reagentId;
	node->data.reagentNum = item.reagentNum;
	ptr->next = node;
	node->next = NULL;

	reagentApplyListLen++;
	return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"删除请求项"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status deleteReagentApplyItemById(int index) {
	if (index < 0) {
		return INFASIBLE;
	}
	ReagentApplyLinkList ptr = reagentApplyList->next;
	while ((ptr-reagentApplyList) < reagentApplyListLen) {
		if ((ptr - reagentApplyList) == index) {
			ptr->next = ptr->next->next;
			return OK;
		}
		ptr = ptr->next;
	}
	reagentApplyListLen--;
	return NOT_FOUND;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"提交请求项"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status commitReagentApply() {
	FILE* fp;
	String fileName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
	String str = (String)malloc(sizeof(char) * INFO_MAXSIZE);
	sprintf(str, "%d", presentUser.id);
	fileName = strcat(strcat(strcat(strcpy(fileName, "./reagentApply/"), str), presentUser.userName), ".txt");
	/*
	   @check:"文件打开错误处理."
	*/
	if (!(fp = fopen(fileName, "w")))
	{
		return ERROR;
	}
	ReagentApplyLinkList ptr = reagentApplyList->next;
	while (ptr) {
		fprintf(fp,
			"%s %d %d\n",
			ptr->data.reagentName,
			ptr->data.reagentId,
			ptr->data.reagentNum
		);
		ptr = ptr->next;
	}
	fclose(fp);
	return OK;
}

/*
    @author:deng
    @date:2022/5/31
    @function:"载入当前用户的申请表结果"
    @input:{
    }
    @output:{
    }
    @execute:[deng.WinMain]
    @return:"执行状态"
*/
Status initResultList() {
	FILE* fp;
	    /*
		   @check:"文件打开错误处理."
		*/
	if (!(fp = fopen("reagentAuditResult.txt", "r")))
	{
		return ERROR;
	}
	while (!feof(fp))
	{
		fgets(BUFF, sizeof(BUFF), fp);
		if (!strcmp(BUFF, "\0")) {
			break;
		}
		//获取以空格切分的属性数组.
		String* reagentResultInfo = yuffieSplit(BUFF);

		if (atoi(reagentResultInfo[3]) == presentUser.id) {
			String* reagentName = (String)malloc(sizeof(char) * INFO_MAXSIZE);
			strcpy(reagentName, reagentResultInfo[0]);
			ReagentApplyItem item = {
				reagentName,
				atoi(reagentResultInfo[1]),
				atoi(reagentResultInfo[2]),
			};
			reagentResultList[reagentResultListLen++] = item;
		}
		BUFF[0] = '\0';
	}
	fclose(fp);
	return OK;
}