#ifndef READER_H
#define READER_H

#include <fstream>
#include <iconv.h>

#define MAX_SYLLABLE_TEXTSIZE 1023

using namespace std;

namespace Reader {
    class data_record {
    public:
        struct header {
            uint32_t id;
            uint16_t lang: 2;
            uint16_t length: 10;
            uint16_t hasTailSpace: 1;
            uint16_t isUnused: 1;
            uint16_t numeric: 1;
            uint16_t _filler: 1;
            uint32_t mapFilePos;
        } header;
        int64_t timestamp;
        char text[MAX_SYLLABLE_TEXTSIZE];
        bool operator==(const data_record& a) {
            return a.header.id == header.id
                && a.header.lang == header.lang
                && a.header.length == header.length
                && a.header.hasTailSpace == header.hasTailSpace
                && a.header.isUnused == header.isUnused
                && a.header.numeric == header.numeric
                && a.header._filler == header._filler
                && a.header.mapFilePos == header.mapFilePos
                && a.timestamp == timestamp
                && a.text == text;
        }
    };

    class Reader {
    public:
        Reader(char*);
        data_record read();
        bool has_next();
        void close();
    private:
        ifstream in;
        iconv_t conv;
        int file_type;
        int check_file_type();
    };
}

#endif
