#include "reader.h"

#define FILE_TYPE_32 32
#define FILE_TYPE_64 64
#define FILEID_SIZE 256
#define MAX_SYLLABLE_TEXTSIZE 1023

using namespace std;

namespace Reader {

    Reader::Reader(char* file_name) {
        in.open(file_name, ios::binary);
        conv = iconv_open("UTF-8","CP874");
        check_file_type();
        in.seekg(256, ios::beg);
    }

    data_record Reader::read() {
        data_record record;

        char text[MAX_SYLLABLE_TEXTSIZE];

        in.read((char*) &record.header, sizeof(record.header));

        if (file_type == FILE_TYPE_64) {
            in.read((char*) &record.timestamp, sizeof(int64_t));
            in.seekg(4, ios::cur);
        } else if (file_type == FILE_TYPE_32) {
            in.read((char*) &record.timestamp, sizeof(int32_t));
        }

        for (int i = 0 ; i < record.header.length ; i++) {
            in.read((char*) &text[i], sizeof(char));
        }

        char* src = &text[0];
        char* des = &record.text[0];
        size_t srclen = sizeof(text);
        size_t deslen = sizeof(record.text);

        iconv(conv, &src, &srclen, &des, &deslen);
        in.seekg(1, ios::cur);

        return record;
    }

    void Reader::close() {
        iconv_close(conv);
    }

    int Reader::check_file_type() {
        data_record record;
        in.seekg(256 + 8 + sizeof(record.header), ios::beg);

        int checker;
        in.read((char*) &checker, sizeof(int));

        if (checker != 0) {
            file_type = FILE_TYPE_32;
        } else {
            file_type = FILE_TYPE_64;
        }

        return file_type;
    }
}
