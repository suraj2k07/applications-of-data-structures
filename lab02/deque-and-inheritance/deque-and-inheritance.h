

using namespace std;

template <typename T>
class Deque
{
    // Write a "Friend" function that overloads the "<<"" operator, and can be used to "cout" a deque.
    // Read about friend functions. Note that friend functions have access to private, public and 
    // protected members!
    friend ostream& operator<<(ostream& out, const Deque& dq)
    { 
      for (int i = 0; i < dq.size; i++)
      {
          out << dq.arr[(dq.front + i) % dq.capacity];
          if (i != dq.size - 1)
              out << " ";
      }
      out << endl;
      return out;

    }

protected:
    // TODO: Suitably initialize the queue parameters (Feel free to add any other variables as needed) 
    T* arr;
    int capacity;
    int resize_factor;
    int size;
    bool auto_resize;
    int front;

public:
    Deque(int cap, bool resize = true, int resize_factor = 2) 
    {       
        // TODO: Implement the constructor that initializes the Deque with a given capacity
        // and optionally the resize factor       
        capacity=cap;
        this->resize_factor = resize_factor;
        auto_resize = resize;    
        arr = new T[capacity];
        size=0;      
        front=0;        
    }

    Deque(bool resize = true, int resize_factor = 2)
    {
        // TODO: Implement the constructor that initializes the Deque with a default capacity
        // and optionally given the resize factor
        capacity=10;
        this->resize_factor = resize_factor;
        auto_resize = resize;    
        arr = new T[capacity];
        size=0; 
        front=0;
    }

    Deque(const Deque& dq)
    {
        // TODO: Implement the copy constructor for the Deque. 
        // What you need to do is copy the contents of the Deque object dq to the new Deque object
        // being instantiated.
        capacity=dq.capacity;
        size=dq.size;
        resize_factor=dq.resize_factor;
        auto_resize=dq.auto_resize;
        arr = new T[capacity];
        front = 0;
        for (int i = 0; i < size; i++) {
          arr[i] = dq.arr[(dq.front + i) % dq.capacity];
        }

    }

    ~Deque()
    {
        // TODO: Implement the destructor
        delete[] arr;
    }

    void print()
    {
        // TODO: Implement a print function similar to the << overload. You can cout the values. Look at the testcases to see how the print output should look

      for (int i = 0; i < size; i++)
      {
          cout << arr[(front + i) % capacity];
          if (i != size - 1)
              cout << " ";
      }
      cout << endl;
    }

    bool is_empty()
    {
        // TODO: Implement the is_empty method to check if the deque is empty
      if(size == 0) return true;
      return false; // DUMMY RETURN
    } 

    int get_capacity()
    {
        // TODO: Implement a getter for the capacity of the Deque
      return capacity; // DUMMY RETURN
    }

    int get_size()
    {
        // TODO: Implement a getter for the size of the Deque
      return size; // DUMMY RETURN
    }
// ATTENTION !!
// We DO NOT want to use Deque as a data structure for the purpose of this lab,
// but want to be able to inherit it's functions selectively and create our 
// Stack and Queue. Therefore, we do not make the following functions public.
protected:

    bool push_back(T data)
    {
        // TODO: Implement the push_back method to push the data into the back of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
        if(size != capacity){
          arr[(front+size)%capacity]=data;
          size+=1;
          return true;}
        else if(!auto_resize) {return false;}
        else{
          T* b;
          b = new T[size*resize_factor];
          for(int i=0;i<size;i++){
            b[i]=arr[(front+i)%capacity];
          }
          capacity*=resize_factor;
          delete[] arr;
          arr = b;
          front = 0;
          arr[size]=data;
          size+=1;
          return true;
        }
    }

