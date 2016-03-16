#ifndef COUNTER_H
#define COUNTER_H

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iconv.h>
#include "reader.h"

using namespace std;

namespace Counter {
    class Alphabet {
        public:
            char c;
            vector<Alphabet*> next;
            vector<Reader::data_record> records;
            // void push_next(Alphabet&);
            void push_record(Reader::data_record& record) {
                if (find(records.begin(), records.end(), record) == records.end()) {
                    records.push_back(record);
                }
            }
    };

    class Counter {
    public:
        Counter();
        void push(Reader::data_record&);
        int count();
    private:
        Alphabet add(string, Reader::data_record&);
        bool contain(char);
        Alphabet create(char, Reader::data_record&);
        vector<Reader::data_record> records;
        vector<Alphabet> alphabets;
        iconv_t conv;
    };
}

#endif
