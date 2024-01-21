#include <iostream>
#include "TabBit.cpp"
using namespace std;
void my_swap(int& a,int& b){
    int temp = b;
    b = a;
    a =temp;

}
int main(){
    

    cout<<"Testing constructors:"<<endl;
    cout<<"Create a tab_bit object with 32 bits"<<endl;
    tab_bit tb(32); 
    cout<<tb<<endl;

    
    cout<<"tab_bit w{1, 0, 1, 1, 0, 0, 0, 1}"<<endl;
    tab_bit w{1, 0, 1, 1, 0, 0, 0, 1};
    cout<<w<<endl;
    cout<<" "<<endl;

    cout<<"Copying w"<<endl;
    tab_bit v(w);
    cout<<v<<endl;

    cout<<"Moving constructor: k(tab_bit(8));"<<endl;
    tab_bit k(tab_bit(8));
    cout<< k<<endl;

     
    cout<< "Testing ref class"<<endl;
    

    tb[0] = true;
    //cout<<"The first assignment returns the reference to a tab_bit::ref object"<<endl;
    //cout<<"That's why second assignemnt would be applied to the same tab_bit::ref object."<<endl;
    tb[1] = false;
    tb[8] = true;
    cout<<"Sets the 1st and 8th bit to true"<<endl;
    //tb[8] = tb[5];
    cout<<tb<<endl;

   
    
    cout<<"The chain of assignments: tb[0] = tb[9] = tb[2]"<<endl;
    tb[0] = tb[9] = tb[2];
    cout<<tb<<endl;

    cout<<"The chain of assignments: tb[0] = tb[8]"<<endl;
    tb[0] = tb[8];
    cout<<tb<<endl;

     cout<< "Reading the first bit: ";
    bool b = tb[0];
    cout<<b<<endl;
    
   
    cout<<"Testing bitwise operations for:"<<endl;
    cout<< w<<endl;
    tab_bit s{0, 0, 1, 1,0,0,1,0};
    cout<<s<<endl;
    cout<<"OR: ";
    cout<< (w|s) <<'\n';
    
    cout<<"AND: ";
    cout<< (w&s) <<'\n';
    
    cout<<"XOR: ";
    cout<< (w^s) <<'\n';

    cout<<"NEG: ";
    cout<< (!s) <<'\n';

    cout<<"|= ";
    s |= w;
    cout<<s<<endl;

    cout<<"s&=w ";
    s &= w;
    cout<<s<<endl;

    cout<<"^= ";
    s ^= w;
    cout<<s<<endl;
    return 0;


   
   
}