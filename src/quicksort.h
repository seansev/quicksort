#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

/**
 * int_cmp() - comparison function for integers
 * @a: first int
 * @b: second int
 *
 * Return:
 *             0 if the integers are equal.
 *             1 if the first integer is greater.
 *             -1 if the second integer is greater.
 */
int int_cmp(const void *a, const void *b);

/**
 * dbl_cmp() - comparison function for doubles
 * @a: first double
 * @b: second double
 *
 * Return:
 *             0 if the doubles are equal.
 *             1 if the first double is greater.
 *             -1 if the second double is greater.
 */
int dbl_cmp(const void *a, const void *b);

/**
 * str_cmp() - comparison function for strings
 * @a: first string
 * @b: second string
 *
 * Uses strcmp logic internally.
 *
 * Return:
 *             0 if the strings are equal.
 *             1 if the first string is greater.
 *             -1 if the second string is greater.
 */
int str_cmp(const void *a, const void *b);

/**
 * quicksort() - sort an array
 * @array: the array to sort
 * @len: the length of the array
 * @elem_sz: the size of each element
 * @cmp: the comparison function to use for sorting
 *
 * Calls quicksort_helper with left = 0 and right = (len - 1).
 */
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*cmp) (const void*, const void*));

#endif
