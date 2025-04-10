#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * Assignment-2
 * Username: stc008 (fill out your username here)
 * Class: UCSD CSE30-S224
 */

#define USAGE_STRING "usage: %s -c incols [-s] col1 [col2 ...]\n"
#define INCOLS_INVALID_RANGE "Err: incols must be >= 1 and <= %d\n"
#define INCOLS_MISSING "Err: input columns required\n"
#define OUTCOLS_MISSING "Err: at least one output column must be provided\n"
#define COL_OUT_OF_RANGE "Err: output column number must be >= 1 and <= %d\n"
#define TOO_MANY_COLS_ERR "Err: too many columns in row. Dropping row...\n"
#define TOO_FEW_COLS_ERR "Err: too few columns in row. Dropping row...\n"
#define STATS_STRING "%d valid lines\n" \
                    "%d dropped lines\n" \
                    "longest field = %d characters\n"
#define MAX_COLS 100

void usage(char *argv0) {
    fprintf(stderr, USAGE_STRING, argv0);
}

int main(int argc, char **argv) {
    int incols = 0; // number of columns in input file
    int outcols = 0; // number of columns in output

    char *linebuf = NULL; // buffer for reading in a single line
    char **colptrs = NULL; // array of pointers to start of each col
    int *outcols_buf = NULL; // buffer for list of output cols (1-indexed)

    unsigned int linecnt = 0; // number of valid lines
    unsigned int dropcnt = 0; // number of invalid (dropped) lines

    // longest field length (does not include whitespace)
    unsigned int longest_field = 0;

    int stats_flag = 0; // was -s provided
    int c_flag = 0; // was -c provided

    int c; // for reading options with getopt
    while ((c = getopt(argc, argv, "c:s")) != -1) {
        switch (c) {
            case 'c':
                // parse incols and check for err
                // make sure that incols is in the valid range 
                // (see MAX_COLS)
                // if it is not, print INCOLS_INVALID_RANGE to stderr 
                // and return failure
		incols = atoi(optarg);
		c_flag = 1;
		if (incols < 1 || incols > MAX_COLS) {
			fprintf(stderr, INCOLS_INVALID_RANGE, MAX_COLS);
			return EXIT_FAILURE;
		}
                break;
            
            case 's':
                // example for s flag
                stats_flag = 1;
                break;
            default:
                // if we got an invalid argument
                usage(*argv);
                return EXIT_FAILURE;
        }
    }
    // check if incols was provided
    // if it wasn't print INCOLS_MISSING to stderr,
    // call usage() with the first element of argv, and return failure
    if (!c_flag) {
	    fprintf(stderr, INCOLS_MISSING);
	    usage(*(argv));
	    return EXIT_FAILURE;
    }

    // set outcols and check that it's at least 1
    // if no output columns are given, print MISSING_OUTCOL to stderr,
    // call usage() with the first element of argv, and return failure
    outcols = argc - optind;
    if (outcols < 1) {
	    fprintf(stderr, OUTCOLS_MISSING);
	    usage(*(argv));
	    return EXIT_FAILURE;
    }

    // allocate memory for outcols_buf
    // make sure to check that malloc didn't fail
    // (malloc returns null on failure)
   
    
    outcols_buf = malloc(outcols * sizeof(int));
    if (!outcols_buf) {
        fprintf(stderr, "malloc failure\n");
        return EXIT_FAILURE;
    }
    

    // parse the rest of argv and fill in outcols_buf
    // make sure to check that the argument is in the correct range
    // of columns
    // if it is not, print COL_OUT_OF_RANGE to stderr and return failure
    // you can use atoi for conversion, and you can assume that all
    // provided arguments will be proper integers
    for (int i = 0; i < outcols; i++) {
	    int col = atoi(*(argv + optind + i));
	    if (col < 1 || col > incols) {
		    fprintf(stderr, COL_OUT_OF_RANGE, incols);
		    free(outcols_buf);
		    return EXIT_FAILURE;
	    }
	    *(outcols_buf + i) = col - 1;
    }

    // allocate space for colptrs using incols
    // if malloc fails, print and return failure
    
    colptrs = malloc(incols * sizeof(char *));
    if (!colptrs) {
        fprintf(stderr, "malloc failure\n");
        free(outcols_buf); // avoid memory leaks
        return EXIT_FAILURE;
    }
    

    // read in the input lines using getline
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&linebuf, &len, stdin)) != -1) {
        int col_count = 0;
	char *ptr = linebuf;
	char *start = ptr;

	for (int i = 0; i < incols; i++) {
		while (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' && *ptr != '\0') {
			ptr++;
		}
		if (i < incols - 1) {
			*ptr++ = '\0';
			*(colptrs + i) = start;
			while (*ptr == ' ' || *ptr == '\t') {
				ptr++;
			}
			start = ptr;
		}
		else {
			*(colptrs + i) = start;
		}
		col_count++;
	}

	char *last_col = *(colptrs + incols - 1);
	while (*last_col != '\0') {
		if (*last_col == '\n') {
			*last_col = '\0';
			break;
		}
		last_col++;
	}

	if (col_count < incols) {
		fprintf(stderr, TOO_FEW_COLS_ERR);
		dropcnt++;
		continue;
	}
	else if (col_count > incols) {
		fprintf(stderr, TOO_MANY_COLS_ERR);
		dropcnt++;
		continue;
	}
	linecnt++;

	for (int i = 0; i < outcols; i++) {
		if (i > 0) {
			printf(" ");
		}
		printf("%s", *(colptrs + *(outcols_buf + i)));
	}
	printf("\n");

	for (int i = 0; i < incols; i++) {
		unsigned int field_len = 0;
		char *temp = *(colptrs + i);
		while (*temp != '\0') {
			field_len++;
			temp++;
		}
		if (field_len > longest_field) {
			longest_field = field_len;
		}
	}

    }

    // print stats **to stderr** if -s provided
    //
    if (stats_flag) {
	    fprintf(stderr, STATS_STRING, linecnt, dropcnt, longest_field);
    }


    // free any allocated memory (outcols_buf, colptrs, and linebuf)
    // before returning
    free(linebuf);
    free(colptrs);
    free(outcols_buf);

    return EXIT_SUCCESS;
}
