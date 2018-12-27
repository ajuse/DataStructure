#include <stdio.h>
#include <stdlib.h>

//应该尽量避免直接操作传下来的指针，而是应该复制这个指针，多并发的情况下参数指针的值可能会改变

struct Node
{
	struct Node *ppre;
	int element;
	struct Node *pnext;
};

int add_node(struct Node *phead, int element)
{
	struct Node *new_node = NULL;
	struct Node *ptmp = phead;

	new_node = (struct Node *)malloc(sizeof(struct Node));

	if(new_node == NULL)
	{
		printf("malloc Node failed !\n");
		return -1;
	}

	while(ptmp->pnext != phead)
	{
		ptmp = ptmp->pnext;
	}

	ptmp->pnext = new_node;
	new_node->pnext = phead;
	new_node->ppre = ptmp;
	new_node->element = element;

	return 0;
}

struct Node *find_node(struct Node *head_list, int element)
{
	struct Node *ptmp = head_list;

	while(ptmp->pnext != head_list && ptmp->element != element)
	{
		ptmp = ptmp->pnext;
	}

	if(ptmp == NULL)
	{
		printf("can't find element %d\n", element);
		return NULL;
	}
	else
	{
		printf("find element %d success\n", element);
		return ptmp;
	}
}

struct Node *find_previous_node(struct Node *head_list, int element)
{
	struct Node *ptmp = head_list;

	while(ptmp->pnext != head_list && ptmp->pnext->element != element)
	{
		ptmp = ptmp->pnext;
	}

	if(ptmp->pnext == NULL)
	{
		printf("can't find element %d\n", element);
		return NULL;
	}
	else
	{
		printf("find element %d success\n", ptmp->pnext->element);
		return ptmp;
	}
}

int del_node(struct Node *phead, int element)
{
	struct Node *ptmp, *pdeltmp;

	ptmp = find_previous_node(phead, element);

	if(ptmp == NULL)
	{
		printf("delete element %d failed!\n", element);

		return -1;
	}

	pdeltmp = ptmp->pnext;
	ptmp->pnext = pdeltmp->pnext;
	pdeltmp->pnext->ppre = ptmp;
	free(pdeltmp);

	printf("delete success\n");

	return 0;
}

int insert_node(struct Node *node, int element)
{
	struct Node *new_node = NULL;
	struct Node *pnode = node, *ptmp = node->pnext;

	new_node = (struct Node *)malloc(sizeof(struct Node));

	if(new_node == NULL || node == NULL)
	{
		printf("malloc Node failed !\n");
		return -1;
	}

	pnode->pnext = new_node;
	new_node->pnext = ptmp;
	ptmp->ppre = new_node;
	new_node->ppre = pnode;
	new_node->element = element;

	return 0;
}

int print_list(struct Node *List)
{
	struct Node *ptmp = List;
	int list_len = 0;
	int count = 20;

	//正序
	do
	{
		printf("%d -> ", ptmp->element);
		list_len++;
		ptmp = ptmp->pnext;
	}while(ptmp != List);

	printf("end, list len : %d\n", list_len);
	//逆序
	list_len = 0;
	ptmp = List;
	do
	{
		printf("%d -> ", ptmp->element);
		list_len++;
		ptmp = ptmp->ppre;
	}while(ptmp != List);
	
	printf("end, list len : %d\n", list_len);
	return 0;
}

int del_list(struct Node *head_list)
{
	struct Node *ptmp, *pfreetmp;

	ptmp = head_list->pnext;
	head_list->pnext = NULL;
	head_list->ppre = NULL;

	while(ptmp != NULL)
	{
		pfreetmp = ptmp->pnext;
		free(pfreetmp);
		ptmp = pfreetmp;
	}

	return 0;
}

int main(void)
{
	struct Node head_list;
	int i;

	head_list.element = 0;
	head_list.pnext = &head_list;
	head_list.ppre = &head_list;

	for (i = 1; i < 10; i++)
		add_node(&head_list, i);

	print_list(&head_list);

	del_node(&head_list, 9);

	print_list(&head_list);

	insert_node(find_node(&head_list, 3), 22);

	print_list(&head_list);

	insert_node(find_node(&head_list, 8), 33);

	print_list(&head_list);

	return 0;

}
