#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  if(head==tail) return true;
  return false; // dummy return
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  if((tail+1)%N==head) {return true;}
  return false; // dummy return
}

template <typename T> void DynamicQueue<T> :: grow() {
  T* B;
  B = new T[N];
  int k=0;
  for(int i=head;i!=tail;i=(i+1)%N){
    B[k]=A[i];
    k+=1;
  }
  k=N;
  N=nextSize();
  delete[] A;
  A = new T[N];
  for(int i=0;i<k;i++){
    A[i]=B[i];
  }
  head=0;
  tail=k;
  delete[] B;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    if (tail >= head)
        return tail - head;
    else
        return N - head + tail;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if (isFull()){
    grow();
    A[tail]=x;
    tail=(tail+1)%N;
  }
  else{
    A[tail]=x;
    tail+=1;
    tail%=N;
  }
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  *x=A[head];
  head+=1;
  head%=N;
  return true; // dummy return
}
