#include "common.h"

int BinarySearch ( int * S , int n , int e ) {
  int iteration_count = 0;
  // Implement binary search here
  // instead of returning position return the number
  // of executed iterations of binary search.
  int first = 0,last=n,mid = (first+last)/2,count=0;
  while(first <= last){
    if (S[mid]==e) return ++count;
    else if (S[mid] > e) {
      first = mid+1 ;
    }
    else last = mid;
    mid = (first+last)/2;
    count += 1;
  }
  return count;
}

double drive_binary_search(unsigned size) {
  // Initialize an array with distinct elements
  // search all elements stored in S and compute
  // the average number of iterations in binary search
  int a[size];
  double d=0;
  for(unsigned c=0;c<size;c++){
    a[c] = 2*size -c ; 
  }
  for (int i=0;i<size;i++){
    d+=BinarySearch(a,size,2*size-i);
  }
  return d/size;
}