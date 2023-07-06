// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>


// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i = 1; i < data.size(); i++){
        int key = data[i], j = i-1;
        for( ; j >= 0; j--){
            if(data[j] > key)
                data[j+1] = data[j];
            else    
                break;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high){
        int pivot = Partition(data, low, high);
        QuickSortSubVector(data, low, pivot-1);
        QuickSortSubVector(data, pivot+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    srand(time(0));
    int pivot = low + rand()%(high-low+1);

    std::swap(data[pivot], data[high]);
    int ptr = low;
    for(int i = low; i < high; i++){
        if(data[i] <= data[high]){
            std::swap(data[i], data[ptr]);
            ptr++;
        }
    }
    std::swap(data[ptr], data[high]);
    return ptr;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
        int mid = low + (high-low)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1, n2 = high - middle2 + 1;
    vector<int> arr1(n1, 0), arr2(n2, 0);
    for(int i = 0; i < n1; i++)
        arr1[i] = data[low+i];
    for(int j = 0; j < n2; j++)
        arr2[j] = data[middle2+j];
    arr1.push_back(INT32_MAX);
    arr2.push_back(INT32_MAX);
    int ptr1 = 0, ptr2 = 0;
    for(int i = low; i <= high; i++){
        if(arr1[ptr1] <= arr2[ptr2]){
            data[i] = arr1[ptr1];
            ptr1++;
        }
        else{
            data[i] = arr2[ptr2];
            ptr2++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
    
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code heres
    int left = 2*root+1;
    int right = 2*root+2;
    int max = root;
    if(left <= heapSize-1 && data[left] > data[root])
        max = left;
    if(right <= heapSize-1 && data[right] > data[max])
        max = right;
    if(max != root){
        std::swap(data[max], data[root]);
        MaxHeapify(data, max);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = data.size()/2; i >= 0; i--)
        MaxHeapify(data, i);
}
