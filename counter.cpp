#include "counter.h"

using namespace std;

namespace Counter {

    Counter::Counter() {
        cout << "Declare counter" << endl;
    }

    void Counter::push(Reader::data_record record) {
        records.push_back(record);
        cout << "Hello" << endl;
        Counter::add(record.text, record);
        cout << "Hello2" << endl;
    }

    int Counter::count() {
        return (int) records.size();
    }

    Alphabet* Counter::add(string text, Reader::data_record record) {
        cout << "In add: " << text << endl;
        Alphabet* al;

        if (!Counter::contain(text[0])) {
            cout << text[0] << " not contain" << endl;
            al = Counter::create(text[0], record);
        } else {
            cout << text[0] << " contain" << endl;
            al = Counter::get(text[0]);
            al->records.push_back(record);
        }

        if (text.length() == 1) {
            cout << "end of recursive" << endl;
            return al;
        }

        Counter::addNext(al, Counter::add(text.substr(1), record));
        return al;
    }

    Alphabet* Counter::get(char c) {
        for (Alphabet* al: alphabets) {
            if (al->c == c) {
                return al;
            }
        }

        return nullptr;
    }

    bool Counter::contain(char c) {
        for (Alphabet* al: alphabets) {
            if (al->c == c) {
                return true;
            }
        }

        return false;
    }

    Alphabet* Counter::create(char c, Reader::data_record record) {
        cout << "In create" << endl;
        Alphabet* al = (Alphabet *) malloc(sizeof(Alphabet));
        al->c = c;
        cout << "create" << endl;
        al->records.push_back(record);
        cout << "push back to alphabets" << endl;
        alphabets.push_back(al);
        return al;
    }

    void Counter::addNext(Alphabet* al, Alphabet* next) {
        if (find(al->next.begin(), al->next.end(), next) != al->next.end()) {
            al->next.push_back(next);
        }

        return;
    }
}
