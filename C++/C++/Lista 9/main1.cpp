
#include "MyList.h"
#include "MyStack.h"
#include "Queue.h"

int main() {
    auto* myList = new calc::List<int>();

    std::cout<< "Insert elements into the list" <<std::endl;
    std::cout<< "myList.InsertAt(0, 10);" <<std::endl;
    std::cout<< "myList.InsertAt(1, 20);" <<std::endl;
    std::cout<< "myList.InsertAt(2, 30);" <<std::endl;
    std::cout<< "myList.InsertAt(3, 40);" <<std::endl;
    std::cout<< "myList.InsertAt(4, 50);" <<std::endl;
    std::cout<< "myList.InsertAt(5, 30);" <<std::endl;
    myList->InsertAt(0, 10);
    myList->InsertAt(1, 20);
    myList->InsertAt(2, 30);
    myList->InsertAt(3, 40);
    myList->InsertAt(4, 50);
    myList->InsertAt(5, 30);
    myList->PrintList();
    std::cout<< "myList.InsertAt(2, 42);" <<std::endl;
    myList->InsertAt(2, 42);
    myList->PrintList();
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Removing Elements: At Index"<<std::endl;
    std::cout<<"myList.RemoveAt(2);"<<std::endl;
    myList->RemoveAt(2);
    myList->PrintList();
    std::cout<<"myList.RemoveAtBeginning();"<<std::endl;
    myList->RemoveAtBeginning();
    myList->PrintList();
    std::cout<<"---------------------------------"<<std::endl;

    std::cout<<"Removing Elements: by Value"<<std::endl;
    myList->PrintList();

    myList->RemoveValue(30);
    std::cout<<"myList.RemoveValue(30);"<<std::endl;
    myList->PrintList();
    std::cout<<"Inserting some 42"<<std::endl;
    myList->InsertAt(3, 42);
    myList->InsertAt(4, 42);
    myList->InsertAt(5, 42);
    myList->PrintList();
    std::cout<<"Removing all the occurrences of 42: "<<std::endl;
    myList->RemoveAllOccurrences(42);
    myList->PrintList();
    std::cout<<"myList.CountAllOccurrence(42): "<<myList->CountAllOccurrence(42)<<std::endl;

    std::cout<<"initializer_list<T>"<<std::endl;
    calc::List<int> myList2 = {1, 2, 3 ,4};
    myList2.PrintList();

    calc::List<int> myList3(*myList);
    std::cout << "myList3 (copy): ";
    myList3.PrintList();
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Test copy/move constructor"<<std::endl;
    calc::List<int> myList4(*std::move(myList));
    std::cout << "myList4 (move): ";
    myList4.PrintList();

    std::cout<<"Testing operators: "<<std::endl;
    std::cout<<"Before copy"<<std::endl;
    myList2.PrintList();
    myList4.PrintList();
    myList2 = myList4;
    std::cout<<"After copy"<<std::endl;
    myList2.PrintList();
    myList4.PrintList();
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Testing Stack: pushing 1 2 3"<<std::endl;
    calc::Stack<int>* myStack1 = new calc::Stack<int>();
    myStack1->Push(1);
    myStack1->Push(2);
    myStack1->Push(3);
    std::cout<<"myStack1.Pop(): "<<myStack1->Pop()<<std::endl;
    std::cout<<myStack1<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Testing Queue: Enqueue 1 2 3 "<<std::endl;
    calc::Queue<int>* q1 = new calc::Queue<int>();
    q1->Enqueue(1);
    q1->Enqueue(2);
    q1->Enqueue(3);
    std::cout<<q1<<std::endl;
    std::cout<<"q1.Dequeue();"<<std::endl;
    q1->Dequeue();
    std::cout<<q1<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Testing sort: "<<std::endl;

    calc::List<int> myList0;

    myList0.InsertAt(0, 10);
    myList0.InsertAt(1, 20);
    myList0.InsertAt(2, 30);
    myList0.InsertAt(3, 40);
    myList0.InsertAt(4, 50);
    myList0.InsertAt(5, 60);
    myList0.PrintList();
    std::cout<<"issorted(myList0)"<<std::endl;
    std::cout<<issorted(myList0)<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Testing sorting:"<<std::endl;
    calc::List<int> myList00;

    myList00.InsertAt(0, 0);
    myList00.InsertAt(1, 25);
    myList00.InsertAt(2, 42);
    myList00.InsertAt(3, 4);
    myList00.InsertAt(4, 5);
    myList00.InsertAt(5, 1);
    myList00.PrintList();
    sort(myList00);
    myList00.PrintList();

    delete myStack1;
    delete q1;
    return 0;
}

