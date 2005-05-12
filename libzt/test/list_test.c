/*
 * Copyright (C) 2000-2005, Jason L. Shiffer <jshiffer@zerotao.com>.  All Rights Reserved.
 * See file COPYING for details.
 *
 * $Id$
 *
 */

/*
 * Description: 
 */
#include <stdlib.h>
#include <stdio.h>

#include <libzt/adt/zt_list.h>
#include "test.h"

int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#define VALUES_MAX 9

typedef struct list_elt list_elt;
struct list_elt {
	zt_list	  list;
	int	  value;
};


int
main(int argc, char *argv[])
{
	list_elt	* al;
	list_elt	* al2;
	zt_list		* tmp;
	zt_list		* tmp2;
	int		  i;
	int		  test_n = 1;
	
	zt_list(list1);
	zt_list(list2);

	TEST_N("zt_list", test_n, list1.prev == &list1);
	TEST_N("zt_list", test_n, list1.next == &list1);
	
	for(i=0; i < sizeof_array(values); i++){
		
		al = XCALLOC(list_elt, 1);
		al->value = values[i];
		
		zt_list_add(&list1, &al->list);

		al = XCALLOC(list_elt, 1);
		al->value = VALUES_MAX - values[i];
		
		zt_list_add(&list2, &al->list);
	}

	tmp2 = &list2;	
	zt_list_for_each(&list1, tmp) {
		tmp2 = zt_list_get_next(tmp2);
		
		al = zt_list_entry(tmp, list_elt, list);
		al2 = zt_list_entry(tmp2, list_elt, list);

		TEST_N("zt_list", test_n, al->value + al2->value == 9);
	}
	
	
	return 0;
}