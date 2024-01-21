#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>

using namespace std;

enum gender { male = 0, female = 1 };

class Llama {
public:
    Llama(const string& name,
        shared_ptr<Llama> m = nullptr,
        shared_ptr<Llama> f = nullptr) : name(name), mother(m), father(f){
        cout << "Lama " << name << " dołączyła się." << endl;
    }

    ~Llama() {
        cout << "Lama " << name << " opuściła :(" << endl;
    }

    bool operator<(const Llama& other) const {
        return name < other.name;
    }

    void AddChild(shared_ptr<Llama> child) {
        children.push_back(child);
    }

    void RemoveChild(shared_ptr<Llama> child) {
        for (auto it = children.begin(); it != children.end(); ++it) {
            if (auto lockedChild = it->lock()) {
                if (lockedChild == child) {
                    children.erase(it);
                    break;
                }
            }
        }
    }

private:
    string name;
    gender gender_lama;
    shared_ptr<Llama> father;
    shared_ptr<Llama> mother;
    vector<weak_ptr<Llama>> children;
};

int main() {
    set<shared_ptr<Llama>> herd;

    shared_ptr<Llama> mother = make_shared<Llama>("Mama Llama");
    shared_ptr<Llama> father = make_shared<Llama>("Tata Llama");

    shared_ptr<Llama> child1 = make_shared<Llama>("Dziecko 1", mother, father);
    shared_ptr<Llama> child2 = make_shared<Llama>("Dziecko 2", mother, father);

    mother->AddChild(child1);
    mother->AddChild(child2);

    herd.insert(mother);
    herd.insert(father);
    herd.insert(child1);
    herd.insert(child2);

    herd.erase(child1);
    child1.reset();
    return 0;
}
