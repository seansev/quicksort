#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to type (char *) and works with them as char pointers
 * for the remainder of the function. Swaps one byte at a time, until all 'size'
 * bytes have been swapped. For example, if ints are passed in, size will be 4
 * and this function will swap 4 bytes starting at a and b pointers.
 */
static void swap(void *a, void *b, size_t size) {
	if (a == NULL || b == NULL) return;
	unsigned char temp;
	unsigned char *x = (unsigned char *)a;
	unsigned char *y = (unsigned char *)b;
	for (size_t i = 0; i < size; i++) {
		temp = x[i];
		x[i] = y[i];
		y[i] = temp;
	}
}

/**
 * Partitions array around a pivot, utilizing the swap function. Each time the
 * function runs, the pivot is placed into the correct index of the array in
 * sorted order. All elements less than the pivot should be to its left, and all
 * elements greater than or equal to the pivot should be to its right.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
	if (array == NULL || cmp == NULL) return left;
	char *a = (char *)array;
	char *p = a + elem_sz*left;
	int s = left;
	for (int i = left+1; i <= right; i++) {
		if (cmp(a + elem_sz*i, p) < 0) {
			s += 1;
			swap(a + elem_sz*s, a + elem_sz*i, elem_sz);
		}
	}
	swap(p, a + elem_sz*s, elem_sz);
	return s;
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
	if (array == NULL || cmp == NULL) return;
	if (left < right) {
		int s = lomuto(array, left, right, elem_sz, cmp);
		quicksort_helper(array, left, s-1, elem_sz, cmp);
		quicksort_helper(array, s+1, right, elem_sz, cmp);
	}
}

// Exported Functions
int int_cmp(const void *a, const void *b) {
	if (a == NULL || b == NULL) return 0;
	int *x = (int *)a;
	int *y = (int *)b;
	return (*x > *y) - (*y > *x);
}

int dbl_cmp(const void *a, const void *b) {
	if (a == NULL || b == NULL) return 0;
	double *x = (double *)a;
	double *y = (double *)b;
	return (*x > *y) - (*y > *x);
}

int str_cmp(const void *a, const void *b) {
	if (a == NULL || b == NULL) return 0;
	char *x = (char *)a;
	char *y = (char *)b;
	return strcmp(x, y);
}

void quicksort(void *array, size_t len, size_t elem_sz,
		int (*cmp)(const void *, const void *)) {
	if (array == NULL || cmp == NULL) return;
	quicksort_helper(array, 0, len-1, elem_sz, cmp);
}
