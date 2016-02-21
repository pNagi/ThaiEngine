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
