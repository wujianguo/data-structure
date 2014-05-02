#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

REA_BLACK_TREE* new_rbtree(COMPARE_FUNC cmp_fn)
{
	REA_BLACK_TREE* p_rbtree = (REA_BLACK_TREE*)malloc(sizeof(REA_BLACK_TREE));
	memset(p_rbtree, 0, sizeof(REA_BLACK_TREE));
	p_rbtree->cmp_fn = cmp_fn;
}

void delete_rbtree(REA_BLACK_TREE* p_rbtree)
{
	while(p_rbtree->size > 0)
		rbtree_erase(p_rbtree, p_rbtree->root->key);
	free(p_rbtree);
}

static BOOL searchBST(REA_BLACK_TREE_NODE* p_root, COMPARE_FUNC cmp_fn, KEY_TYPE key, REA_BLACK_TREE_NODE** pp_ret)
{
	if(p_root == NULL)		
	{
		return FALSE;
	}
	else if(cmp_fn(key, p_root->key) == 0)
	{
		*pp_ret = p_root;
		return TRUE;
	}
	else if(cmp_fn(key, p_root->key) < 0)
	{
		return searchBST(p_root->left, cmp_fn, key, pp_ret);
	}
	else
	{
		return searchBST(p_root->right, cmp_fn, key, pp_ret);
	}
}

REA_BLACK_TREE_NODE* rbtree_search(REA_BLACK_TREE* p_rbtree, KEY_TYPE key)
{
	if(p_rbtree == NULL)
		return NULL;
	if(p_rbtree->root == NULL)
		return NULL;
	REA_BLACK_TREE_NODE* p_node = NULL;
	BOOL b = searchBST(p_rbtree->root, p_rbtree->cmp_fn, key, &p_node);
	return b ? p_node : NULL;
}

static REA_BLACK_TREE_NODE* new_rbtree_node(KEY_TYPE key)
{
	REA_BLACK_TREE_NODE* p_node = NULL;
	p_node = (REA_BLACK_TREE_NODE*)malloc(sizeof(REA_BLACK_TREE_NODE));
	memset(p_node, 0, sizeof(REA_BLACK_TREE_NODE));
	p_node->key = key;
	p_node = NULL;
}

static BOOL insertBST(REA_BLACK_TREE_NODE** pp_root, COMPARE_FUNC cmp_fn, KEY_TYPE key, REA_BLACK_TREE_NODE** pp_ret)
{
	if(*pp_root == NULL)
	{
		*pp_root = new_rbtree_node(key);
		*pp_ret = *pp_root;
		return TRUE;
	}
	else if(cmp_fn(key, (*pp_root)->key) == 0)
	{
		*pp_ret = *pp_root;
		return FALSE;
	}
	else if(cmp_fn(key, (*pp_root)->key) < 0)
	{
		if((*pp_root)->left == NULL)
		{
			(*pp_root)->left = new_rbtree_node(key);
			(*pp_root)->left->parent = *pp_root;
			*pp_ret = (*pp_root)->left;
			return TRUE;
		}
		return insertBST(&(*pp_root)->left, cmp_fn, key, pp_ret);
	}
	else
	{
		if((*pp_root)->right == NULL)
		{
			(*pp_root)->right = new_rbtree_node(key);
			(*pp_root)->right->parent = *pp_root;
			*pp_ret = (*pp_root)->right;
			return TRUE;
		}
		return insertBST(&(*pp_root)->right, cmp_fn, key, pp_ret);
	}
}

static REA_BLACK_TREE_NODE* grandparent(REA_BLACK_TREE_NODE* p_node)
{
	return p_node->parent->parent;
}

static REA_BLACK_TREE_NODE* uncle(REA_BLACK_TREE_NODE* p_node)
{
	if(p_node->parent == grandparent(p_node)->left)
		return grandparent(p_node)->right;
	else
		return grandparent(p_node)->left;
}

static void color_rbtree_case1(REA_BLACK_TREE_NODE* p_node)
{
	p_node->color = BLACK;
}

static void color_rbtree_case2(REA_BLACK_TREE_NODE* p_node)
{
	p_node->color = RED;
}

static void rotate_left(REA_BLACK_TREE_NODE* p_node)
{
	REA_BLACK_TREE_NODE* p_grand = grandparent(p_node);

	p_grand->left = p_node;

	p_node->parent->parent = p_node;
	p_node->parent->right = p_node->left;
	if(p_node->left)
		p_node->left->parent = p_node->parent;

	p_node->left = p_node->parent;
	p_node->parent = p_grand;
}

