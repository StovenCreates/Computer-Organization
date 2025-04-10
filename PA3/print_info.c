#include "Version.h"

#if !defined(MYPRINTINFO)
#warning("using solution print_info")
#else
#warning("using my print_info.c")

#include <stdio.h>
#include <limits.h>
#include "node.h"

#define TABSZ_MSG "Table size: %lu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"


void print_info(node **htable, unsigned long tabsz) {
	// TODO: walk down the indices of the htable
	// iterate through each chain and update statistics
	// print out statistics at end
	//
	// NOTE: all your statistics variables should be of type
	// unsigned long
	//
	// NOTE: you may use ULONG_MAX if you want
	// (maximum value for unsigned long int)
	
	unsigned long total_entries = 0;
	unsigned long longest_chain = 0;
	unsigned long shortest_chain = ULONG_MAX;
	unsigned long empty_buckets = 0;

	for (unsigned long i = 0; i < tabsz; i++) {
		node *current = htable[i];
		unsigned long chain_length = 0;

		while (current != NULL) {
			chain_length++;
			total_entries++;
			current = current->next;
		}

		if (chain_length == 0) {
			empty_buckets++;
		}
		else {
			if (chain_length > longest_chain) {
				longest_chain = chain_length;
			}
			if (chain_length < shortest_chain) {
				shortest_chain = chain_length;
			}
		}
	}

	if (total_entries == 0) {
		shortest_chain = 0;
	}

	printf(TABSZ_MSG, tabsz);
	printf(TOTAL_ENTRIES_MSG, total_entries);
	printf(LONGEST_MSG, longest_chain);
	printf(SHORTEST_MSG, shortest_chain);
	printf(EMPTY_MSG, empty_buckets);
}
#endif
