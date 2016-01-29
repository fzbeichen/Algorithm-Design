

/**
 *	˳������ɾ�Ĳ�ʵ��
 *	
 *  ����޸�ʱ�䣺2016/1/29
 *
 */

#include<stdio.h>

#define MAXSIZE 100
#define FALSE   0
#define TRUE    1

typedef struct 
{
	int elem[MAXSIZE];	//ÿ��Ԫ�ش洢һ��int�͵���������MAXSIZE��
	int length;			//��ǰ���Ա�洢�ĸ���
}seqList;

void initSeqList(seqList *);
void createSeqList(seqList *);
void printfSeqList(seqList *);
int insertSeqList(seqList *, int, int);
int deleteSeqList(seqList *, int);
int searchSeqList(seqList *, int);
int changeSeqList(seqList *, int, int);

//main����Ϊ���Գ��򣬾��幦���ڷֺ���ʵ��
int main(void)
{
	seqList tempList;																//�������Ա�	
	//��ʵ��鶨������������ȫ����
	int insertDest, insertNum, deleteDest, flag, searchDest, 
		changeDest,changeNum;
	
	initSeqList(&tempList);															//���Ա��ʼ��

	createSeqList(&tempList);														//�������Ա�

	printf("���---��Ҫ��____λ�����____������(��ʽ�磺2,34 ):\n");				//���Ա����
	scanf("%d,%d", &insertDest, &insertNum);
	flag = insertSeqList(&tempList, insertDest, insertNum);
	if(!flag)
		return 0;
	printfSeqList(&tempList);

	printf("ɾ��---������Ҫɾ��____λ�õ�ֵ��Ŀǰ����Ϊ%d:\n", tempList.length);	//���Ա�ɾ��
	scanf("%d", &deleteDest);
	flag = deleteSeqList(&tempList, deleteDest);
	if(!flag)
		return 0;
	printfSeqList(&tempList);

	printf("����---������Ҫ����____λ�õ�ֵ��Ŀǰ����Ϊ%d:\n", tempList.length);	//���Ա����
	scanf("%d", &searchDest);
	flag = searchSeqList(&tempList, searchDest);
	if(!flag)
		return 0;
	printf("���ҵ�ֵΪ��%d\n",flag);

	printf("�޸�---��Ҫ��____λ�õ�ֵ��Ϊ____������(��ʽ�磺2,34 ):\n");			//���Ա��޸�
	scanf("%d,%d", &changeDest, &changeNum);
	flag = changeSeqList(&tempList, changeDest, changeNum);
	if(!flag)
		return 0;
	printfSeqList(&tempList);

	return 0;
}

//��ʼ����tempList
void initSeqList(seqList *tempList)
{
	tempList->length = 0;
}

//���Ա���
void createSeqList(seqList *tempList)
{
	int temp;
	printf("���ʴ������뼸������\n");
	scanf("%d", &tempList->length);
	printf("��~��ʼ���룺\n");
	for(temp = 0; temp < tempList->length; temp ++)
	{
		scanf("%d", &tempList->elem[temp]);
	}
}

//���Ա����
void printfSeqList(seqList *tempList)
{
	int temp;
	printf("���������Ա�Ϊ��\n");
	for(temp = 0; temp < tempList->length; temp ++)
	{
		printf("%-4d", tempList->elem[temp]);
	}
	printf("\n");
}

//���Ա�Ĳ���,�����Ա��tempList��destλ�ò���num, destλ�ô�1��ʼ����
int insertSeqList(seqList *tempList, int dest, int num)
{
	int temp;
	//����
	if(tempList->length == MAXSIZE-1)
	{
		printf("���Ա��ѱ�����");
		return FALSE;			
	}
	//�ж�dest����ȷ��,tempList->length + 1������������
	if(dest < 1 || dest > tempList->length + 1)
	{
		printf("�����λ�ô���");
		return FALSE;
	}
	//��ȷִ�в���
	for(temp = tempList->length; temp >= dest; temp--)
	{
		tempList->elem[temp] = tempList->elem[temp-1];
	}
	tempList->elem[temp] = num;
	tempList->length ++;

	return TRUE;
}

//���Ա�ɾ��
int deleteSeqList(seqList *tempList, int dest)
{
	int temp;
	//�п�
	if(tempList->length == 0)
	{
		printf("���Ա�Ϊ�գ�");
		return FALSE;		
	}
	//����ɾ�������ڵ�λ��
	if(dest < 1 || dest > tempList->length)
	{
		printf("ɾ����λ�ò����ڣ�");
		return FALSE;
	}
	for(temp = dest; temp < tempList->length; temp ++)
	{
		tempList->elem[temp-1] = tempList->elem[temp];
	}
	tempList->length --;

	return TRUE;
}

//���Ա����
int searchSeqList(seqList *tempList, int dest)
{
	//�п�
	if(tempList->length == 0)
	{
		printf("���Ա�Ϊ�գ�");
		return FALSE;		
	}
	//���ܲ��Ҳ����ڵ�λ��
	if(dest < 1 || dest > tempList->length)
	{
		printf("���ҵ�λ�ò����ڣ�");
		return FALSE;
	}
	return tempList->elem[dest-1];
}

//���Ա��޸�,�����Ա��tempList��destλ�ø�Ϊnum, destλ�ô�1��ʼ����
int changeSeqList(seqList *tempList, int dest, int num)
{
	//�п�
	if(tempList->length == 0)
	{
		printf("���Ա�Ϊ�գ�");
		return FALSE;		
	}
	//�����滻�����ڵ�λ��
	if(dest < 1 || dest > tempList->length)
	{
		printf("�滻��λ�ò����ڣ�");
		return FALSE;
	}
	tempList->elem[dest-1] = num;

	return TRUE;
}