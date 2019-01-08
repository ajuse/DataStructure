#include <stdio.h>
#include <stdlib.h>


struct AvlTree
{
    int element;
    struct AvlTree *left;
    struct AvlTree *right;
    int height;
};

int printf_tree_inorder_traversal(struct AvlTree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }  

    if (tree->left != NULL)
    {
        printf_tree_inorder_traversal(tree->left);
    }

    printf("%d:%dh ", tree->element, tree->height);

    if (tree->right != NULL)
    {
        printf_tree_inorder_traversal(tree->right);
    }

    return 0;
}

int get_tree_height(struct AvlTree *tree)
{
    if (tree == NULL)
    {
        return -1;
    }
    else
    {
        return tree->height;
	}
}

int get_max_tree_height(struct AvlTree *tree)
{
    int letf_height, right_height;

    letf_height = get_tree_height(tree->left);
    right_height = get_tree_height(tree->right);

    return (letf_height > right_height) ? letf_height : right_height;
}

struct AvlTree *make_empty(struct AvlTree *tree)
{
    if (tree != NULL)
    {
        make_empty(tree->left);
        make_empty(tree->right);
        free(tree);
    }

    return NULL;
}

/* 0 means right, 1 means left */
static struct AvlTree *single_rotate(struct AvlTree *tree, int operate)
{
    struct AvlTree *tree_tmp;

    //printf("tree->element %d get in single rotate\n", tree->element);
    if (operate == 0)
    {
        tree_tmp = tree->left;
        tree->left = tree_tmp->right;
        tree_tmp->right = tree;

        tree_tmp->height = get_max_tree_height(tree_tmp) + 1;
        tree->height = get_max_tree_height(tree) + 1;
    }
    else if (operate == 1)
    {
        tree_tmp = tree->right;
        tree->right = tree_tmp->left;
        tree_tmp->left = tree;

        tree_tmp->height = get_max_tree_height(tree_tmp) + 1;
        tree->height = get_max_tree_height(tree) + 1;
    }
    else
    {
        printf("not support this %d operate !\n", operate);
    }

    return tree_tmp;
}

struct AvlTree *double_rotate(struct AvlTree *tree, int operate)
{
    //printf("tree->element %d get in double rotate\n", tree->element);
    if (operate == 0)
    {
        tree->right = single_rotate(tree->right, 0);
        return single_rotate(tree, 1);
    }
    else if (operate == 1)
    {
        tree->left = single_rotate(tree->left, 1);
        return single_rotate(tree, 0);
    }

    return tree;
}

/* 0 means right, 1 means left */
struct AvlTree *insert_node(struct AvlTree *tree, int element)
{
    if (tree == NULL)
    {
        tree = (struct AvlTree *)malloc(sizeof(struct AvlTree));
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
            tree->height = 0;
            printf("add element : %d success\n", element);
        }
    }
    else if (element < tree->element)
    {
        //printf("element %d < tree->element %d\n", element, tree->element);
        tree->left = insert_node(tree->left, element);

        if ((get_tree_height(tree->left) - get_tree_height(tree->right)) == 2)
        {
            if (tree->left->element > element)
            {
                tree = single_rotate(tree, 0);
            }
            else
            {
                tree = double_rotate(tree, 1);
            }
        }
    }
    else if (element > tree->element)
    {
        //printf("element %d > tree->element %d\n", element, tree->element);
        tree->right = insert_node(tree->right, element);

        if ((get_tree_height(tree->right) - get_tree_height(tree->left)) == 2)
        {
            if (tree->right->element < element)
            {
                tree = single_rotate(tree, 1);
            }
            else
            {
                tree = double_rotate(tree, 0);
            }
        }
    }

    tree->height = get_max_tree_height(tree) + 1;

    printf_tree_inorder_traversal(tree);
    printf("\n");

    return tree;
}

struct AvlTree *find_node(struct AvlTree *tree, int element)
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

struct AvlTree *find_min_node(struct AvlTree *tree)
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


struct AvlTree *delete_node(struct AvlTree *tree, int element)
{
    struct AvlTree *tree_tmp;

    if (tree == NULL)
    {		
        printf("Tree is NULL\n");	
        return NULL;	
    }
    else if (element < tree->element)
    {
        //printf("element %d < tree->element %d\n", element, tree->element);
        tree->left = delete_node(tree->left, element);

        if ((get_tree_height(tree->left) - get_tree_height(tree->right)) == 2)
        {
            if (tree->left->element > element)
            {
                tree = single_rotate(tree, 0);
            }
            else
            {
                tree = double_rotate(tree, 1);
            }
        }
    }
    else if (element > tree->element)
    {
        //printf("element %d > tree->element %d\n", element, tree->element);
        tree->right = delete_node(tree->right, element);

        if ((get_tree_height(tree->right) - get_tree_height(tree->left)) == 2)
        {
            if (tree->right->element < element)
            {
                tree = single_rotate(tree, 1);
            }
            else
            {
                tree = double_rotate(tree, 0);
            }
        }
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
            printf("delete element %d success\n", tree_tmp->element);

        }
    }

    if (tree)
    tree->height = get_max_tree_height(tree) + 1;

    return tree;
}

int main(void)
{
    struct AvlTree tree;
    struct AvlTree *tmp_node = NULL;

    int num[10] = {30, 4, 31, 10, 18, 16, 28, 15, 12, 14};
    int i;

    tree.element = 5;
    tree.left = NULL;
    tree.right = NULL;

    tmp_node = &tree;

    printf("root element : %d\n", tree.element);
    for (i = 0; i < 10; i++)
    {      
        tmp_node = insert_node(tmp_node, num[i]);
        printf("\n");
    }

    printf_tree_inorder_traversal(tmp_node);
    printf("\n");

    delete_node(tmp_node, 18);

    printf_tree_inorder_traversal(tmp_node);
    printf("\n");

    return 0;   
}
