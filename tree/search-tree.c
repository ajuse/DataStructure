#include <stdio.h>
#include <stdlib.h>


struct SearchTree
{
	int element;
	struct SearchTree *left;
	struct SearchTree *right;
};

struct SearchTree *make_empty(struct SearchTree *tree)
{
	if (tree != NULL)
	{
		make_empty(tree->left);
		make_empty(tree->right);
		free(tree);
	}

	return NULL;
}

struct SearchTree *insert_node(struct SearchTree *tree, int element)
{
	if (tree == NULL)
	{
		tree = (struct SearchTree *)malloc(sizeof(struct SearchTree));
		if (tree == NULL)
		{
			printf("malloc failed!\n");
			return NULL;
		}
		else
		{
			tree->element = element;
			tree->left = NULL;
			tree->right = NULL;
			printf("add element : %d success\n", element);
		}
	}
	else if (element < tree->element)
	{
		//printf("element %d < tree->element %d\n", element, tree->element);
		tree->left = insert_node(tree->left, element);
	}
	else if (element > tree->element)
	{
		//printf("element %d > tree->element %d\n", element, tree->element);
		tree->right = insert_node(tree->right, element);
	}
	
	return tree;
}

struct SearchTree *find_node(struct SearchTree *tree, int element)
{
	if (tree == NULL)
	{
		printf("can't find element %d\n", element);
		return NULL;
	}
	else if (element < tree->element)
	{
		//printf("element %d < tree->element %d\n", element, tree->element);
		return find_node(tree->left, element);
	}
	else if (element > tree->element)
	{
		//printf("element %d > tree->element %d\n", element, tree->element);
		return find_node(tree->right, element);
	}
    else if (element == tree->element)
    {
        printf("find element : %d success\n", element);
    }
	
	return tree;
}

struct SearchTree *find_min_node(struct SearchTree *tree)
{
	if (tree == NULL)
	{
		printf("find min node Tree is NULL!\n");
		return NULL;
	}

	if (tree->left == NULL)
	{					
		return tree;	
	}
	else
	{
	
		return find_min_node(tree->left);
	}
}


struct SearchTree *delete_node(struct SearchTree *tree, int element)
{
	struct SearchTree *tree_tmp;
	if (tree == NULL)
	{		
		printf("Tree is NULL\n");	
		return NULL;	
	}
	else if (element < tree->element)
	{
		//printf("element %d < tree->element %d\n", element, tree->element);
		tree->left = delete_node(tree->left, element);
	}
	else if (element > tree->element)
	{
		//printf("element %d > tree->element %d\n", element, tree->element);
		tree->right = delete_node(tree->right, element);
	}
	else
	{
		//two children
		if (tree->right != NULL && tree->left != NULL)
		{
			tree_tmp = find_min_node(tree->right);
			tree->element = tree_tmp->element;
			tree->right = delete_node(tree->right, tree->element);
		}
		//one or zero children
		else
		{
			tree_tmp = tree;
			if (tree->right == NULL)
			{
				tree = tree->left;
			}
			else if (tree->left == NULL)
			{
				tree = tree->right;
			}

			free(tree_tmp);
		}
	}
	
	return tree;
}

int printf_tree_inorder_traversal(struct SearchTree *tree)
{
	if (tree == NULL)
	{
		return 0;
	}

	if (tree->left != NULL)
	{
		printf_tree_inorder_traversal(tree->left);
	}

	printf("%d ", tree->element);

	if (tree->right != NULL)
	{
		printf_tree_inorder_traversal(tree->right);
	}

	return 0;
}

int main(void)
{
	struct SearchTree tree;
    struct SearchTree *tmp_node = NULL;
    
	int num[10] = {3, 4, 1, 10, 8, 6, 9, 15, 12, 14};
	int i;
	
	tree.element = 5;
	tree.left = NULL;
	tree.right = NULL;

	printf("root element : %d\n", tree.element);
	for (i = 0; i < 10; i++)
	{
		insert_node(&tree, num[i]);
	}

	printf_tree_inorder_traversal(&tree);
	printf("\n");

    tmp_node = find_node(&tree, 9);

    if (tmp_node != NULL)
    {
        printf("find element : %d\n", tmp_node->element);
    }

    delete_node(&tree, 10);

    printf_tree_inorder_traversal(&tree);
	printf("\n");

	delete_node(&tree, 9);

    printf_tree_inorder_traversal(&tree);
	printf("\n");


	return 0;
}
