#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

int main(int argc, char **argv) {
	
	const char *usage = "Usage: ./sort [-i|-d] [filename]\n"
		"   -i: Specifies the input contains ints.\n"
		"   -d: Specifies the input contains doubles.\n"
		"   filename: The file to sort. If no file is supplied, input is read from\n"
		"             stdin.\n"
		"   No flags defaults to sorting strings.\n";
	
	char buffer[MAX_STRLEN+2];
	FILE *file = NULL;
	int length = 0;

	int opt;
	// MODE 1 = Integer, MODE 2 = Double, MODE 3 = String
	int mode = 0;
	while ((opt = getopt(argc, argv, ":id")) != -1) {
		switch (opt) {
			case 'i':
				if (mode) goto MULTIPLE_FLAGS;
				mode = 1;
				break;
			case 'd':
				if (mode) goto MULTIPLE_FLAGS;
				mode = 2;
				break;
			case '?':
				goto INVALID_FLAG;
				break;
		}
	}
	if (!mode) mode = 3;
	
	if (argc - optind > 1) {
		goto MULTIPLE_ARGS;
	} else if (argc - optind == 1) {
		file = fopen(argv[optind], "r");
		if (file == NULL) goto NOT_FOUND;
	} else {
		file = stdin;
	}
	
	if (mode == 1) {
		int *array = (int *)malloc(MAX_ELEMENTS * sizeof(int));
		if (array == NULL) goto MALLOC_FAIL;
		while (fgets(buffer, MAX_STRLEN, file) != NULL) {
			array[length] = atoi(buffer);
			length++;
		}
		quicksort(array, length, sizeof(int), int_cmp);
		for (int i = 0; i < length; i++) {
			printf("%d\n", array[i]);
		}
		free(array);
	} else if (mode == 2) {
		double *array = (double *)malloc(MAX_ELEMENTS * sizeof(double));
		if (array == NULL) goto MALLOC_FAIL;
		while (fgets(buffer, MAX_STRLEN, file) != NULL) {
			array[length] = atof(buffer);
			length++;
		}
		quicksort(array, length, sizeof(double), dbl_cmp);
		for (int i = 0; i < length; i++) {
			printf("%f\n", array[i]);
		}
		free(array);
	} else if (mode == 3) {
		size_t size = MAX_STRLEN + 2;
		char *array = (char *)malloc(MAX_ELEMENTS * size);
		if (array == NULL) goto MALLOC_FAIL;
		while (fgets(buffer, size, file) != NULL) {
			strcpy(array + size*length, buffer);
			length++;
		}
		quicksort(array, length, size, str_cmp);
		for (int i = 0; i < length; i++) {
			printf("%s", array + size*i);
		}
		free(array);
	}

	fclose(file);

	return EXIT_SUCCESS;

MULTIPLE_FLAGS:
	fprintf(stderr, "Error: Too many flags specified.\n");
	return EXIT_FAILURE;

INVALID_FLAG:
	fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
	fprintf(stderr, "%s", usage);
	return EXIT_FAILURE;

MULTIPLE_ARGS:
	fprintf(stderr, "Error: Too many files specified.\n");
	return EXIT_FAILURE;

NOT_FOUND:
	fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno));
	return EXIT_FAILURE;

MALLOC_FAIL:
	fprintf(stderr, "Error: malloc failed. %s.\n", strerror(errno));
	return EXIT_FAILURE;
}
