//
// Created by viktoria on 15.05.23.
//

#ifndef LISTA_9_QUEUE_H
#define LISTA_9_QUEUE_H

#include "MyList.h"

namespace calc {
    template<typename T>
    class Queue : private List<T> {
    public:
        using List<T>::IsEmpty;

        void Enqueue(T value);

        T Dequeue();

        T Front();

        int Size() const { return this->getSize(); }

        template<typename U>
        friend std::ostream &operator<<(std::ostream &os, const Queue<U> &stk);

    };

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const Queue<T> &stk) {
        os << static_cast<const List<T>&>(stk);
        return os;
    }

    template<typename T>
    T Queue<T>::Front() {

        if (this->IsEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return this->GetHead()->value;

    }

    template<typename T>
    T Queue<T>::Dequeue() {
        if (this->IsEmpty()) {
            throw std::invalid_argument("Queue is empty");
        }
        T value = this->head->value;
        this->RemoveAtBeginning();
        return value;
    }

    template<typename T>
    void Queue<T>::Enqueue(T value) {
        {
            this->InsertAtEnd(value);
        }

    }


};


#endif //LISTA_9_QUEUE_H
