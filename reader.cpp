#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iconv.h>

using namespace std;

#define MAX_SYLLABLE_TEXTSIZE 1023

uint32_t id;
uint16_t info;
uint32_t mapFilePos;
int64_t timestamp;

char raw[MAX_SYLLABLE_TEXTSIZE];
char text[MAX_SYLLABLE_TEXTSIZE];

void read_record(ifstream &in, iconv_t conv) {

    memset(raw, 0, sizeof(raw));
    memset(text, 0, sizeof(text));

    in.read((char*) &id, sizeof(uint32_t));
    in.read((char*) &info, sizeof(uint16_t));

    bitset<2> lang(bitset<2>(info).to_string());
    bitset<10> length(bitset<10>(info >>= 2).to_string());
    bitset<1> hasTailSpace(bitset<1>(info >>= 10).to_string());
    bitset<1> isUnused(bitset<1>(info >>= 1).to_string());
    bitset<1> numeric(bitset<1>(info >>= 1).to_string());
    bitset<1> _filler(bitset<1>(info >>= 1).to_string());

    in.seekg(2, ios::cur);
    in.read((char*) &mapFilePos, sizeof(uint32_t));

    //check if 32bit or 64bit file
    in.seekg(8, ios::cur);
    int checker;
    in.read((char*) &checker, sizeof(int));
    in.seekg(-8-sizeof(int), ios::cur);

    if (checker != 0) {
        in.read((char*) &timestamp, sizeof(int32_t));
    } else {
        in.read((char*) &timestamp, sizeof(int64_t));
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

    cout << "id: " << id;
    cout << " lang: " << lang.to_ulong()
    << " length: " << length.to_ulong()
    << " hasTailSpace: " << hasTailSpace.to_ulong()
    << " isUnused: " << isUnused.to_ulong()
    << " numeric: " << numeric.to_ulong()
    << " _filler: " << _filler.to_ulong();
    cout << " mapFilePos: " << mapFilePos;
    cout << " timestamp: " << timestamp << endl;
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
