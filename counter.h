#ifndef COUNTER_H
#define COUNTER_H

#include <fstream>
#include <vector>
#include "reader.h"

using namespace std;

namespace Counter {
    class Counter {
    public:
        Counter();
        void push(Reader::data_record);
        int count();
    private:
        vector<Reader::data_record> records;
    };
}

#endif
