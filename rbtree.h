#ifndef _RBTREE_H_
#define _RBTREE_H_

#define LOG_DEBUG(format, ...) printf("[%s:%d] " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);

typedef enum _boolean
{
    FALSE = 0, 
    TRUE = 1
}BOOL;

typedef enum _color
{
	RED = 0,
	BLACK = 1
}COLOR;

typedef char KEY_TYPE;
typedef int (*COMPARE_FUNC)(KEY_TYPE a, KEY_TYPE b);
typedef void (*DATA_TO_STRING_FUNC)(void* data, char* str);
typedef void* (*STRING_TO_DATA_FUNC)(char* str);

typedef struct _tagRedBlackTreeNode
{
	KEY_TYPE key;
	void* data;
	COLOR color;
	struct _tagRedBlackTreeNode *left, *right, *parent;
}REA_BLACK_TREE_NODE;

typedef struct _tagRedBlackTree
{
	COMPARE_FUNC cmp_fn; 
	REA_BLACK_TREE_NODE *root;
	unsigned int size;
}REA_BLACK_TREE;

REA_BLACK_TREE* new_rbtree(COMPARE_FUNC cmp_fn);
void delete_rbtree(REA_BLACK_TREE* p_rbtree);

REA_BLACK_TREE_NODE* rbtree_search(REA_BLACK_TREE* p_rbtree, KEY_TYPE key);

REA_BLACK_TREE_NODE* rbtree_insert(REA_BLACK_TREE* p_rbtree, KEY_TYPE key, void* data);
void rbtree_erase(REA_BLACK_TREE* p_rbtree, KEY_TYPE key);

void dump_rbtree_to_file(REA_BLACK_TREE* p_rbtree, const char* file_path, DATA_TO_STRING_FUNC to_string);
REA_BLACK_TREE* load_rbtree_from_file(const char* file_path, STRING_TO_DATA_FUNC to_data);

#endif