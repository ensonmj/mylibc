#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "misc.h"

/**
 * @brief 不完全最大堆，只能确保最大的元素在堆顶
 *
 * @param arr
 * @param low 数组下标最小值
 * @param high 数组下标最大值
 */
void heap_shift_up(int *arr, int low, int high)
{
    if(arr == NULL || low == high)
        return;

    int tmp = arr[low];
    int i;
    for(i=2*low+1; i<=high; i=2*i+1) {
        if(i<high && arr[i] < arr[i+1])
            i++;

        if(tmp>=arr[i])
            break;

        arr[low] = arr[i];
        low = i;
    }
    arr[low] = tmp;
}

void heap_sort_ascend(int *arr, int len)
{
    for(int i=len/2-1; i>=0; i--) {
        heap_shift_up(arr, i, len-1);
    }

    //每次取出顶部最大的那个数放后面，再进行一次顶点调整
    for(int i=len-1; i>0; i--) {
        swap(&arr[0], &arr[i]);
        heap_shift_up(arr, 0, i-1);
    }
}

/**
 * @brief 不完全最小堆，只能确保最小的元素在堆顶
 *
 * @param arr
 * @param low 数组下标最小值
 * @param high 数组下标最大值
 */
void heap_shift_down(int *arr, int low, int high)
{
    if(arr == NULL || low == high)
        return;

    int tmp = arr[low];
    int i;
    for(i=2*low+1; i<=high; i=2*i+1) {
        if(i<high && arr[i] > arr[i+1])
            i++;

        if(tmp<=arr[i])
            break;

        arr[low] = arr[i];
        low = i;
    }
    arr[low] = tmp;
}

void heap_sort_descend(int *arr, int len)
{
    for(int i=len/2-1; i>=0; i--) {
        heap_shift_down(arr, i, len-1);
    }

    for(int i=len-1; i>0; i--) {
        swap(&arr[0], &arr[i]);
        heap_shift_down(arr, 0, i-1);
    }
}
