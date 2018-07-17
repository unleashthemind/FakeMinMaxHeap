// File: Driver.cpp
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 4
// Combination of tests 


#include "MinMaxHeap.h"
#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>
#include <string.h>
using namespace std;

template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
   int n = H.size() ;
   T minKey, maxKey, leftKey, rightKey ;
   int minPos, maxPos, pos ;
   
   bool passed=true ;

   cout << "Sanity Check minHeap...\n" ;

   for (int i=1 ; i<=n ; i++) {
      H.locateMin(i,minKey,maxPos) ; 
      H.locateMax(maxPos,maxKey,minPos) ; 
      
      if (minKey != maxKey) {
         passed = false ;
         cout << "Key mismatch at i = " << i << ": "
            << "minKey = " << minKey << ", " 
            << "minPos = " << minPos << ", " 
            << "maxKey = " << maxKey << ", " 
            << "maxPos = " << maxPos 
            << endl ;
      }
   
      if (minPos != i) {
         passed = false ;
         cout << "Position mismatch at i = " << i << ": "
            << "minKey = " << minKey << ", " 
            << "minPos = " << minPos << ", " 
            << "maxKey = " << maxKey << ", " 
            << "maxPos = " << maxPos 
            << endl ;
      }
   
      if (2*i <= n) {  // has left child
         H.locateMin(2*i,leftKey,pos) ;
         if (leftKey < minKey) {  // left child smaller than root 
            passed = false ;
            cout << "Bad heap condition at i = " << i << ": "
               << "root key = " << minKey << ", " 
               << "left key = " << leftKey 
               << endl ;
         }
      }  
   
      if (2*i+1 <= n) {  // has right child
         H.locateMin(2*i+1,rightKey,pos) ;
         if (rightKey < minKey) {  // right child smaller than root 
            passed = false ;
            cout << "Bad heap condition at i = " << i << ": "
               << "root key = " << minKey << ", " 
               << "right key = " << rightKey 
               << endl ;
         }
      }  
   
   }  // end of for (...)


   cout << "Sanity Check maxHeap...\n" ;

   for (int i=1 ; i<=n ; i++) {
      H.locateMax(i,maxKey,minPos) ; 
      H.locateMin(minPos,minKey,maxPos) ; 
      
      if (minKey != maxKey) {
         passed = false ;
         cout << "Key mismatch at i = " << i << ": "
            << "minKey = " << minKey << ", " 
            << "minPos = " << minPos << ", " 
            << "maxKey = " << maxKey << ", " 
            << "maxPos = " << maxPos 
            << endl ;
      }
   
      if (maxPos != i) {
         passed = false ;
         cout << "Position mismatch at i = " << i << ": "
            << "minKey = " << minKey << ", " 
            << "minPos = " << minPos << ", " 
            << "maxKey = " << maxKey << ", " 
            << "maxPos = " << maxPos 
            << endl ;
      }
   
      if (2*i <= n) {  // has left child
         H.locateMax(2*i,leftKey,pos) ;
         if (leftKey > maxKey) {  // left child bigger than root 
            passed = false ;
            cout << "Bad heap condition at i = " << i << ": "
               << "root key = " << maxKey << ", " 
               << "left key = " << leftKey 
               << endl ;
         }
      }  
   
      if (2*i+1 <= n) {  // has right child
         H.locateMax(2*i+1,rightKey,pos) ;
         if (rightKey > maxKey) {  // right child bigger than root 
            passed = false ;
            cout << "Bad heap condition at i = " << i << ": "
               << "root key = " << maxKey << ", " 
               << "right key = " << rightKey 
               << endl ;
         }
      }  
   }  // end of for (...)


   if (passed) {
      cout << "Passed sanityCheck().\n" ;
   } 
   else {
      cout << "*** Failed sanityCheck().\n" ;
   }
}

