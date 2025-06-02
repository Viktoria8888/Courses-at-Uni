package org.example;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.Map;

class Info<From, To extends From> {
    public boolean isSingleton = false;
    public boolean isInstance = false;
    public Class<From> fromType;
    public Class<To> toType;
    public From singletonInstance;
    public Object concreteInstance;
}
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.FIELD)
@interface Inject {
}
public class SimpleContainer {
    private Map<Class<?>, Info<?, ?>> data = new HashMap<>();

    private <T> T createInstance(Class<T> type) {
        try {
            return type.getDeclaredConstructor().newInstance();
        } catch (Exception e) {
            throw new RuntimeException("Cannot create instance of " + type.getName(), e);
        }
    }

    public <T> void registerType(Class<T> type, boolean singleton) {
        if (checkInterfaceOrAbstract(type)) {
            throw new IllegalArgumentException("Cannot register interface or abstract class without mapping");
        }
        Info<T, T> info = new Info<>();
        info.fromType = type;
        info.toType = type;
        info.isSingleton = singleton;
        if (singleton) {
            info.singletonInstance = createInstance(type);
        }
        data.put(type, info);
    }

    public <From, To extends From> void registerTypeMap(Class<From> from, Class<To> to, boolean singleton) {
        if (!checkInterfaceOrAbstract(from)) {
            throw new IllegalArgumentException("From type must be an interface or abstract class");
        }
        if (checkInterfaceOrAbstract(to)) {
            throw new IllegalArgumentException("To type must be a concrete class");
        }
        Info<From, To> info = new Info<>();
        info.fromType = from;
        info.toType = to;
        info.isSingleton = singleton;
        if (singleton) {
            info.singletonInstance = createInstance(to);
        }
        data.put(from, info);
    }
    public <From> void registerInstance(Class<From> from, From instance) {
        if (instance == null) {
            throw new IllegalArgumentException("Instance cannot be null");
        }
        if (!from.isAssignableFrom(instance.getClass())) {
            throw new IllegalArgumentException("Provided instance does not implement/extend the given type");
        }

        Info<From, ?> info = new Info<>();
        info.fromType = from;
        info.isInstance = true;
        info.concreteInstance = instance;

        data.put(from, info);
    }

    public <T> boolean checkInterfaceOrAbstract(Class<T> type) {
        return type.isInterface() || Modifier.isAbstract(type.getModifiers());
    }
    public void buildUp(Object instance) {
        Class<?> clazz = instance.getClass();
        for (Field field : clazz.getDeclaredFields()) {
            if (field.isAnnotationPresent(Inject.class)) {
                Class<?> fieldType = field.getType();
                Object dependency = resolve(fieldType);
                try {
                    field.setAccessible(true);
                    field.set(instance, dependency);
                } catch (IllegalAccessException e) {
                    throw new RuntimeException("Failed to inject dependency into field: " + field.getName(), e);
                }
            }
        }}

    public <T> T resolve(Class<T> type) {
        if (!data.containsKey(type)) {
            if (checkInterfaceOrAbstract(type)) {
                throw new IllegalArgumentException("No registration for interface or abstract class: " + type.getName());
            } else {
                return createInstance(type);
            }
        }
        Info<T, ?> info = (Info<T, ?>) data.get(type);
        if (info.isSingleton) {
            return info.singletonInstance;
        }
        else if (info.isInstance){
            return (T)info.concreteInstance;
        }
        else {
            return createInstance(info.toType);
        }
    }
}