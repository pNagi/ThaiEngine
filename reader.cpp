#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iconv.h>
#include <bitset>

using namespace std;

#define MAX_SYLLABLE_TEXTSIZE 1023

void read_record(ifstream &in, iconv_t conv) {

    uint32_t id;
    uint16_t info;
    uint32_t mapFilePos;
    uint64_t timestamp;
    char raw[MAX_SYLLABLE_TEXTSIZE];
    char text[MAX_SYLLABLE_TEXTSIZE];
    memset(raw, 0, sizeof(raw));
    memset(text, 0, sizeof(text));

    in.read((char*) &id, sizeof(uint32_t));
    cout << "id: " << id;

    in.read((char*) &info, sizeof(uint16_t));

    bitset<2> lang(bitset<2>(info).to_string());
    bitset<10> length(bitset<10>(info >>= 2).to_string());
    bitset<1> hasTailSpace(bitset<1>(info >>= 10).to_string());
    bitset<1> isUnused(bitset<1>(info >>= 1).to_string());
    bitset<1> numeric(bitset<1>(info >>= 1).to_string());
    bitset<1> _filler(bitset<1>(info >>= 1).to_string());

    cout << " lang: " << lang.to_ulong()
    << " length: " << length.to_ulong()
    << " hasTailSpace: " << hasTailSpace.to_ulong()
    << " isUnused: " << isUnused.to_ulong()
    << " numeric: " << numeric.to_ulong()
    << " _filler: " << _filler.to_ulong();

    in.seekg(2, ios::cur);

    in.read((char*) &mapFilePos, sizeof(uint32_t));
    cout << " mapFilePos: " << mapFilePos;

    //check
    in.seekg(8, ios::cur);
    int checker;
    in.read((char*) & checker, sizeof(int));
    in.seekg(-12, ios::cur);

    if (checker != 0) {
        uint32_t time32;
        in.read((char*) &time32, sizeof(uint32_t));
        cout << " timestamp: " << time32 << endl;
    } else {
        in.read((char*) &timestamp, sizeof(uint64_t));
        cout << " timestamp: " << timestamp << endl;

        in.seekg(4, ios::cur);
    }

    for (int i = 0 ; i < length.to_ulong() ; i++) {
        in.read((char*) &raw[i], sizeof(char));
    }

    char* src = &raw[0];
    char* des = &text[0];
    size_t srclen = sizeof(raw);
    size_t deslen = sizeof(text);

    iconv(conv, &src, &srclen, &des, &deslen);
    in.seekg(1, ios::cur);

    cout << "text: " << text << endl << endl;
}

int main(int argc, char* argv[]) {

    ifstream in(argv[1], ios::binary);
    iconv_t conv = iconv_open("UTF-8","CP874");

    in.seekg(256, ios::beg);

    while(!in.eof()) {
        try {
            read_record(in, conv);
        } catch (int e) {
            cout << "error!";
            break;
        }
    }

    iconv_close(conv);

    return 0;
}
