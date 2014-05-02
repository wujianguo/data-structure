#! /bin/bash
gcc main.c rbtree.c list.c
if [ $? = 0 ];then
	./a.out
fi