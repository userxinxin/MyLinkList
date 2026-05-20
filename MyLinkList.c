#include <stdio.h>
#include <stdlib.h>


//定义链表的节点结构
typedef struct Node
{
	int data;
	struct Node* next;
}NODE;

//定义链表的结构
typedef struct LinkList
{
	NODE* pHead;
	NODE* pEnd;
	int length;
}LL;

//初始化节点
NODE* initNode(int data)
{
	NODE* pTemp = (NODE*)malloc(sizeof(NODE));
	if (NULL == pTemp)
	{
		printf("节点初始化失败\n");
		return NULL;
	}
	pTemp->data = data;
	pTemp->next = NULL;
	return pTemp;
}

//初始化链表,给链表分配内存
LL * initLL()
{
	LL* pTemp = (LL*)malloc(sizeof(LL));
	if (NULL == pTemp)
	{
		printf("链表初始化失败\n");
		return;
	}
	pTemp->pEnd = pTemp->pHead = NULL;
	pTemp->length = 0;
	return pTemp;
}

//从尾部添加数据，空链表适用
void appendList(LL* pList, int data)
{
	NODE* pTemp = initNode(data);
	if (NULL == pTemp)
	{
		return;
	}
	//链表没有数据
	if (NULL == pList->pHead)
	{
		pList->pHead = pList->pEnd = pTemp;
	}
	else
	{
		pList->pEnd->next = pTemp;
		pList->pEnd = pTemp;
	}
	pList->length++;
	pTemp = NULL;
}

//头插或者中间插
void insertNode(LL* pList, int idx, int data)
{
	if (NULL == pList || NULL == pList->pHead)
	{
		printf("链表为空，无法插入\n");
		return;
	}
	NODE* pTemp = initNode(data);
	if (NULL == pTemp)
	{
		return;
	}
	if (idx <= 0)
	{
		pTemp->next = pList->pHead;
		pList->pHead = pTemp;
	}
	else if (idx >= pList->length)
	{
		pList->pEnd->next = pTemp;
		pList->pEnd = pTemp;
	}
	else
	{
		NODE* pPre = pList->pHead;
		//pre,predecessor,前任，前辈，前驱
		for (int i = 1; i < idx; i++)
		{
			pPre = pPre->next;
		}
		pTemp->next = pPre->next;
		pPre->next = pTemp;
		pPre = NULL;
	}
	pList->length++;
	pTemp = NULL;
}

//节点删除,头尾中间
void delNode(LL* pList, int idx)
{
	NODE* pTemp = pList->pHead;
	//ptemp是要删除的节点
	if (idx <= 0)
	{
		pList->pHead = pTemp->next;
	}
	else if (idx >= pList->length)
	{
		NODE* pPre = pList->pHead;
		while (NULL != pTemp->next)
		{
			pPre = pTemp;
			pTemp = pTemp->next;
		}
		//ptemp遍历到最后节点,ppre倒数第二个节点
		pPre->next = NULL;

	}
	else
	{
		//ppre在删除节点前一个位置,
		NODE* pPre = pList->pHead;
		for (int i = 1; i < idx; i++)
		{
			pPre = pPre->next;
		}
		 pTemp = pPre->next;
		pPre->next = pTemp->next;
		
	}
	pList->length--;
	free(pTemp);
	
}

//改
void modiNode(LL* pList, int idx, int data)
{
	if (NULL == pList || NULL == pList->pHead)
	{
		printf("链表为空，无法修改值\n");
		return;
	}
	NODE* pTemp = pList->pHead;
	if (idx >= pList->length)
	{
		pList->pEnd->data = data;
		return;
	}
	//ptemp要移动到要改的位置上
	for (int i = 0; i < idx; i++)
	{
		pTemp = pTemp->next;
	}
	pTemp->data = data;
}

//查,不能用二分，因为链表不支持随机访问，也不能指针偏移
void findNode(LL* pList, int data)
{
	if (NULL == pList || NULL == pList->pHead)
	{
		printf("链表为空，无法查找\n");
		return;
	}
	int i = 0;
	NODE* pTemp = pList->pHead;
	while (NULL != pTemp)
	{
		i++;
		if (pTemp->data == data)
		{
			printf("数据%d在链表中的第%d个位置\n",data,i);
			return;
		}
		pTemp = pTemp->next;
	}
	printf("没找到\n");
}

//链表的死亡
void delLL(LL* pList)
{
	if (NULL == pList || NULL == pList->pHead)
	{
		printf("链表为空，无法释放\n");
		return;
	}
	NODE* pTemp = pList->pHead;
	while (NULL != pList->pHead)
	{
		pTemp = pList->pHead;
		pList->pHead = pList->pHead->next;
		free(pTemp);
		pTemp = NULL;
	}
	pList->pEnd = NULL;
	pList->length = 0;
	
}

//遍历链表
void printfLL(LL* pList)
{
	if (NULL == pList)
	{
		printf("链表为空，无法遍历\n");
		return;
	}
	NODE* pTemp = pList->pHead;
	while (NULL != pTemp) 
	{
		NODE* pPre = pTemp;
		printf("%d\t", pPre->data);
		pTemp = pTemp->next;
	}
	printf("\n");
}

int main(void)
{
	LL *pList = initLL();
	appendList(pList,1);
	appendList(pList, 2);
	appendList(pList, 3);
	//appendList(pList, 4);
	//appendList(pList, 5);

	//insertNode(pList, -1, 0);
	//insertNode(pList, 9, 999);
	//insertNode(pList, 9, 6);

	printfLL(pList);

	modiNode(pList, -1, 0);

	findNode(pList, 6);

	printfLL(pList);

	delLL(pList);
	free(pList);
	return 0;
}
//怎么才能把新记录提交到github嘞