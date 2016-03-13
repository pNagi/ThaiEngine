#include "counter.h"

using namespace std;

namespace Counter {

    Counter::Counter() {
    }

    void Counter::push(Reader::data_record record) {
        records.push_back(record);
        if (record.)
    }

    int Counter::count() {
        return records.size();
    }

    Alphabet Counter::add(string text, Reader::data_record record) {
        Alphabet al;

        if (!Counter::contain(text[0])) {
            al = Counter::create(text[0], record);
        } else {
            al = Counter::get(text[0]);
        }

        if (text.length() == 1) {
            return;
        }

        Counter::addNext(al, Counter::add(text.substr(1), record));
        return al;
    }

    Alphabet Counter::get(char c) {
        for (auto it = begin(alphabets) ; it != end (alphabets) ; it++) {
            if (it.c == c) {
                return it;
            }
        }

        return null;
    }

    bool Counter::contain(char c) {
        for (auto it = begin(alphabets) ; it != end (alphabets) ; it++) {
            if (it.c == c) {
                return true;
            }
        }

        return false;
    }

    void Counter::create(char c, record) {
        Alphabet al;
        al.c = c;
        al.records.push_back(record);
    }

    void Counter::addNext(Alphabet al, Alphabet next) {
        if (find(al.next.begin(), al.next.end(), next) != al.next.end()) {
            al.next.push_back(next);
        }

        return;
    }
}
