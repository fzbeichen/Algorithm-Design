

/**
 *	顺序表的增删改查实现
 *	
 *  最后修改时间：2016/1/29
 *
 */

#include<stdio.h>

#define MAXSIZE 100
#define FALSE   0
#define TRUE    1

typedef struct 
{
	int elem[MAXSIZE];	//每个元素存储一个int型的数，最多存MAXSIZE个
	int length;			//当前线性表存储的个数
}seqList;

void initSeqList(seqList *);
void createSeqList(seqList *);
void printfSeqList(seqList *);
int insertSeqList(seqList *, int, int);
int deleteSeqList(seqList *, int);
int searchSeqList(seqList *, int);
int changeSeqList(seqList *, int, int);

//main函数为测试程序，具体功能在分函数实现
int main(void)
{
	seqList tempList;																//定义线性表	
	//其实这块定义两个变量完全够用
	int insertDest, insertNum, deleteDest, flag, searchDest, 
		changeDest,changeNum;
	
	initSeqList(&tempList);															//线性表初始化

	createSeqList(&tempList);														//创建线性表

	printf("添加---你要在____位置添加____请输入(样式如：2,34 ):\n");				//线性表添加
	scanf("%d,%d", &insertDest, &insertNum);
	flag = insertSeqList(&tempList, insertDest, insertNum);
	if(!flag)
		return 0;
	printfSeqList(&tempList);

	printf("删除---请问你要删除____位置的值，目前长度为%d:\n", tempList.length);	//线性表删除
	scanf("%d", &deleteDest);
	flag = deleteSeqList(&tempList, deleteDest);
	if(!flag)
		return 0;
	printfSeqList(&tempList);

	printf("查找---请问你要查找____位置的值，目前长度为%d:\n", tempList.length);	//线性表查找
	scanf("%d", &searchDest);
	flag = searchSeqList(&tempList, searchDest);
	if(!flag)
		return 0;
	printf("查找的值为：%d\n",flag);

	printf("修改---你要把____位置的值改为____请输入(样式如：2,34 ):\n");			//线性表修改
	scanf("%d,%d", &changeDest, &changeNum);
	flag = changeSeqList(&tempList, changeDest, changeNum);
	if(!flag)
		return 0;
	printfSeqList(&tempList);

	return 0;
}

//初始化表tempList
void initSeqList(seqList *tempList)
{
	tempList->length = 0;
}

//线性表创建
void createSeqList(seqList *tempList)
{
	int temp;
	printf("请问打算输入几个数：\n");
	scanf("%d", &tempList->length);
	printf("好~开始输入：\n");
	for(temp = 0; temp < tempList->length; temp ++)
	{
		scanf("%d", &tempList->elem[temp]);
	}
}

//线性表输出
void printfSeqList(seqList *tempList)
{
	int temp;
	printf("操作后线性表为：\n");
	for(temp = 0; temp < tempList->length; temp ++)
	{
		printf("%-4d", tempList->elem[temp]);
	}
	printf("\n");
}

//线性表的插入,向线性表表tempList的dest位置插入num, dest位置从1开始计算
int insertSeqList(seqList *tempList, int dest, int num)
{
	int temp;
	//判满
	if(tempList->length == MAXSIZE-1)
	{
		printf("线性表已表满！");
		return FALSE;			
	}
	//判断dest的正确性,tempList->length + 1，添加在最后面
	if(dest < 1 || dest > tempList->length + 1)
	{
		printf("插入的位置错误！");
		return FALSE;
	}
	//正确执行操作
	for(temp = tempList->length; temp >= dest; temp--)
	{
		tempList->elem[temp] = tempList->elem[temp-1];
	}
	tempList->elem[temp] = num;
	tempList->length ++;

	return TRUE;
}

//线性表删除
int deleteSeqList(seqList *tempList, int dest)
{
	int temp;
	//判空
	if(tempList->length == 0)
	{
		printf("线性表为空！");
		return FALSE;		
	}
	//不能删除不存在的位置
	if(dest < 1 || dest > tempList->length)
	{
		printf("删除的位置不存在！");
		return FALSE;
	}
	for(temp = dest; temp < tempList->length; temp ++)
	{
		tempList->elem[temp-1] = tempList->elem[temp];
	}
	tempList->length --;

	return TRUE;
}

//线性表查找
int searchSeqList(seqList *tempList, int dest)
{
	//判空
	if(tempList->length == 0)
	{
		printf("线性表为空！");
		return FALSE;		
	}
	//不能查找不存在的位置
	if(dest < 1 || dest > tempList->length)
	{
		printf("查找的位置不存在！");
		return FALSE;
	}
	return tempList->elem[dest-1];
}

//线性表修改,把线性表表tempList的dest位置改为num, dest位置从1开始计算
int changeSeqList(seqList *tempList, int dest, int num)
{
	//判空
	if(tempList->length == 0)
	{
		printf("线性表为空！");
		return FALSE;		
	}
	//不能替换不存在的位置
	if(dest < 1 || dest > tempList->length)
	{
		printf("替换的位置不存在！");
		return FALSE;
	}
	tempList->elem[dest-1] = num;

	return TRUE;
}