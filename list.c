#include <stdlib.h>
#include <string.h>
#include "list.h"

LIST* new_list()
{
	LIST* p_list = (LIST*)malloc(sizeof(LIST));
	memset(p_list, 0, sizeof(LIST));
	return p_list;
}

void delete_list(LIST* p_list)
{
	LIST_NODE* delete_node = p_list->head;
	LIST_NODE* next = NULL;
	while(delete_node != NULL)
	{
		next = delete_node->next;
		free(delete_node);
		delete_node = next;
	}
	free(p_list);
}

void list_push(LIST* p_list, void* data)
{
	LIST_NODE* p_new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE));
	memset(p_new_node, 0, sizeof(LIST_NODE));
	p_new_node->data = data;
	if(p_list->head == NULL)
	{
		p_list->head = p_new_node;
	}
	else
	{
		LIST_NODE* node = p_list->head;
		while(node->next != NULL)
			node = node->next;
		node->next = p_new_node;
	}
	p_list->size++;
}

void* list_pop(LIST* p_list)
{
	void* data = p_list->head->data;
	list_erase(p_list, data);
	return data;
}

void list_erase(LIST* p_list, void* data)
{
	LIST_NODE** curr = &p_list->head;
    for(; *curr; )
    {
        LIST_NODE* entry = *curr;
        if((*curr)->data == data)
        {
            *curr = entry->next;
            free(entry);
            p_list->size--;
        }
        else
            curr = &entry->next;
    }
}