#include "Version.h"
#if !defined(MYLOADTABLE)
#warning("using solution load_table")
#else
#warning("using my load_table.c")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define MAX_LINELEN 100 
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

int load_table(node **htable, unsigned long int tabsz, char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
		return -1;
	}
	
	// TODO: loop through the file and read one line at a time using fgets
	// see manual page for fgets for information on parameters
	char buf[MAX_LINELEN + 1]; // input buffer for fgets
	while (fgets(buf, MAX_LINELEN + 1, fp) == buf) {
		// TODO: for each line, use strtok to break it into columns
		// (convert the second, third, and fourth columns to unsigned longs)
		char *id = strtok(buf, ",");
		char *heightstr = strtok(NULL, ",");
		char *xstr = strtok(NULL, ",");
		char *ystr = strtok(NULL, ",");

		unsigned long height = strtoul(heightstr, NULL, 10);
		unsigned long xcoord = strtoul(xstr, NULL, 10);
		unsigned long ycoord = strtoul(ystr, NULL, 10);

		// TODO: get the corresponding chain for this entry
		unsigned long hash_value = hash(id) % tabsz;
		
		// TODO: check that the node doesn't already exist in table
		node *existing_node = node_lookup(htable[hash_value], id);
		if (existing_node != NULL) {
			fprintf(stderr, DUPLICATE_ID_MSG, id);
			continue;
		}

		// TODO: add non-duplicate node to the front of its chain
		htable[hash_value] = insert_node(id, height, xcoord, ycoord, htable[hash_value]);
		if (htable[hash_value] == NULL) {
			fprintf(stderr, INSERTION_ERROR_MSG, id);
			fclose(fp);
			return -1;
		}


	}

	fclose(fp);
	return 0;
}
#endif
