
/**
 *	
 *  ��������ͷ��㣩����ɾ�Ĳ�ʵ��
 *	
 *  ����޸�ʱ�䣺2016/1/29
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define ARRMALLOCSIZE 5
#define FALSE		  0
#define TRUE		  1			

typedef struct listNode
{
	int data;					//������
	struct listNode *next;		//ָ����
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

//main��������Ϊ����ʵ�����򣬾����㷨�ڷֺ���ʵ��
int main(void)
{
	linkList headerNode;													//����ͷ���
	resNode resultNode;														//���水ֵ���ҵĽ��
	int searchValue = 0, listLength, i, deleteValue, flag,
		searchDest, insertDest, insertValue, changeDest, changeValue;

	initLinkList(&headerNode);												//ͷ����ʼ��

	printf("���������֣���-1��������");
	flag = footCreateLinkList(&headerNode);									//β�巨����
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
	printfLinkList(&headerNode);							

	listLength = getLinkListLength(&headerNode);							//���
	printf("\n������ĳ���Ϊ��%d������ͷ��㣩", listLength);

	printf("\n����---��������Ҫ���ҵ�ֵ:");									//��ֵ����
	scanf("%d", &searchValue);
	flag = searchLinkListByValue(&headerNode, searchValue, &resultNode);
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
	else
	{
		if(resultNode.length == 0)
			printf("û�в鵽�йص�����%d��Ϣ--�����������ܣ�", searchValue);
		else
		{
			printf("��Ҫ���ҵ�ֵ�ڵ������λ�ã�");
			for(i = 0; i < resultNode.length; i++)
				printf("%-4d", resultNode.arr[i]);
		}
	}

	printf("\n����---��������Ҫ���ҵ�λ��:");								//��λ�ò���
	scanf("%d", &searchDest);
	flag = searchLinkListByIndex(&headerNode, searchDest);
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
	else
		printf("��Ҫ���ҵ�ֵΪ��%d", flag);

	printf("\nɾ��---��������Ҫɾ����λ��:");								//ɾ��
	scanf("%d", &deleteValue);
	flag = deleteLinkList(&headerNode, deleteValue);
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
	printfLinkList(&headerNode);

	printf("\n���---������Ҫ��____λ�����____ֵ����2,3��:");				//���
	scanf("%d,%d", &insertDest, &insertValue);
	flag = insertLinkList(&headerNode, insertDest, insertValue);
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
	printfLinkList(&headerNode);

	printf("\n�޸�---�������____λ�õ�ֵ��Ϊ____����2,3��:");						//�޸�
	scanf("%d,%d", &changeDest, &changeValue);
	flag = changeLinkList(&headerNode, changeDest, changeValue);
	if(!flag)
	{
		printf("���벻��������ʧ�ܣ�");
		return 0;
	}
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

//���
void printfLinkList(linkList *tempList)
{
	linkList *p = tempList->next;
	printf("��������Ϊ��\n");
	while(p)
	{
		printf("%-4d", p->data);
		p = p->next;
	}	
}


//��ȡ��(�ǵð�����ͷ)
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

//[��ֵdest]����,��Ӧ�ڵ��λ�ô洢��tempNode��--��ֵ����
int searchLinkListByValue(linkList *tempList, int num, resNode *tempNode)
{
	linkList *p = tempList->next;
	int j = 1;

	tempNode->length = 0;
	tempNode->arr = (int *)malloc(sizeof(int) * ARRMALLOCSIZE);
	//����ʧ��
	if(!tempNode->arr)
		return FALSE;
	//ѭ����������б���
	while(p)
	{
		//�ռ䲻�㿪�ٿռ�
		if((!(tempNode->length % 5)) && tempNode->length != 0)
		{
			tempNode->arr = (int *)realloc(tempNode->arr,  sizeof(int) * (tempNode->length + 1) * ARRMALLOCSIZE);
			//����ʧ��
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

//����destλ�õ�ֵ--��λ�ò���
int searchLinkListByIndex(linkList *tempList, int dest)
{
	linkList *p = searchLinkListDestBefore(tempList, dest-1);		//����pָ��dest-1�ڵ�

	if(!p || !p->next)												//dest-1 �� destλ�ò������ж�
		return FALSE;
	
	return p->next->data;
}

//ɾ�������еĵ�destλ�õ�ֵ
int deleteLinkList(linkList *tempList, int dest)
{
	linkList *p = searchLinkListDestBefore(tempList, dest-1);		//����pָ��dest-1�ڵ�

	if(!p || !p->next)												//dest-1 �� destλ�ò������ж�
		return FALSE;
	
	if(!p->next->next)												//dest���ڣ���Ϊ���һ���ڵ�
		p->next = NULL;
	else															//dest���ڣ�Ϊ�м�ڵ�
		p->next = p->next->next;
	
	return TRUE;
}

//����dest-1λ�ÿ�ʼ������ָ��
linkList *searchLinkListDestBefore(linkList *tempList, int dest)
{
	linkList * p = tempList;
	int i = 0, linkListLength;

	linkListLength = getLinkListLength(tempList);

	//λ�úϷ����ж�
	if(dest < 0 || dest > linkListLength)
		return NULL;

	for(i = 0; i < dest; i++)
		p = p->next;
	return p;
}

//��destλ�ò���num
int insertLinkList(linkList *tempList, int dest, int num)
{
	linkList *p, *node;

	p = searchLinkListDestBefore(tempList, dest-1);					//����pָ��dest-1�ڵ�
	if(!p)															//dest-1λ�ò������ж�
		return FALSE;

	node = (linkList *)malloc(sizeof(linkList));
	if(!node)
		return FALSE;
													
	node->data = num;												//dest�����ڻ򲻴��ڲ�Ӱ��
	node->next = p->next;
	p->next = node;
	
	return TRUE;
}

//��destλ�õ�ֵ��Ϊnum
int changeLinkList(linkList *tempList, int dest, int num)
{
	linkList *p = searchLinkListDestBefore(tempList, dest-1);		//����pָ��dest-1�ڵ�
	if(!p || !p->next)												//dest-1λ�ò������ж�
		return FALSE;
	
	p->next->data = num;
	
	return TRUE;
}