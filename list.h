#ifndef _LIST_H_
#define _LIST_H_

typedef struct _tagListNode
{
	void* data;
	struct _tagListNode* next;
}LIST_NODE;

typedef struct _tagList
{
	LIST_NODE* head;
	unsigned int size;
}LIST;

LIST* new_list();
void delete_list(LIST* p_list);
void list_push(LIST* p_list, void* data);
void list_erase(LIST* p_list, void* data);
void* list_pop(LIST* p_list);

#endif