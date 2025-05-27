package model;

import jakarta.persistence.*;
import java.util.*;

@Entity
public class Parent {
    @Id
    @GeneratedValue
    private Long id;

    private String name;

    @OneToMany(mappedBy = "parent", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Child> children = new ArrayList<>();

    // constructors
    public Parent() {}
    public Parent(String name) {
        this.name = name;
    }

    // getters/setters
    public Long getId() { return id; }
    public String getName() { return name; }
    public List<Child> getChildren() { return children; }

    public void addChild(Child child) {
        children.add(child);
        child.setParent(this);
    }

    public void removeChild(Child child) {
        children.remove(child);
        child.setParent(null);
    }

    public void setName(String name) {
        this.name = name;
    }
}


package model;

import jakarta.persistence.*;

@Entity
public class Child {
    @Id
    @GeneratedValue
    private Long id;

    private String name;

    @ManyToOne
    @JoinColumn(name = "parent_id")
    private Parent parent;

    // constructors
    public Child() {}
    public Child(String name) {
        this.name = name;
    }

    // getters/setters
    public Long getId() { return id; }
    public String getName() { return name; }
    public Parent getParent() { return parent; }

    public void setName(String name) {
        this.name = name;
    }

    public void setParent(Parent parent) {
        this.parent = parent;
    }
}

import model.*;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

public class Main {
    public static void main(String[] args) {
        Configuration config = new Configuration().configure();
        try (SessionFactory sessionFactory = config.buildSessionFactory();
             Session session = sessionFactory.openSession()) {

            session.beginTransaction();

            Parent parent = new Parent("Parent 1");
            Child child1 = new Child("Child A");
            Child child2 = new Child("Child B");

            parent.addChild(child1);
            parent.addChild(child2);

            session.persist(parent);  // CascadeType.ALL saves children too

            session.getTransaction().commit();

            // Read from DB
            session.beginTransaction();
            Parent loaded = session.get(Parent.class, parent.getId());
            System.out.println("Loaded: " + loaded.getName());
            for (Child c : loaded.getChildren()) {
                System.out.println(" - Child: " + c.getName());
            }
            session.getTransaction().commit();
        }
    }
}
