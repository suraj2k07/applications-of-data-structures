#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  if(head==tail) return true;
  return false; // dummy return
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  if(tail-head==N) return true;
  return false; // dummy return
}

template <typename T> void DynamicQueue<T> :: grow() {
  T* B;
  B = new T[N];  
  N=nextSize();
  for(int i=0;i<tail-head;i++){
    B[i]=A[i+head];
  }
  delete[] A;
  A=new T[N];
  for(int i=0;i<tail-head;i++){
    A[i]=B[i];
  }
  delete[] B;
  tail=tail-head;
  head=0;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return tail-head; // dummy return
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if(tail<N){
    A[tail]=x;
    tail+=1;}
  else if (head !=0 ){
    for(int i=0;i<tail-head;i++){
      A[i]=A[i+head];
    }
  tail=tail-head;
  head=0;
  A[tail]=x;
  tail+=1;
  }
  else {
    grow();
    A[tail]=x;
    tail+=1;
  }
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if(size()==0) return false;
  *x=A[head];
  head+=1;
  return true; // dummy return
}
