#include "counter.h"

using namespace std;

namespace Counter {

    Counter::Counter() {
    }

    void Counter::push(Reader::data_record record) {
        records.push_back(record);
    }

    int Counter::count() {
        return records.size();
    }
}
