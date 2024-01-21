
/*    Zdefiniuj klasę opakowującą plik tekstowy line_writer. Obiekt takiej klasy ma przetrzymywać wskaźnik/referencję do strumienia plikowego ofstream stworzonego i otwartego w konstruktorze. Zadaniem obiektów tej klasy będzie pisanie do pliku wiersz po wierszu. Klasa ta powinna zamykać strumień w destruktorze.
    W programie głównym stwórz kilka wskaźników shared_ptr odnoszących się do tego samego obiektu plikowego. Niech każdy fragment programu posiadający taki własny wskaźnik zapisze w tym pliku swoje dane. Plik powinien zostać zamknięty dopiero, gdy wszystkie sprytne wskaźniki zostaną zlikwidowane. */
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

class line_writer {
public:
    line_writer(const string& filename) {
        file = make_shared<ofstream>(filename, ios::out);
    }

    void writeLine(const string& line) {
        if (file->is_open()) {
            *file << line << endl;
        }
    }

    ~line_writer() {
        if (file->is_open()) {
            file->close();
        }
    }

private:
    shared_ptr<ofstream> file;
};

int main() {
    string filename = "del00.txt";

    shared_ptr<line_writer> example = make_shared<line_writer>(filename);
    example->writeLine("EXAMPLE POINTER");
    shared_ptr<line_writer> shared_file1 = example;
    shared_file1->writeLine("Shared_file1");
    shared_ptr<line_writer> shared_file2 = shared_file1;
    shared_file2->writeLine("Shared_file2");



    return 0;
}
