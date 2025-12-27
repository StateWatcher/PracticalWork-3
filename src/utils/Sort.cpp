#include "Sort.h"
#include <algorithm>

void shakerSort(int* start, int* end)
{
    int* left = start;
    int* right = end - 1;
    
    while (left <= right)
    {
        for (int* i = left; i < right; ++i)
        {
            if (*i > *(i + 1))
            {
                std::swap(*i, *(i + 1));
            }
        }
        --right;
        
        for (int* i = right; i > left; --i)
        {
            if (*i < *(i - 1))
            {
                std::swap(*i, *(i - 1));
            }
        }
        ++left;
    }
}

void insertionSort(int* start, int* end)
{
    for (int* i = start + 1; i < end; ++i)
    {
        int key = *i;
        int* j = i - 1;
        
        while (j >= start && *j > key)
        {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
    }
}

void combSort(int* start, int* end)
{
    const double shrink = 1.247;
    int gap = end - start;
    bool swapped = true;
    
    while (gap > 1 || swapped)
    {
        gap = static_cast<int>(gap / shrink);
        if (gap < 1) gap = 1;
        
        swapped = false;
        for (int* i = start; i + gap < end; ++i)
        {
            if (*i > *(i + gap))
            {
                std::swap(*i, *(i + gap));
                swapped = true;
            }
        }
    }
}

void quickSortHelper(int* begin, int* end)
{
    if (begin >= end) return;
    
    int* left = begin;
    int* right = end;
    int mid = *(begin + (end - begin) / 2);
    
    while (left <= right)
    {
        while (*left < mid) ++left;
        while (*right > mid) --right;
        
        if (left <= right)
        {
            std::swap(*left, *right);
            ++left;
            --right;
        }
    }
    
    if (begin < right) quickSortHelper(begin, right);
    if (left < end) quickSortHelper(left, end);
}

void quickSort(int* start, int* end)
{
    if (start < end)
    {
        quickSortHelper(start, end - 1);
    }
}