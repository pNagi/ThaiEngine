#include <stdio.h>
#include <iostream>
#include <vector>
#include <reader.h>

using namespace std;

void print_record(Reader::data_record &record) {
    cout << "id: " << record.header.id
    << " lang: " << record.header.lang
    << " length: " << record.header.length
    << " hasTailSpace: " << record.header.hasTailSpace
    << " isUnused: " << record.header.isUnused
    << " numeric: " << record.header.numeric
    << " _filler: " << record.header._filler
    << " mapFilePos: " << record.header.mapFilePos
    << " timestamp: " << record.timestamp << endl;
    cout << "text: " << record.text << endl << endl;
}

int main(int argc, char* argv[]) {

    while(true) {
        try {
            print(Reader::read());
        } catch (int e) {
            cout << "error!";
            break;
        }
    }

    return 0;
}
