
// File: MinMaxHeap.cpp
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 4
// Fake MinMaxHeap implementation

#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

#include <iostream>
#include <stdexcept>

template <typename T>
bool comp1(T a,T b) {
   return a < b;
}
template <typename T>
bool comp2(T a,T b) {
   return a > b;
}

template <typename T>
class MinMaxHeap {
public:
	// Overloaded Constructor
   MinMaxHeap<T>(int capacity);
	
	// Copy Constructor
   MinMaxHeap(const MinMaxHeap<T>& other);
	
	// Destructor
   ~MinMaxHeap<T>();

	// Overloaded assignment operator
   const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);
	
	// Add data
   void insert(const T& data);
		
	// Remove smallest data
   T deleteMin();
	
	// Remove biggest data 
   T deleteMax();
	
	// Getter for m_size
   int size();
	
	// Outputs all data
   void dump();
	
   void locateMin(int pos, T& data, int& index);
	
   void locateMax(int pos, T& data, int& index);
		
   class Heap{
   public:
      Heap(bool (func)(T a,T b),const int& capacity){
         m_size = 0;
         m_capacity = capacity;
         compare = func;
         m_data = new T[capacity]();
      }
      ~Heap(){
         delete[] m_data;
      }
      Heap(const Heap *other){
         m_size = other->m_size;
         m_capacity = other->m_capacity;
         compare = other->compare;
         m_data = new T[m_capacity]();
         for (int i = 0;i <= m_size;i++){
            m_data[i] = other->m_data[i];
         }
      }
      int insert(const T& data){
         if((m_size + 1) < m_capacity){
            m_data[m_size + 1] = data;
            bubbleUp(m_size + 1);
            m_size++;
            return m_size - 1;
         }
         throw std::range_error("Heap capacity met");
      }
      bool deletion(int index){
         if(index <= m_size && index > 0){
            m_data[index] = m_data[m_size]; 
            m_size--;
            bubbleDown(index);
            bubbleUp(index);
            return true;
         }
         return false;
      } 
      int top(){
         return m_data[1];
      }
      void dump(){
         for (int i = 1;i <= m_size;i++){
            std::cout << "Heap[" << i << "] = (";
            std::cout << m_data[i] << ")" << std::endl;
         }
      }
      T *m_data;
      int m_size;
      int m_capacity;
      bool (*compare)(T a,T b);
      int parent(int index){
         return (index / 2) - ((index / 2) % 1);
      }
   private:
      void bubbleUp(int index){
         if (index >= 2){
            if(compare(m_data[index],m_data[parent(index)])){
               T temp = m_data[index];
               m_data[index] = m_data[parent(index)];
               m_data[parent(index)] = temp;
               bubbleUp(parent(index));
            }
         }
      }
      void bubbleDown(int index){
         if(m_size >= (2 * index)){ // Has children
            int childIndex;
            if(m_size == (2 * index)){ // Only has a left child
               childIndex = 2 * index;
            } 
            else {
               if(compare(m_data[2 * index],m_data[(2 * index) + 1])){ // Compare two children
                  childIndex = 2 * index;
               } 
               else {
                  childIndex = (2 * index) + 1;
               }
            }
            if(compare(m_data[childIndex],m_data[index])){
               T temp = m_data[index];
               m_data[index] = m_data[childIndex];
               m_data[childIndex] = temp;
               bubbleDown(childIndex);
            } 		
         }
      }
   };
	
private:
	// Size of heap
   int m_size;
	
	// Capacity of heap
   int m_capacity;
   Heap* minHeap;
   Heap* maxHeap;
	
};
#include "MinMaxHeap.cpp"
#endif
