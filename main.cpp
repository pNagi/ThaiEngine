#include <iostream>
#include "reader.h"
#include "counter.h"

using namespace std;

void print_record(Reader::data_record record) {
    cout << "id: " << record.header.id
    << " lang: " << record.header.lang
    << " length: " << record.header.length
    << " hasTailSpace: " << record.header.hasTailSpace
    << " isUnused: " << record.header.isUnused
    << " numeric: " << record.header.numeric
    << " _filler: " << record.header._filler
    << " mapFilePos: " << record.header.mapFilePos
    << " timestamp: " << record.timestamp << endl;
    cout << "text: " << record.text << endl;
}

int main(int argc, char* argv[]) {
    Reader::Reader reader(argv[1]);
    Counter::Counter counter;

    while(reader.has_next()) {
        try {
            Reader::data_record record = reader.read();
            print_record(record);
            counter.push(record);
            cout << "counter: " << counter.count() << endl << endl;
        } catch (int e) {
            cout << "error!";
            break;
        }
    }

    reader.close();
    return 0;
}
