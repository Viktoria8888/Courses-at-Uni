//
// Created by viktoria on 15.05.23.
//

#ifndef LISTA_9_MYSTACK_H
#define LISTA_9_MYSTACK_H
#include "MyList.h"
namespace calc{
    template<typename T>
    class Stack : private List<T> {
    public:
        using List<T>::IsEmpty;

        void Push(T value);

        T Pop();

        T Top();

        int Size() const { return this->getSize();}

        template<typename U>
        friend std::ostream &operator<<(std::ostream &os, const Stack<U> &stk);



    };
    template<typename T>
    std::ostream &operator<<(std::ostream &os, const Stack<T> &stk) {
        os << static_cast<const List<T>&>(stk);
        return os;
    }
    template<typename T>
    T Stack<T>::Top() {
        if (this->IsEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return this->GetTail()->value;
    }

    template<typename T>
    T Stack<T>::Pop() {
        if (this->IsEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        T value = this->GetTail()->value;
        this->RemoveAtEnd();
        return value;
    }

    template<typename T>
    void Stack<T>::Push(T value) {
        this->InsertAtEnd(value);
    }


}


#endif //LISTA_9_MYSTACK_H
