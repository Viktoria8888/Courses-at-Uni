//
// Created by viktoria on 13.04.23.
//
#include "Expression.cpp"

int main(){
    cout<<"Testing number:"<<endl;
    Number num( 3);
    cout<<num.label()<<endl;

    cout<<"Testing variable: ";
    Variable new_var("x");
    cout << new_var.label() << endl;
    cout<<"Changing the value of the variable new_var.change_var(\"x\", 9): ";
    new_var.change_var("x", 9);
    cout<<new_var.evaluate()<<endl;
    cout<<"Variable::delete_var(\"x\")"<<endl;
    //Variable::delete_var("x");

    Variable::printingVals();

    cout<<"Testing constants"<<endl;
    cout<<(new Pi())->label()<<" ";
    cout<<(new Pi())->evaluate()<<endl;

    cout<<"Testing operators:"<<endl;
    cout<<"(new Sin((new Number(3.14))))->evaluate()"<<endl;
    cout << (new Sin((new Number( 3.14))))->evaluate() << endl;

    cout<<"(new Exp((new Number(3.14))))->evaluate() ";
    cout << (new Exp((new Number( 3.14))))->evaluate() << endl;

    Expression *w = new Subtract(
            new Pi(),
            new Add(
                    new Number(2),
                    new Multiply(
                            new Variable("x"),
                            new Number(7)
                    )
            )
    );
    cout<<w->label()<<endl;
    cout<<w->evaluate()<<endl;

    Expression *s = new Divide(
            new Multiply(
                new Subtract(new Variable("x"), new Number(1)), new Variable("x")), new Number(2));
    cout<<s->label()<<endl;


    return 0;
}