package org.example;


import com.google.inject.AbstractModule;
import com.google.inject.Guice;
import com.google.inject.Injector;

public class Main {
    public static void main(String[] args) {
        Injector injector = Guice.createInjector(new DemoGuice());
        // 1) Rejestrowanie typów dzieje się automatycznie (Just in time bindings)
        // Jeśli konstruktor zawiera annotachę @Inject lub kiedy jest bezargumentowy.
        Foo foo1 = injector.getInstance(Foo.class);
        foo1.print();

        // 2) Rejestrowanie implementacji interfejsów
        IQux qux1 = injector.getInstance(IQux.class);
        qux1.sayHello();
        // 3) Klasa abstrakcyjna na implementacje
        IBar bar1 = injector.getInstance(IBar.class);
        bar1.sayHello();

        // 4) Metoda fabrykująca (poprzez @Provides, jest jeszcze @AssistedInjector)
        BarFromFactoryMethod bar2 = injector.getInstance(BarFromFactoryMethod.class);

        // 5) Rejestracja Instancji (też poprzez provides)
        Bar bar3 = injector.getInstance(Bar.class);
        Bar bar4 = injector.getInstance(Bar.class);
        System.out.println(bar3==bar4);

    }
}