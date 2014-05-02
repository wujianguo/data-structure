#include <stdio.h>
#include <time.h>
#include "rbtree.h"
#include "list.h"

int cmp_fun(KEY_TYPE a, KEY_TYPE b)
{
	return a - b;
}

void data_to_string(void* data, char* str)
{
	int d = (int)data;
	sprintf(str, "int:%d", d);
}

void* string_to_data(char* str)
{

}

void inorder_visit(REA_BLACK_TREE_NODE* p_node)
{
	if(p_node == NULL)
		return;
	LOG_DEBUG("key:%c", p_node->key);
	inorder_visit(p_node->left);
	inorder_visit(p_node->right);
}
// unsigned int rbtree_num(REA_BLACK_TREE_NODE* p_node);
void pre_visit(REA_BLACK_TREE_NODE* p_node)
{
	if(p_node == NULL)
		return;
	pre_visit(p_node->left);
	LOG_DEBUG("key:%c", p_node->key);
	// LOG_DEBUG(":%d", rbtree_num(p_node));
	pre_visit(p_node->right);
}

void post_visit(REA_BLACK_TREE_NODE* p_node)
{
	if(p_node == NULL)
		return;
	post_visit(p_node->right);
	LOG_DEBUG("key:%c", p_node->key);
	post_visit(p_node->left);
}

unsigned int rbtree_hight(REA_BLACK_TREE_NODE* p_node)
{
	unsigned int hight = 1;
	while(p_node->parent != NULL)
	{
		hight++;
		p_node = p_node->parent;
	}
	return hight;
}

unsigned int rbtree_num(REA_BLACK_TREE_NODE* p_node)
{
	LIST* p_list = new_list();
	list_push(p_list, p_node);
	unsigned int num = 0;
	while(p_list->size > 0)
	{
		REA_BLACK_TREE_NODE* p_node = list_pop(p_list);
		if(p_node)
		{
			num++;
			list_push(p_list, p_node->left);
			list_push(p_list, p_node->right);
		}
	}
	delete_list(p_list);
	return num;
}

unsigned int rbtree_left_num(REA_BLACK_TREE_NODE* p_node)
{
	if(p_node == NULL)
		return 0;
	if(p_node->parent == NULL)
		return rbtree_num(p_node);

	if(p_node == p_node->parent->left)
		return rbtree_left_num(p_node->parent->parent) - 2;
	if(p_node == p_node->parent->right)
		return rbtree_left_num(p_node->parent) + rbtree_left_num(p_node->left);
	return 0;
}

void print_tree_node(REA_BLACK_TREE_NODE* p_node, int offset)
{
	if(p_node != NULL)
	{
		offset = rbtree_left_num(p_node) - offset;
		int i;
		for(i=0; i<offset; ++i)
			printf("\t");

		if(p_node->left != NULL)
			printf("%c,", p_node->left->key);
		else
			printf("NULL,");

		// if(p_node->parent != NULL)
		// 	printf("%c,", p_node->parent->key);
		// else
		// 	printf("NULL,");

		printf("%c,", p_node->key);
		if(p_node->right != NULL)
			printf("%c,", p_node->right->key);
		else
			printf("NULL,");
		printf("%d,%d", p_node->color, offset);
		// printf("hight:%d\t\t", rbtree_hight(p_node));
		printf("\t\t\t");
	}
}

void print_tree(REA_BLACK_TREE_NODE* p_root)
{
	printf("*******************\n");
	LIST* p_list = new_list();
	list_push(p_list, p_root);
	unsigned int hight = 0;
	int offset = 0;
	BOOL b = FALSE;
	while(p_list->size > 0)
	{
		REA_BLACK_TREE_NODE* p_node = list_pop(p_list);
		if(p_node)
		{
			if(hight != rbtree_hight(p_node))
			{
				printf("\n");
				b = TRUE;
			}
			else
				b = FALSE;
			hight = rbtree_hight(p_node);
		}
		print_tree_node(p_node, offset);
		if(p_node)
		{
			list_push(p_list, p_node->left);
			list_push(p_list, p_node->right);
			offset = rbtree_left_num(p_node);
			if(b)
				offset = 0;
		}

	}
	printf("\n\n*******************\n");
	delete_list(p_list);
}

int main(int argc, char const *argv[])
{

	REA_BLACK_TREE* p_rbtree = NULL;
	p_rbtree = new_rbtree(cmp_fun);
	int i;
	for(i=0; i<10; i++)
	{
		int r = random()%26;
		char s = 'A'+r;
		rbtree_insert(p_rbtree, s, NULL);
	}
	
	// pre_visit(p_rbtree->root);
	// inorder_visit(p_rbtree->root);
	// post_visit(p_rbtree->root);
	print_tree(p_rbtree->root);
	// LOG_DEBUG("size:%d", p_rbtree->size)

	for(i=0; i<10; ++i)
	{
		// rbtree_erase(p_rbtree, i);
	}
	// inorder_visit(p_rbtree->root);
	// LOG_DEBUG("size:%d", p_rbtree->size)
	delete_rbtree(p_rbtree);
	p_rbtree = NULL;
	// LOG_DEBUG("OK");
	return 0;
}