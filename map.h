#ifndef _MAP_H_
#define _MAP_H_

#include "rbtree.h"

typedef REA_BLACK_TREE MAP;

MAP* new_map(COMPARE_FUNC cmp_fn);

void map_insert(MAP* p_map, KEY_TYPE key, void* value);
void map_erase(MAP* p_map, KEY_TYPE key);
void* map_get(MAP* p_map, KEY_TYPE key);
void delete_map(MAP* p_map);

#endif