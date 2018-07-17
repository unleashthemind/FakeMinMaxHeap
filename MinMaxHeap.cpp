// File: MinMaxHeap.cpp
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 4
// Fake MinMaxHeap Made with one min and one max heap and function pointers

#include "MinMaxHeap.h"
#ifndef MINMAXHEAP_C
#define MINMAXHEAP_C


template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
   m_size = 0;
   m_capacity = capacity;
   minHeap = new Heap(&comp1,m_capacity + 1);
   maxHeap = new Heap(&comp2,m_capacity + 1);
}

template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){

   m_size = other.m_size;
   m_capacity = other.m_capacity;
   minHeap = new Heap(other.minHeap);
   maxHeap = new Heap(other.maxHeap);
}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){
   delete minHeap;
   delete maxHeap;
}

template <typename T>
void MinMaxHeap<T>::insert(const T& data){
   if(m_size < m_capacity){
      minHeap->insert(data);
      maxHeap->insert(data);
      m_size++;
   } 
   else {
      throw std::out_of_range("Heap capacity met");
   }
}

template <typename T>

const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){
   delete minHeap;
   delete maxHeap;
   m_size = rhs.m_size;
   m_capacity = rhs.m_capacity;
   minHeap = new Heap(rhs.minHeap);
   maxHeap = new Heap(rhs.maxHeap);
}

template <typename T>
T MinMaxHeap<T>::deleteMin(){
   T min = minHeap->m_data[1];
   if(minHeap->deletion(1)){
   	//delete from maxHeap too
      for(int i = maxHeap->m_size;i > 0;i--){ //runs in logn because min value is always in the leaves
         if(min == maxHeap->m_data[i]){
            maxHeap->deletion(i);
            m_size--;
            return min;
         }
      }
   } 
   else {
      throw std::out_of_range("Heap empty");
   }
}

template <typename T>
T MinMaxHeap<T>::deleteMax(){
   T max = maxHeap->m_data[1];
   if(maxHeap->deletion(1)){
   	//delete from minHeap too
      for(int i = minHeap->m_size;i > 0;i--){ //runs in logn because max value is always in the leaves
         if(max == minHeap->m_data[i]){
            minHeap->deletion(i);
            m_size--;
            return max;
         }
      }
   } 
   else {
      throw std::out_of_range("Heap empty");
   }
}

template <typename T>
int MinMaxHeap<T>::size(){
   return m_size;
}

template <typename T>
void MinMaxHeap<T>::dump(){
   if(m_size > 0){
      std::cout << "... MinMaxHeap::dump() ..." << std::endl;
      std::cout << "------------Min Heap------------" << std::endl;
      minHeap->dump();
      std::cout << "------------Max Heap------------" << std::endl;
      maxHeap->dump();
   }
}

template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){
   data = minHeap->m_data[pos];
   for(int i = maxHeap->m_size;i > 0;i--){ //Runs O(n) unless pos = 1
      if(data == maxHeap->m_data[i]){
         index = i;
         return;
      }
   } 
}

template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){
   data = maxHeap->m_data[pos];
   for(int i = minHeap->m_size;i > 0;i--){ //Runs O(n) unless pos = 1
      if(data == minHeap->m_data[i]){
         index = i;
         return;
      }
   }
}

#endif