    T pop_front()
    {
        // TODO: Implement the pop_front method to pop the data from the front of the deque
        // Throw exception if the deque is empty
      T x;
      if(!is_empty()){
        x=arr[front];
        front+=1;
        front%=capacity;
        return x;
      }
      else throw "empty";
    }

//Returns true if push succeds else returns false
    bool push_front(T data)
    {
        // TODO: Implement the push_front method to push the data into the front of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
        if (size == capacity && !auto_resize) return false;
        if (size == capacity && auto_resize) {
            int new_capacity = capacity * resize_factor;
            T* b = new T[new_capacity];
            for (int i = 0; i < size; i++) {
                b[i] = arr[(front + i) % capacity];
            }
            delete[] arr;
            arr = b;
            capacity = new_capacity;
            front = 0;
        }
        front = (front - 1 + capacity) % capacity;
        arr[front] = data;
        size++;
        return true;
    }

    T pop_back()
    {
        // TODO: Implement the pop_back method to pop the data from the back of the deque
        // Throw exception if the deque is empty
        T x;
        if(!is_empty()){
          x=arr[(front+size-1)%capacity];
          size-=1;
          return x;
        }
        else throw "empty";
    }

    T peek_front()
    {
        // TODO: Implement the peek_front method to return the front element of the deque
        // Throw exception if the deque is empty
        if(!is_empty()){
          return arr[front];
        }
        else throw "empty";    
      }

    T peek_back()
    {
        // TODO: Implement the peek_back method to return the last element of the deque
        // Throw exception if the deque is empty
        T x;
        if(!is_empty()){
          return arr[(front+size-1)%capacity];
        }
        else throw "empty";
    }
};

// Before you go on to this part, read about class inheritance and understand the 3 types below:

// Public inheritance: public->public, protected->protected
// Protected inheritance: public->protected, protected->protected
// Private inheritance (default): public->private, protected->private

// To access private members of the base class, you need to declare derived class as a friend class

// Now, create the Queue class, and you must derive it from Deque. Why implement everything again!

template<typename T>
class Queue : public Deque<T>
{
public:
    // -------------- Constructors --------------
    Queue(int cap, bool resize = true, int resize_factor = 2)
        : Deque<T>(cap, resize, resize_factor) {}

    Queue(bool resize = true, int resize_factor = 2)
        : Deque<T>(resize, resize_factor) {}

    // Copy constructor
    Queue(const Queue<T>& q) : Deque<T>(q) {}

    // -------------- Make protected Deque functions public --------------
    using Deque<T>::push_back;   // Queue inserts at the back
    using Deque<T>::pop_front;   // Queue removes from the front
    using Deque<T>::peek_front;  // Peek the front element
    using Deque<T>::is_empty;
    using Deque<T>::get_size;
    using Deque<T>::get_capacity;

    // Optional: provide a uniform API like "push" for enqueue
    bool push(T data) { return this->push_back(data); }
    T pop() { return this->pop_front(); }
    T peek() { return this->peek_front(); }
};


// Now, create the Stack class, and you must derive it from Deque. Why implement everything again!


template<typename T>
class Stack : public Deque<T>
{
public:
    // -------------- Constructors --------------
    Stack(int cap, bool resize = true, int resize_factor = 2)
        : Deque<T>(cap, resize, resize_factor) {}

    Stack(bool resize = true, int resize_factor = 2)
        : Deque<T>(resize, resize_factor) {}

    // Copy constructor
    Stack(const Stack<T>& s) : Deque<T>(s) {}

    // -------------- Make protected Deque functions public --------------
    using Deque<T>::push_back;   // Stack pushes to the back (top)
    using Deque<T>::pop_back;    // Stack pops from the back (top)
    using Deque<T>::peek_back;   // Peek the top element
    using Deque<T>::is_empty;
    using Deque<T>::get_size;
    using Deque<T>::get_capacity;

    // Optional: provide a uniform API like "push"/"pop" for stack
    bool push(T data) { return this->push_back(data); } // push to top
    T pop() { return this->pop_back(); }               // pop from top
    T top() { return this->peek_back(); }             // peek top
};
