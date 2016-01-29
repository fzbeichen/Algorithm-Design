
/**
 *	单链表（带头结点）的倒置
 *	
 *  最后修改时间：2016/1/29
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define FALSE		  0
#define TRUE		  1			

typedef struct listNode
{
	int data;					//数据域
	struct listNode *next;		//指针域
}linkList;

void initLinkList(linkList *);
int headCreateLinkList(linkList *);
int footCreateLinkList(linkList *);
void printfLinkList(linkList *);
void reverseLinkList(linkList *);

int main(void)
{
	linkList headerNode;													//申请头结点
	int flag;

	initLinkList(&headerNode);												//头结点初始化

	printf("请输入数字（输-1结束）：");
	flag = footCreateLinkList(&headerNode);									//尾插法创建(下文有实现头插法)
	if(!flag)
	{
		printf("输入不合理，操作失败！");
		return 0;
	}
		printf("倒置前的结果为：\n");
	printfLinkList(&headerNode);							

	printf("\n倒置后的结果为：\n");

	reverseLinkList(&headerNode);
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

//单链表的倒置
void reverseLinkList(linkList *tempList)
{
	linkList *newList = tempList->next, *node;

	//保存头结点	
	tempList->next = NULL;

	while(newList)
	{
		node = newList;
		newList = newList->next;

		node->next = tempList->next;
		tempList->next = node;
	}
}

//输出
void printfLinkList(linkList *tempList)
{
	linkList *p = tempList->next;
	while(p)
	{
		printf("%-4d", p->data);
		p = p->next;
	}	
}