static void rotate_right(REA_BLACK_TREE_NODE* p_node)
{
	REA_BLACK_TREE_NODE* p_grand = grandparent(p_node);

	p_grand->right = p_node;

	p_node->parent->parent = p_node;
	p_node->parent->left = p_node->right;
	if(p_node->right)
		p_node->right->parent = p_node->parent;

	p_node->right = p_node->parent;
	p_node->parent = p_grand;
}

static void color_rbtree(REA_BLACK_TREE_NODE* p_node)
{
	if(p_node->parent == NULL)
		p_node->color = BLACK;
	else if(p_node->parent->color = BLACK)
		p_node->color = RED;
	else if(uncle(p_node) != NULL && uncle(p_node)->color == RED)
	{
		p_node->parent->color = BLACK;
		uncle(p_node)->color = BLACK;
		grandparent(p_node)->color = RED;	
		color_rbtree(grandparent(p_node));
	}
	else if(p_node == p_node->parent->right && p_node->parent == grandparent(p_node)->left)
	{
		rotate_left(p_node->parent);
		p_node = p_node->left;
	}
	else if(p_node == p_node->parent->left && p_node->parent == grandparent(p_node)->right)
	{
		rotate_right(p_node->parent);
		p_node = p_node->right;
	}
	else
	{
		p_node->parent->color = BLACK;
		grandparent(p_node)->color = RED;
		if(p_node == p_node->parent->left && p_node->parent == grandparent(p_node)->left)
			rotate_right(grandparent(p_node));
		else
			rotate_left(grandparent(p_node));
	}
}

REA_BLACK_TREE_NODE* rbtree_insert(REA_BLACK_TREE* p_rbtree, KEY_TYPE key, void* data)
{
	REA_BLACK_TREE_NODE* p_node = NULL;
	BOOL b = insertBST(&p_rbtree->root, p_rbtree->cmp_fn, key, &p_node);
	p_node->data = data;
	if(b)
	{
		color_rbtree(p_node);
		p_rbtree->size++;
	}
	return p_node;
}

static void eraseBST_ex(REA_BLACK_TREE_NODE** pp_node)
{
	if((*pp_node)->left == NULL && (*pp_node)->right == NULL)
	{
		free(*pp_node);
		*pp_node = NULL;
	}
	else if((*pp_node)->left == NULL)
	{
		REA_BLACK_TREE_NODE* right = (*pp_node)->right;
		if(right)
			right->parent = (*pp_node)->parent;
		free(*pp_node);
		*pp_node = right;
	}
	else if((*pp_node)->right == NULL)
	{
		REA_BLACK_TREE_NODE* left = (*pp_node)->left;
		if(left)
			left->parent = (*pp_node)->parent;
		free(*pp_node);
		*pp_node = left;
	}
	else
	{
		REA_BLACK_TREE_NODE** pp_right = &(*pp_node)->right;
		while((*pp_right)->left != NULL)
			pp_right = &(*pp_right)->left;
		(*pp_node)->key = (*pp_right)->key;
		(*pp_node)->data = (*pp_right)->data;
		REA_BLACK_TREE_NODE* right = (*pp_right)->right;
		if(right)
			right->parent = (*pp_right)->parent;
		free(*pp_right);
		*pp_right = right;
	}
}

static BOOL eraseBST(REA_BLACK_TREE_NODE** pp_root, COMPARE_FUNC cmp_fn, KEY_TYPE key)
{
	if(*pp_root == NULL)
	{
		return FALSE;
	}
	else if(cmp_fn(key, (*pp_root)->key) == 0)
	{
		eraseBST_ex(pp_root);
		return TRUE;
	}
	else if(cmp_fn(key, (*pp_root)->key) < 0)
	{
		return eraseBST(&(*pp_root)->left, cmp_fn, key);
	}
	else
	{
		return eraseBST(&(*pp_root)->right, cmp_fn, key);
	}
}

void rbtree_erase(REA_BLACK_TREE* p_rbtree, KEY_TYPE key)
{
	BOOL b = eraseBST(&p_rbtree->root, p_rbtree->cmp_fn, key);
	if(b)
		p_rbtree->size--;
}

void dump_rbtree_to_file(REA_BLACK_TREE* p_rbtree, const char* file_path, DATA_TO_STRING_FUNC to_string)
{

}

REA_BLACK_TREE* load_rbtree_from_file(const char* file_path, STRING_TO_DATA_FUNC to_data)
{

}