template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T>& origS) {
   multiset<T> S ;  
   typename multiset<T>::iterator it ;

   int n = H.size() ;
   int pos ;
   int key ;

   bool passed = true ;

   S = origS ;  // make copy

   if ( n != S.size() ) {
      passed = false ;
      cout << "Heap and multiset sizes do not match!\n" ;
      cout << "   Heap size = " << n << endl ;
      cout << "   Set size  = " << S.size() << endl ;
   }


   for (int i=1 ; i <= n ; i++) {
      H.locateMin(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
         passed = false ;
         cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
      } 
      else {
         S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the min-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }


   S = origS ;  // start over

   for (int i=1 ; i <= n ; i++) {
      H.locateMax(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
         passed = false ;
         cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
      } 
      else {
         S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the max-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }

   if (passed) {
      cout << "Passed check against multiset\n" ;
   } 
   else {
      cout << "***Failed check against multiset\n" ;
   }

}

template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T,greater<T> >& origS) {
   multiset<T,greater<T> > S ;  
   typename multiset<T,greater<T> >::iterator it ;

   int n = H.size() ;
   int pos ;
   int key ;

   bool passed = true ;

   S = origS ;  // make copy

   if ( n != S.size() ) {
      passed = false ;
      cout << "Heap and multiset sizes do not match!\n" ;
      cout << "   Heap size = " << n << endl ;
      cout << "   Set size  = " << S.size() << endl ;
   }


   for (int i=1 ; i <= n ; i++) {
      H.locateMin(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
         passed = false ;
         cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
      } 
      else {
         S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the min-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }


   S = origS ;  // start over

   for (int i=1 ; i <= n ; i++) {
      H.locateMax(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
         passed = false ;
         cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
      } 
      else {
         S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the max-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }

   if (passed) {
      cout << "Passed check against multiset\n" ;
   } 
   else {
      cout << "***Failed check against multiset\n" ;
   }

}


int main(){
	//Test1
   MinMaxHeap<int> H(25) ;
   H.insert(5) ;
   H.insert(10) ;
   H.insert(7) ;
   H.insert(9) ;
   H.insert(6) ;
   H.insert(2) ;
   H.insert(16) ;
   H.insert(12) ;
   H.insert(11) ;

   cout << "Initial MinMax Heap\n" ;
   H.dump() ;

   H.insert(8); 
   cout << "After inserting 8\n" ;
   H.dump() ;

   sanityCheck(H) ;

   int answer ;
   answer = H.deleteMin() ;
   cout << "\n\nMin item " << answer << " removed from MinMax Heap\n" ;

   H.dump() ;
   sanityCheck(H) ;

   answer = H.deleteMax() ;
   cout << "\n\nMax item " << answer << " removed from MinMax Heap\n" ;

   H.dump() ;
   sanityCheck(H) ;
	
	//Test2
   MinMaxHeap<string> H1(25) ;
   H1.insert("jkl") ;
   H1.insert("yz_") ;
   H1.insert("abc") ;
   H1.insert("mno") ;
   H1.insert("vwx") ;
   H1.insert("pqr") ;
   H1.insert("ghi") ;
   H1.insert("def") ;
   H1.insert("stu") ;

   H1.dump() ;
   sanityCheck(H1) ;

   string answer1 ;
   answer1 = H1.deleteMin() ;
   cout << "Min item " << answer1 << " removed from MinMax Heap\n" ;

   answer1 = H1.deleteMax() ;
   cout << "Max item " << answer1 << " removed from MinMax Heap\n" ;

   H1.dump() ;
   sanityCheck(H1) ;
	
	//Test3 (works, but commented out since NoCopyString is not a file we are supposed to turn in)
   /*
   MinMaxHeap<NoCopyString> H2(9) ;

   const char* myData[9] = {
      "jkl", "yz_", "abc",
      "mno", "vwx", "pqr",
      "ghi", "def", "stu" 
      } ;

   H2.insert(myData[0]) ;
   H2.insert(myData[1]) ;
   H2.insert(myData[2]) ;
   H2.insert(myData[3]) ;
   H2.insert(myData[4]) ;
   H2.insert(myData[5]) ;
   H2.insert(myData[6]) ;
   H2.insert(myData[7]) ;
   H2.insert(myData[8]) ;

   H2.dump() ;
   sanityCheck(H2) ;

   NoCopyString answer2 ;
   answer2 = H2.deleteMin() ;
   cout << "Min item " << answer2 << " removed from MinMax Heap\n" ;

   answer2 = H2.deleteMax() ;
   cout << "Max item " << answer2 << " removed from MinMax Heap\n" ;

   H2.dump() ;
   sanityCheck(H2) ;
	*/
	//Test 4
   srand(4178012351) ;

   MinMaxHeap<int> H3(1000) ;
   multiset<int> S ;
   multiset<int>::iterator it ;
   int key ;
   bool passed ;

   for (int i=0 ; i < 500 ; i++) {
      key = rand() % 100 ;
      // cout << "Insert key = " << key << endl ;
      H3.insert(key) ;
      S.insert(key) ;
   }
   //sanityCheck(H3) ; //Sanity check was written to handle duplicates differently than how I chose
   checkAgainstSet(H3,S) ;

   passed = true ;
   for (int i=0 ; i < 450 ; i++) {
      key = H3.deleteMin() ;
      if (key != *S.begin()) {
         passed = false ;
         cout << "deleteMin() returns key that is not the smallest key!\n" ;
      } 
      else {
         S.erase(S.begin()) ;
      }
   }

   //sanityCheck(H3) ;//Sanity check was written to handle duplicates differently than how I chose

   if (passed) {
      checkAgainstSet(H3,S) ;
   } 
   else {
      cout << "***Failed deleteMin() test!\n" ;
      cout << "Skipped check against multiset\n" ;
   }
	//Test 5
   srand(4178012351) ;

   MinMaxHeap<int> H4(1000) ;
   multiset<int,greater<int> > S1 ;
   multiset<int,greater<int> >::iterator it1 ;

   for (int i=0 ; i < 750 ; i++) {
      key = rand() % 100 ;
      // cout << "Insert key = " << key << endl ;
      H4.insert(key) ;
      S1.insert(key) ;
   }
   //sanityCheck(H4) ; //Sanity check was written to handle duplicates differently than how I chose
   checkAgainstSet(H4,S1) ;

   passed = true ;
   for (int i=0 ; i < 400 ; i++) {
      key = H4.deleteMax() ;
      if (key != *S1.begin()) {
         passed = false ;
         cout << "deleteMax() returns key that is not the largest key!\n" ;
      } 
      else {
         S1.erase(S1.begin()) ;
      }
   }

   //sanityCheck(H4) ; //Sanity check was written to handle duplicates differently than how I chose


   if (passed) {
      checkAgainstSet(H4,S1) ;
   } 
   else {
      cout << "***Failed deleteMax() test!\n" ;
      cout << "Skipped check against multiset\n" ;
   }
	// Test 6
   MinMaxHeap<int> H5(25) ;
   H5.insert(5) ;
   H5.insert(10) ;
   H5.insert(7) ;
   H5.insert(9) ;
   H5.insert(6) ;
   H5.insert(2) ;
   H5.insert(16) ;
   H5.insert(12) ;
   H5.insert(11) ;

   cout << "Initial MinMax Heap\n" ;
   H5.dump() ;
   sanityCheck(H5) ;

   MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H5) ;
   cout << "copied MinMax Heap\n" ;
   Gptr->dump();

   H5.deleteMax() ;
   Gptr->deleteMin() ;
   cout << "\nH and *Gptr after deleteMax and deleteMin\n" ;
   sanityCheck(H5) ;
   sanityCheck(*Gptr) ;

   delete Gptr ;

   cout << "\nH after Gptr deleted\n" ;
   H5.deleteMin() ;
   H5.deleteMax() ;
   sanityCheck(H5) ;

   MinMaxHeap<int> K1(11) ;
   K1.insert(29) ;
   K1.insert(24) ;
   K1.insert(23) ;
   K1.insert(22) ;
   K1.insert(28) ;
   K1.insert(26) ;
   K1.insert(30) ;
   K1.insert(21) ;
   K1.insert(25) ;
   K1.insert(27) ;

   cout << "\nK1 after inserts\n" ;
   sanityCheck(K1) ;

   MinMaxHeap<int> K2(4) ;
   K2.insert(43) ;
   K2.insert(42) ;
   K2.insert(44) ;
   K2.insert(41) ;

   cout << "\nK2 after inserts\n" ;
   sanityCheck(K2) ;

   K2 = K1 ;
   K1.deleteMax() ;
   K2.insert(57) ;

   cout << "\nK1 & K2 after assignment, etc...\n" ;
   sanityCheck(K1) ;
   sanityCheck(K2) ;
   return 0;
}
