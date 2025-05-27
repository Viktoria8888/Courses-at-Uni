package org.example;

import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.Map;

public class SimpleContainer {

    private Map<Class<?>, Object> singletons = new HashMap<>();
    private Map<Class<?>, Class<?>> registrations = new HashMap<>();
    private Map<Class<?>, Boolean> singletonFlags = new HashMap<>();

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
        singletonFlags.put(type, singleton);
        if (singleton) {
            T instance = createInstance(type);
            singletons.put(type, instance);
        }
        registrations.put(type, type);
    }

    public <From, To extends From> void registerTypeMap(Class<From> from, Class<To> to, boolean singleton) {
        if (!checkInterfaceOrAbstract(from)) {
            throw new IllegalArgumentException("From type must be an interface or abstract class");
        }
        if (checkInterfaceOrAbstract(to)) {
            throw new IllegalArgumentException("To type must be a concrete class");
        }
        registrations.put(from, to);
        singletonFlags.put(from, singleton);
        if (singleton) {
            To instance = createInstance(to);
            singletons.put(from, instance);
        }
    }

    public <T> boolean checkInterfaceOrAbstract(Class<T> type) {
        return type.isInterface() || Modifier.isAbstract(type.getModifiers());
    }

    public <T> T resolve(Class<T> type) {
        if (!registrations.containsKey(type)) {
            if (checkInterfaceOrAbstract(type)) {
                throw new IllegalArgumentException("No registration for interface or abstract class: " + type.getName());
            } else {
                return createInstance(type);
            }
        }
        if (singletonFlags.getOrDefault(type, false)) {

            return type.cast(singletons.get(type));
        } else {
            Class<?> impl = registrations.get(type);
            return type.cast(createInstance(impl));
        }
    }
}