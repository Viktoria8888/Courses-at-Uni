package org.example;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.awt.*;

import static org.junit.jupiter.api.Assertions.*;

interface IBar {
    void doWork();
}
interface IFoo{

}
class Bar implements IBar {
    public void doWork() {
        System.out.println("Do work Bar");
    }
}

class Foo implements IFoo {
}
interface IQux{

}
public class SimpleContainerTest {

    SimpleContainer container;

    @BeforeEach
    void setUp() {
        container = new SimpleContainer();
    }

    @Test
    void testResolveSingleton() {
        container.registerType(Foo.class, true);
        Foo foo1 = container.resolve(Foo.class);
        assertNotNull(foo1);
        assertEquals(Foo.class, foo1.getClass());

        Foo foo2 = container.resolve(Foo.class);
        assertSame(foo1, foo2);
    }

    @Test
    void testResolveTransient() {
        container.registerType(Foo.class, false);
        Foo foo1 = container.resolve(Foo.class);
        assertNotNull(foo1);
        assertEquals(Foo.class, foo1.getClass());
        Foo foo2 = container.resolve(Foo.class);
        assertNotSame(foo1, foo2);

    }
    @Test
    void testResolveInterfaceExists(){
        container.registerTypeMap(IBar.class, Bar.class,false);
        IBar bar = container.resolve(IBar.class);
        assertEquals(bar.getClass(), Bar.class);
    }
    @Test
    void testResolveInterfaceDoesntExists(){
        assertThrows(IllegalArgumentException.class, () -> {
            container.resolve(IQux.class);
        });
    }
    @Test
    void testInterfaceClassMappingDoesntExist(){
        Bar bar = container.resolve(Bar.class);
        assertEquals(bar.getClass(),Bar.class);

    }
    @Test
    void testResolveInstance(){
        IFoo foo1 = new Foo();
        container.registerInstance(IFoo.class,foo1);
        IFoo foo2 = container.resolve(IFoo.class);
        assertSame(foo1, foo2);

    }
    @Test
    void testbuildUp(){
        class NeedsBar {
            @Inject
            private IBar bar;

            public IBar getBar() {
                return bar;
            }
        }
        NeedsBar needsBar = new NeedsBar();
        container.registerTypeMap(IBar.class, Bar.class,false);
        container.buildUp(needsBar);
        assertEquals(needsBar.getBar().getClass(), Bar.class);
    }

}