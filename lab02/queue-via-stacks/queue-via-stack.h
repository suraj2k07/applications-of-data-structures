// WRITE IMPLEMENTATIONS OF METHODS BELOW

#include "queue.h"

template <typename T>
Queue<T>::Queue() {
}

template <typename T>
Queue<T>::~Queue() {
}

template <typename T>
void Queue<T>::enqueue(T value) {
    first_stack.push(value);
    return; 
}

template <typename T>
T Queue<T>::dequeue() {
    T k;
    if(!second_stack.isEmpty()){
        k=second_stack.pop();
    }
    else {
        size_t g=first_stack.getSize();
        while(g>1){
            second_stack.push(first_stack.pop());
            g-=1;
        }
        k=first_stack.pop();
    }
    return k;
}

template <typename T>
T Queue<T>::peek() {
    if(second_stack.isEmpty()){
        size_t g=first_stack.getSize();
        while(g>0){
            
            second_stack.push(first_stack.pop());
            g-=1;
        }
    }
    return second_stack.peek();
}

template <typename T>
bool Queue<T>::isEmpty() {
    return first_stack.isEmpty() && second_stack.isEmpty();
}

template <typename T>
size_t Queue<T>::getSize() {
    return first_stack.getSize()+second_stack.getSize();
}