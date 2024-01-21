//
// Created by viktoria on 03.05.23.
//
#include "RationalNum.h"

int main(){
    using namespace rational_num;
    std::cout<<"Testing default constructor: "<<"\n";
    RationalNum s1 = RationalNum(42);
    RationalNum s2 = RationalNum();
    std::cout<<"RationalNum(42): ";
    s1.print_frac();
    std::cout<<std::endl;
    std::cout<<"RationalNum(): ";
    s2.print_frac();
    std::cout<<std::endl;




//    std::cout<<"Testing operators: "<<"\n";
//    RationalNum l1 = RationalNum(1,3);
//    RationalNum l2 = RationalNum(1,20);
//    l1.print_frac();
//    std::cout<<" + ";
//    l2.print_frac();
//    RationalNum l3 = l1 +l2;
//    std::cout<<"=";
//    l3.print_frac();
//    std::cout<<std::endl;
//    std::cout<<"Result as a floating decimal: "<<"\n";
//    std::cout<<l3<<std::endl;
//    std::cout<<"----------------------"<<std::endl;
//
//    l1.print_frac();
//    std::cout<<" - ";
//    l2.print_frac();
//    RationalNum l4 = l1 - l2;
//    std::cout<<"=";
//    l4.print_frac();
//    std::cout<<std::endl;
//    std::cout<<"Result as a floating decimal: "<<"\n";
//    std::cout<<l4<<std::endl;
//    std::cout<<"----------------------"<<std::endl;
//
//    l1.print_frac();
//    std::cout<<" * ";
//    l2.print_frac();
//    RationalNum l5 = l1 * l2;
//    std::cout<<"=";
//    l5.print_frac();
//    std::cout<<std::endl;
//    std::cout<<"Result as a floating decimal: "<<"\n";
//    std::cout<<l5<<std::endl;
//    std::cout<<"----------------------"<<std::endl;
//
//    l1.print_frac();
//    std::cout<<" / ";
//    l2.print_frac();
//    RationalNum l6 = l1 / l2;
//    std::cout<<"=";
//    l6.print_frac();
//    std::cout<<std::endl;
//    std::cout<<"Result as a floating decimal: "<<"\n";
//    std::cout<<l6<<std::endl;
//    std::cout<<"----------------------"<<std::endl;
//
//    std::cout<<"Testing given fraction RationalNum(2359348,99900): "<<"\n";
//    RationalNum s3 = RationalNum(2359348,99900);
//    std::cout<<s3<<"\n";

    RationalNum e1 = RationalNum(2,4);

    std::cout<<"Testing unary operators"<<std::endl;
    e1.print_frac();
    std::cout<<std::endl;
    RationalNum e3 = -e1;
    e3.print_frac();
    std::cout<<e3<<std::endl;
    std::cout<<std::endl;
    e1.print_frac();
    std::cout<<std::endl;
    RationalNum e4 = !e1;
    e4.print_frac();
    std::cout<<e4<<std::endl;
    std::cout<<"-------------"<<std::endl;

    RationalNum a1 = 2+ e1 ;
    e1.print_frac();
    std::cout<<a1<<std::endl;


    return 0;
}