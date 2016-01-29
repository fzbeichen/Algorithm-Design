
/**
 *	��������ͷ��㣩�ĵ���
 *	
 *  ����޸�ʱ�䣺2016/1/29
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define FALSE		  0
#define TRUE		  1			

typedef struct listNode
{
	int data;					//������
	struct listNode *next;		//ָ����
}linkList;

void initLinkList(linkList *);
int headCreateLinkList(linkList *);
int footCreateLinkList(linkList *);
void printfLinkList(linkList *);
void reverseLinkList(linkList *);

int main(void)
{
	linkList headerNode;													//����ͷ���
	int flag;

	initLinkList(&headerNode);												//ͷ����ʼ��

	printf("���������֣���-1��������");
	flag = footCreateLinkList(&headerNode);									//β�巨����(������ʵ��ͷ�巨)
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
		printf("����ǰ�Ľ��Ϊ��\n");
	printfLinkList(&headerNode);							

	printf("\n���ú�Ľ��Ϊ��\n");

	reverseLinkList(&headerNode);
	printfLinkList(&headerNode);
	printf("\n");

	return 0;
}

//ͷ����ʼ��
void initLinkList(linkList *tempList)
{
	tempList->next = NULL;		//ָ�����ƿ�
}

//ͷ�巨����
int headCreateLinkList(linkList *tempList)
{
	int temp;
	linkList *node;
	node = (linkList *)malloc(sizeof(linkList));
	//����ʧ��
	if(!node)
		return FALSE;

	scanf("%d", &temp);
	while(temp != -1)
	{
		node->data = temp;
		node->next = tempList->next;
		tempList->next = node;

		node = (linkList *)malloc(sizeof(linkList));
		//����ʧ��
		if(!node)
			return FALSE;
		scanf("%d", &temp);
	}

	free(node);
	return TRUE;
}

//β�巨����
int footCreateLinkList(linkList *tempList)
{
	int temp;
	linkList *node, *flag;											//flagָ����Զָ��tempListβ��λ��
	flag = tempList;

	node = (linkList *)malloc(sizeof(linkList));
	//����ʧ��
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
		//����ʧ��
		if(!node)
			return FALSE;
		scanf("%d", &temp);
	}
	free(node);
	return TRUE;
}

//������ĵ���
void reverseLinkList(linkList *tempList)
{
	linkList *newList = tempList->next, *node;

	//����ͷ���	
	tempList->next = NULL;

	while(newList)
	{
		node = newList;
		newList = newList->next;

		node->next = tempList->next;
		tempList->next = node;
	}
}

//���
void printfLinkList(linkList *tempList)
{
	linkList *p = tempList->next;
	while(p)
	{
		printf("%-4d", p->data);
		p = p->next;
	}	
}