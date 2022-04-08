#pragma once
using namespace std;
typedef  pair<int, int> edge;
static int partition(vector< pair<int, edge> > arr, int start, int end)
{

    int pivot = arr[start].first;

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i].first <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i].first <= pivot) {
            i++;
        }

        while (arr[j].first > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}
static void quickSort(vector< pair<int, edge> > arr, int start, int end)
{

    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}