#include <stdio.h>
#include "misc.h"

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_arr(int arr[], int len)
{
    for(int i=0; i<len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
