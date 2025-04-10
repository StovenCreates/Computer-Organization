#include "Version.h"
#if !defined(MYMAIN)
#warning("using solution delete_table")
#else
#warning("using my delete_table.c")

#include <stdlib.h>
#include "node.h"

void delete_table(node **htable, unsigned long tabsz) {
	// TODO: walk through the chains in table
	//
	// TODO: free all the memory associated to each node in each chain
	//
	// TODO: free the entire table
	//
	for (unsigned long i = 0; i < tabsz; i++) {
		node *current = htable[i];
		while (current != NULL) {
			node *temp = current;
			current = current->next;
			free(temp->id);
			free(temp);
		}
	}
	free(htable);
}
#endif
