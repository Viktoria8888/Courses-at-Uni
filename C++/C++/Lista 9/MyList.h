//
// Created by viktoria on 14.05.23.
//

#ifndef LISTA_9_MYLIST_H
#define LISTA_9_MYLIST_H

#include <stdexcept>
#include <iostream>
#include <functional>

namespace calc {


    template<typename T>
    class List {
    private:
        class Node {
        public:
            Node *next;
            T value;
        };

        int size;

    protected:
        Node *head;
    public:
        Node * GetTail() {
            if (IsEmpty()) {
                return nullptr;
            }

            Node *curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            return curr;
        }

        Node *GetHead() const {
            return head;
        }
        List() : head(nullptr), size(0) {}

        ~List();

        List(const List<T> &other);

        List(List<T> &&other);

        List<T> &operator=(const List<T> &other);

        List<T> &operator=(List<T> &&other);

        bool IsEmpty() const;

        void PrintList();

        void InsertAt(int index, T value);

        void InsertAtBeginning(T Value);

        void InsertAtEnd(T value);

        void RemoveAt(int index);

        void RemoveAtBeginning();

        void RemoveAtEnd();

        int FindIndex(T value);

        void RemoveValue(T value);

        void RemoveAllOccurrences(T value);

        int CountAllOccurrence(T value);

        int getSize() const;

        List(std::initializer_list<T> values);

        template<typename U>
        friend std::ostream &operator<<(std::ostream &os, const List<U> &lst);

        template<typename U, typename Compare>
        friend void sort(List<U>& list);

    };

    template<typename T>
    int List<T>::getSize() const {
        return size;
    }

    // issorted template function
    template<typename T, typename Compare = std::less_equal<T>>
    bool issorted(const List<T>& list) {
        if (list.IsEmpty() || list.getSize() == 1)
            return true;

        const auto& comparator = Compare();
        auto current = list.GetHead();

        while (current->next != nullptr) {
            if (!comparator(current->value, current->next->value))
                return false;
            current = current->next;
        }

        return true;
    }


    template<typename T, typename Compare = std::less_equal<T>>
    void sort(List<T>& list) {
        if (list.IsEmpty() || list.getSize() == 1)
            return;

        const auto& comparator = Compare();
        typename List<T>::Node* current = list.GetHead()->next;
        typename List<T>::Node* sortedList = nullptr;

        while (current != nullptr) {
            typename List<T>::Node* next = current->next;

            if (sortedList == nullptr || comparator(current->value, sortedList->value)) {
                current->next = sortedList;
                sortedList = current;
            } else {
                typename List<T>::Node* temp = sortedList;
                while (temp->next != nullptr && comparator(temp->next->value, current->value)) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;
        }

        list.GetHead()->next = sortedList;
    }





    template<typename T>
    std::ostream &operator<<(std::ostream &os, const List<T> &lst) {
        typename List<T>::Node *current = lst.head;
        while (current != nullptr) {
            os << current->value << " ";
            current = current->next;
        }
        return os;
    }

    template<typename T>
    List<T>::List(std::initializer_list<T> values) : head(nullptr), size(0) {
        for (const auto &value: values) {
            InsertAtEnd(value);
        }
    }

    template<typename T>
    List<T>::List(const List<T> &other) : head(nullptr), size(0) {
        Node *otherNode = other.head;
        while (otherNode != nullptr) {
            InsertAtEnd(otherNode->value);
            otherNode = otherNode->next;
        }
    }

    template<typename T>
    List<T>::List(List<T> &&other) : head(nullptr), size(0) {
        std::swap(head, other.head);
        std::swap(size, other.size);
    }

    template<typename T>
    List<T> &List<T>::operator=(const List<T> &other) {
        if (this != &other) {
            // Clear the current list
            Node *current = head;
            while (current != nullptr) {
                Node *next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            size = 0;
            Node *otherNode = other.head;
            while (otherNode != nullptr) {
                InsertAtEnd(otherNode->value);
                otherNode = otherNode->next;
            }
        }
        return *this;
    }

    template<typename T>
    List<T> &List<T>::operator=(List<T> &&other) {
        if (this != &other) {

            Node *current = head;
            while (current != nullptr) {
                Node *next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            size = 0;


            std::swap(head, other.head);
            std::swap(size, other.size);
        }
        return *this;
    }




    template<typename T>
    bool List<T>::IsEmpty() const {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    template<typename T>
    List<T>::~List() {
        Node *temp = head;
        while (temp != nullptr) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }

    template<typename T>
    void List<T>::PrintList() {
        Node *currentNode = head;
        while (currentNode != nullptr) {
            std::cout << currentNode->value << "→";
            currentNode = currentNode->next;
        }
        std::cout << std::endl;
    }

    template<typename T>
    void List<T>::InsertAt(int index, T value) {
//        if (index < 0 || index > size) {
//            throw std::invalid_argument("The index is out of range");
//        }

        Node *newNode = new Node;
        newNode->value = value;

        if (IsEmpty()) {
            newNode->next = nullptr;
            head = newNode;
        } else if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            // Insert at the specified index
            Node *prevNode = head;
            for (int i = 0; i < index - 1; i++) {
                prevNode = prevNode->next;
            }
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }

        size++;
    }

    template<typename T>
    void List<T>::InsertAtBeginning(T Value) {
        InsertAt(0, Value);
    }

    template<typename T>
    void List<T>::InsertAtEnd(T value) {

        InsertAt(size, value);
    }

    template<typename T>
    void List<T>::RemoveAt(int index) {
        if (index < 0 || index > size) {
            throw std::invalid_argument("The index is out of range");
        }

        if (IsEmpty()) {
            throw std::invalid_argument("The list is empty");
        }

        if (index == 0) {
            head = head->next;
        } else {
            Node *prevNode = nullptr;
            Node *curr = head;
            for (int k = 0; k < index; k++) {
                prevNode = curr;
                curr = curr->next;
            }
            prevNode->next = curr->next;
        }
        size--;
    }

    template<typename T>
    void List<T>::RemoveAtBeginning() {
        RemoveAt(0);
    }

    template<typename T>
    void List<T>::RemoveAtEnd() {
        RemoveAt(size - 1);
    }

    template<typename T>
    int List<T>::FindIndex(T value) {
        if (IsEmpty()) {
            throw std::invalid_argument("The list is empty");
        }
        int i = 0;
        Node *curr = head;
        while (curr->next != nullptr) {
            if (curr->value == value) {
                return i;
            }
            curr = curr->next;
            i++;
        }
        return -1;
    }


    template<typename T>
    void List<T>::RemoveValue(T value) {
        RemoveAt(FindIndex(value));
    }

    template<typename T>
    void List<T>::RemoveAllOccurrences(T value) {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr != nullptr) {
            if (curr->value == value) {
                // Node contains the value, remove it
                if (prev == nullptr) {
                    // Node is the head of the list
                    head = curr->next;
                    delete curr;
                    curr = head;
                } else {
                    // Node is not the head of the list
                    prev->next = curr->next;
                    delete curr;
                    curr = prev->next;
                }
                size--;
            } else {
                // Move to the next node
                prev = curr;
                curr = curr->next;
            }
        }
    }

    template<typename T>
    int List<T>::CountAllOccurrence(T value) {
        if (IsEmpty()) {
            throw std::invalid_argument("The list is empty");
        }
        int i = 0;
        Node *curr = head;
        while (curr != nullptr) {
            if (curr->value == value) {
                i++;
            }
            curr = curr->next;
        }
        return i;
    }





} // calc

#endif //LISTA_9_MYLIST_H
