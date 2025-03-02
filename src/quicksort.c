#include <stdio.h>
#include <string.h>
#include "quicksort.h"

static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/**
 * swap() - swaps the values at two addresses
 * @a: first address
 * @b: second address
 * @size: the length in bytes to swap
 */
static void swap(void *a, void *b, size_t size) {
	char temp = '\0';
	char *x = (char *)a;
	char *y = (char *)b;
	for (size_t i = 0; i < size; i++) {
		temp = *x;
		*x = *y;
		*y = temp;
	}
}

/**
 * lomuto() - partitions an array around a pivot
 * @array: the array to partition
 * @left: left bound index
 * @right: right bound index
 * @elem_sz: the size of each array element
 * @cmp: comparison function to use
 *
 * The pivot is placed into the correct index of the array in sorted order. All
 * elements less than the pivot are moved to its left, all elements greater to
 * its right.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
	int s = left;
	for (int i = left+1; i <= right; i++) {
		if (cmp(array[i], array[left]) < 0) {
			s += 1;
			swap(array[s], array[i], elem_sz);
		}
	}
	swap(array[left], array[s], elem_sz);
	return s;
}

/**
 * quicksort_helper() - recursively sorts with lomuto partitioning
 * @array: the array to sort
 * @left: left bound index
 * @right: right bound index
 * @elem_sz: the size of each array element
 * @cmp: comparison function to use
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
	if (left < right) {
		int s = lomuto(array, left, right, elem_sz, cmp);
		quicksort_helper(array, left, s-1, elem_sz, cmp);
		quicksort_helper(array, s+1, right, elem_sz, cmp);
	}
}
