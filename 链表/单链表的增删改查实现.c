
/**
 *	
 *  单链表（带头结点）的增删改查实现
 *	
 *  最后修改时间：2016/1/29
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define ARRMALLOCSIZE 5
#define FALSE		  0
#define TRUE		  1			

typedef struct listNode
{
	int data;					//数据域
	struct listNode *next;		//指针域
}linkList;

typedef struct resultNode
{
	int *arr;
	int length;
}resNode;

void initLinkList(linkList *);
int headCreateLinkList(linkList *);
int footCreateLinkList(linkList *);
void printfLinkList(linkList *);
int getLinkListLength(linkList *);
int searchLinkListByValue(linkList *, int, resNode *);
int deleteLinkList(linkList *, int);
linkList *searchLinkListDestBefore(linkList *, int);
int searchLinkListByIndex(linkList *, int);
int insertLinkList(linkList *, int, int);
int changeLinkList(linkList *, int, int);

//main函数程序为测试实例程序，具体算法在分函数实现
int main(void)
{
	linkList headerNode;													//申请头结点
	resNode resultNode;														//保存按值查找的结果
	int searchValue = 0, listLength, i, deleteValue, flag,
		searchDest, insertDest, insertValue, changeDest, changeValue;

	initLinkList(&headerNode);												//头结点初始化

	printf("请输入数字（输-1结束）：");
	flag = footCreateLinkList(&headerNode);									//尾插法创建
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
	printfLinkList(&headerNode);							

	listLength = getLinkListLength(&headerNode);							//求表长
	printf("\n单链表的长度为：%d（包括头结点）", listLength);

	printf("\n查找---请输入你要查找的值:");									//按值查找
	scanf("%d", &searchValue);
	flag = searchLinkListByValue(&headerNode, searchValue, &resultNode);
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
	else
	{
		if(resultNode.length == 0)
			printf("没有查到有关的数字%d信息--继续其他功能：", searchValue);
		else
		{
			printf("你要查找的值在单链表的位置：");
			for(i = 0; i < resultNode.length; i++)
				printf("%-4d", resultNode.arr[i]);
		}
	}

	printf("\n查找---请输入你要查找的位置:");								//按位置查找
	scanf("%d", &searchDest);
	flag = searchLinkListByIndex(&headerNode, searchDest);
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
	else
		printf("你要查找的值为：%d", flag);

	printf("\n删除---请输入你要删除的位置:");								//删除
	scanf("%d", &deleteValue);
	flag = deleteLinkList(&headerNode, deleteValue);
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
	printfLinkList(&headerNode);

	printf("\n添加---请问你要给____位置添加____值（如2,3）:");				//添加
	scanf("%d,%d", &insertDest, &insertValue);
	flag = insertLinkList(&headerNode, insertDest, insertValue);
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
	printfLinkList(&headerNode);

	printf("\n修改---请问你把____位置的值改为____（如2,3）:");						//修改
	scanf("%d,%d", &changeDest, &changeValue);
	flag = changeLinkList(&headerNode, changeDest, changeValue);
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
	printfLinkList(&headerNode);
	printf("\n");

	return 0;
}

//头结点初始化
void initLinkList(linkList *tempList)
{
	tempList->next = NULL;		//指针域制空
}

//头插法创建
int headCreateLinkList(linkList *tempList)
{
	int temp;
	linkList *node;
	node = (linkList *)malloc(sizeof(linkList));
	//创建失败
	if(!node)
		return FALSE;

	scanf("%d", &temp);
	while(temp != -1)
	{
		node->data = temp;
		node->next = tempList->next;
		tempList->next = node;

		node = (linkList *)malloc(sizeof(linkList));
		//创建失败
		if(!node)
			return FALSE;
		scanf("%d", &temp);
	}

	free(node);
	return TRUE;
}

//尾插法创建
int footCreateLinkList(linkList *tempList)
{
	int temp;
	linkList *node, *flag;											//flag指针永远指向tempList尾部位置
	flag = tempList;
	node = (linkList *)malloc(sizeof(linkList));
	//创建失败
	if(!node)
		return FALSE;

	scanf("%d", &temp);
	while(temp != -1)
	{
		node->data = temp;
		node->next = flag->next;
		flag->next = node;
		flag = node;

		node = (linkList *)malloc(sizeof(linkList));
		//创建失败
		if(!node)
			return FALSE;
		scanf("%d", &temp);
	}
	free(node);
	return TRUE;
}

//输出
void printfLinkList(linkList *tempList)
{
	linkList *p = tempList->next;
	printf("操作后结果为：\n");
	while(p)
	{
		printf("%-4d", p->data);
		p = p->next;
	}	
}


//获取表长(记得包括表头)
int getLinkListLength(linkList *tempList)
{
	int length = 0;
	linkList *p = tempList;
	while(p)
	{
		length ++;
		p = p->next;
	}
	return length;
}

//[按值dest]查找,对应节点的位置存储在tempNode里--按值查找
int searchLinkListByValue(linkList *tempList, int num, resNode *tempNode)
{
	linkList *p = tempList->next;
	int j = 1;

	tempNode->length = 0;
	tempNode->arr = (int *)malloc(sizeof(int) * ARRMALLOCSIZE);
	//创建失败
	if(!tempNode->arr)
		return FALSE;
	//循环对链表进行遍历
	while(p)
	{
		//空间不足开辟空间
		if((!(tempNode->length % 5)) && tempNode->length != 0)
		{
			tempNode->arr = (int *)realloc(tempNode->arr,  sizeof(int) * (tempNode->length + 1) * ARRMALLOCSIZE);
			//创建失败
			if(!tempNode->arr)
				return FALSE;
		}
		if(p->data == num)
		{
			tempNode->arr[tempNode->length++] = j;
		}
		p = p->next;
		j++;
	}
	return TRUE;
}

//查找dest位置的值--按位置查找
int searchLinkListByIndex(linkList *tempList, int dest)
{
	linkList *p = searchLinkListDestBefore(tempList, dest-1);		//现在p指向dest-1节点

	if(!p || !p->next)												//dest-1 或 dest位置不存在判断
		return FALSE;
	
	return p->next->data;
}

//删除链表中的第dest位置的值
int deleteLinkList(linkList *tempList, int dest)
{
	linkList *p = searchLinkListDestBefore(tempList, dest-1);		//现在p指向dest-1节点

	if(!p || !p->next)												//dest-1 或 dest位置不存在判断
		return FALSE;
	
	if(!p->next->next)												//dest存在，但为最后一个节点
		p->next = NULL;
	else															//dest存在，为中间节点
		p->next = p->next->next;
	
	return TRUE;
}

//返回dest-1位置开始的链表指针
linkList *searchLinkListDestBefore(linkList *tempList, int dest)
{
	linkList * p = tempList;
	int i = 0, linkListLength;

	linkListLength = getLinkListLength(tempList);

	//位置合法性判断
	if(dest < 0 || dest > linkListLength)
		return NULL;

	for(i = 0; i < dest; i++)
		p = p->next;
	return p;
}

//向dest位置插入num
int insertLinkList(linkList *tempList, int dest, int num)
{
	linkList *p, *node;

	p = searchLinkListDestBefore(tempList, dest-1);					//现在p指向dest-1节点
	if(!p)															//dest-1位置不存在判断
		return FALSE;

	node = (linkList *)malloc(sizeof(linkList));
	if(!node)
		return FALSE;
													
	node->data = num;												//dest不存在或不存在不影响
	node->next = p->next;
	p->next = node;
	
	return TRUE;
}

//把dest位置的值改为num
int changeLinkList(linkList *tempList, int dest, int num)
{
	linkList *p = searchLinkListDestBefore(tempList, dest-1);		//现在p指向dest-1节点
	if(!p || !p->next)												//dest-1位置不存在判断
		return FALSE;
	
	p->next->data = num;
	
	return TRUE;
}