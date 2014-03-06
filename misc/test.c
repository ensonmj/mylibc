#include <stdio.h>
#include "misc.h"
#include "sort.h"

int main(int argc, char *argv[])
{
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int cnt = sizeof(arr)/sizeof(int);
    printf("orig array:");
    print_arr(arr, cnt);

    heap_sort_ascend(arr, sizeof(arr)/sizeof(int));
    printf("heap ascend sort:");
    print_arr(arr, sizeof(arr)/sizeof(int));

    int arr1[] = {49, 38, 65, 97, 76, 13, 27, 49};
    heap_sort_descend(arr1, sizeof(arr1)/sizeof(int));
    printf("heap descend sort:");
    print_arr(arr1, sizeof(arr1)/sizeof(int));

    //getchar();

    return 0;
}
