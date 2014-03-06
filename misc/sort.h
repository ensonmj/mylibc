#ifndef __MYLIBC_SORT_H__
#define __MYLIBC_SORT_H__

void heap_shift_up(int *arr, int low, int high);
void heap_sort_ascend(int *arr, int len);
void heap_shift_down(int *arr, int low, int high);
void heap_sort_descend(int *arr, int len);

#endif
