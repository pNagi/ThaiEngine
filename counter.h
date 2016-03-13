#ifndef COUNTER_H
#define COUNTER_H

#include <fstream>
#include <vector>
#include <iostream>
#include "reader.h"

using namespace std;

namespace Counter {
    class Alphabet {
        public:
            char c;
            vector<Alphabet*> next;
            vector<Reader::data_record> records;
    };

    class Counter {
    public:
        Counter();
        void push(Reader::data_record);
        int count();
    private:
        Alphabet* add(string, Reader::data_record);
        Alphabet* get(char);
        bool contain(char);
        Alphabet* create(char, Reader::data_record);
        void addNext(Alphabet*, Alphabet*);
        vector<Reader::data_record> records;
        vector<Alphabet*> alphabets;
    };
}

#endif
