package org.example;

import com.google.inject.*;

class Foo{
    public void print(){
        System.out.println("Hello from Foo!");
    }
}
abstract class IBar{
    abstract void sayHello();
}
class Bar extends IBar{

    @Override
    void sayHello() {
        System.out.println("Hello from Bar!");
    }
}
interface IQux{
    void sayHello();
}
class Qux implements IQux{

    @Override
    public void sayHello() {
        System.out.println("Hello from Qux!");
    }
}

class BarFromFactoryMethod{
    @Inject
    public BarFromFactoryMethod(String name, Bar bar){
        bar.sayHello();
        System.out.println("Hello "+ name);
    }
}

class FooSingleton{

}

public class DemoGuice extends AbstractModule {
    @Override
    protected void configure() {
        bind(IQux.class).to(Qux.class);
        bind(IBar.class).to(Bar.class);
        bind(Bar.class).toInstance(new Bar()); // singleton domyślnie;

        bind(FooSingleton.class).in(Reques);

    }

    // metoda fabrykująca
    @Provides
    BarFromFactoryMethod getBarFromFactory(Bar bar) {
        return new BarFromFactoryMethod("Jan Kowalski", bar);
    }
}




