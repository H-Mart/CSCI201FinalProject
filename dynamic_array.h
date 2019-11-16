#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class DynamicArray {
   private:
    T* array;
    size_t curEnd;
    size_t allocated;
    void resize(size_t const newSize);

   public:
    DynamicArray();
    DynamicArray(size_t const initialSize);
    ~DynamicArray();
    void push(T val);
    T pop();
    T last();
    int length();
    int elementsAllocated();
    T operator[](int i) const;
    T& operator[](int i);
};

template <typename T>
void DynamicArray<T>::resize(size_t const newSize) {
    std::cout << "resizing to: " << newSize << std::endl;
    T* newArray = new T[newSize];
    std::copy(array, array + curEnd, newArray);
    delete[] array;
    array = newArray;
    allocated = newSize;
}

template <typename T>
DynamicArray<T>::DynamicArray() {
    array = new T[1];
    curEnd = 0;
    allocated = 1;
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t const initialSize) {
    array = new T[initialSize];
    curEnd = 0;
    allocated = initialSize;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] array;
}

template <typename T>
void DynamicArray<T>::push(T val) {
    if (curEnd < allocated) {
        array[curEnd] = val;
        curEnd++;
    } else {
        resize(allocated * 2);
        array[curEnd++] = val;
    }
}

template <typename T>
T DynamicArray<T>::pop() {
    T val = array[curEnd - 1];
    --curEnd;
    if (curEnd < allocated / 2) {  // todo maybe

        resize(allocated / 2);
    }
    return val;
}

template <typename T>
T DynamicArray<T>::last() {
    return array[curEnd - 1];
}
template <typename T>
int DynamicArray<T>::length() {
    return curEnd;
}

template <typename T>
int DynamicArray<T>::elementsAllocated() {
    return allocated;
}

template <typename T>
T DynamicArray<T>::operator[](int i) const {
    return array[i];
}

template <typename T>
T& DynamicArray<T>::operator[](int i) { return array[i]; }

#endif
