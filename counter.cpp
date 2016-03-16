#include "counter.h"

using namespace std;

namespace Counter {

    Counter::Counter() {
        cout << "Declare counter" << endl;
        conv = iconv_open("UTF-8","CP874");
    }

    void Counter::push(Reader::data_record& record) {
        records.push_back(record);
        // cout << "Hello" << endl;
        Counter::add(record.text, record);
        // cout << "Hello2" << endl;
    }

    int Counter::count() {
        return (int) records.size();
    }

    Alphabet Counter::add(string text, Reader::data_record& record) {
        // cout << "In add: " << text << endl;

        char test[1023];
        memset(test, 0, sizeof(text));

        cout << text[0] << endl;
        Alphabet al;

        char* src = &text[0];
        char* des = &test[0];
        size_t srclen = sizeof(text);
        size_t deslen = sizeof(test);

        iconv(conv, &src, &srclen, &des, &deslen);
        cout << "original:" << record.text << endl;
        cout << "text:    " << text << endl;
        // cout << "text[0]: " << text[0] << endl;
        cout << "test:    " << test << endl;
        // cout << "test[0]: " << test[0] << endl;

        if (!Counter::contain(text[0])) {
            // cout << text[0] << " not contain" << endl;
            al = Counter::create(text[0], record);
        } else {
            // cout << text[0] << " contain" << endl;
            for (Alphabet a: alphabets) {
                if (a.c == text[0]) {
                    al = a;
                }
            }
            al.push_record(record);
        }

        // cout << string(1, al.c) << ": ";
        // for (Reader::data_record record: al.records) {
        //     cout << record.text << " ";
        // }
        // cout << endl;

        if (text.length() <= 1) {
            cout << "end of recursive" << endl;
            return al;
        }

        // Alphabet next = Counter::add(text.substr(1), record);
        // al.push_next(&next);

        return al;
    }

    bool Counter::contain(char c) {
        for (Alphabet al: alphabets) {
            if (al.c == c) {
                return true;
            }
        }

        return false;
    }

    Alphabet Counter::create(char c, Reader::data_record& record) {
        // cout << "In create" << endl;
        Alphabet al;

        al.c = c;

        // cout << "create: " << c << endl;
        al.records.push_back(record);
        // cout << "push back to alphabets" << endl;
        alphabets.push_back(al);
        return al;
    }

    bool operator==(const Alphabet& a, const Alphabet& b) {
        return a.c == b.c;
    }

    // void Alphabet::push_next(Alphabet& n) {
    //     if (find(next.begin(), next.end(), n) == next.end()) {
    //         next.push_back(next);
    //     }
    // }
}
