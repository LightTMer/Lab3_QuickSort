#pragma once
#include <utility>
#include <algorithm>

constexpr int InsertLimit = 15;

template<typename T>
bool comp(const T& a, const T& b) {
    return a < b;
}

template<typename T, typename Compare>
T& Median(T* arr, int low, int high, Compare comp) {
    int mid = low + ((high - low) >> 1);

    if (comp(arr[mid], arr[low])) {
        T temp = std::move(arr[low]);
        arr[low] = std::move(arr[mid]);
        arr[mid] = std::move(temp);
    }
    if (comp(arr[high], arr[low])) {
        T temp = std::move(arr[low]);
        arr[low] = std::move(arr[high]);
        arr[high] = std::move(temp);
    }
    if (comp(arr[high], arr[mid])) {
        T temp = std::move(arr[mid]);
        arr[mid] = std::move(arr[high]);
        arr[high] = std::move(temp);
    }
    return arr[mid];
}

template <typename T, typename Compare>
int Partition(T* arr, int low, int high, Compare comp) {
    T pivot = Median(arr, low, high, comp);
    int i = low;
    int j = high;

    while (true) {
        while (comp(arr[i], pivot)) i++;
        while (comp(pivot, arr[j])) j--;

        if (i >= j) return j;

        T temp = std::move(arr[i]);
        arr[i] = std::move(arr[j]);
        arr[j] = std::move(temp);
        i++;
        j--;
    }
}

template <typename T, typename Compare>
void InsertionSort(T* arr, int low, int high, Compare comp) {
    for (int i = low + 1; i <= high; i++) {
        T key = std::move(arr[i]);
        int j = i - 1;

        while (j >= low && comp(key, arr[j])) {
            arr[j + 1] = std::move(arr[j]);
            --j;
        }
        arr[j + 1] = std::move(key);
    }
}

template<typename T, typename Compare>
void Sort(T* first, T* last, Compare comp) {
    if (first == last) return;

    int low = 0;
    int high = static_cast<int>(last - first) - 1;

    while (low < high) {
        if ((high - low) + 1 < InsertLimit) {
            InsertionSort(first, low, high, comp);
            break;
        }

        int mid = Partition(first, low, high, comp);
        int left = mid - low + 1;
        int right = high - (mid + 1) + 1;

        if (left < right) {
            Sort(first + low, first + mid + 1, comp);
            low = mid + 1;
        }
        else {
            Sort(first + mid + 1, first + high + 1, comp);
            high = mid;
        }
    }
}