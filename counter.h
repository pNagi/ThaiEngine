#ifndef COUNTER_H
#define COUNTER_H

#include <fstream>
#include <vector>
#include "reader.h"

using namespace std;

namespace Counter {
    class Alphabet {
        char c;
        vector<alphabet> next;
        vector<Reader::data_record> records;
    };

    class Counter {
    public:
        Counter();
        void push(Reader::data_record);
        int count();
    private:
        void add();
        bool contain();
        void create();
        void addNext();
        vector<Reader::data_record> records;
        vector<Alphabet> alphabets;
    };
}

#endif
