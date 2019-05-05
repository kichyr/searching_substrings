#include<iostream>
#include <unistd.h>
#include <sys/select.h>
#include <iterator>
#include <fcntl.h>

#include <unistd.h>
#include"searcher.h"
using namespace std;


int default_read = 6;
//overlord <<
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

void print_modifyed_str(char* s, int size_s, vector<int>& answ, int start) {
    int k = 0;
    for(int i = start; i < size_s; i++) {
        cout << s[i];
        if(k < answ.size() && i == answ[k]) {
            cout << "*";
            k++;
        }
    }
}


int main(int argc, char** argv) {
    if(argc < 1) {
        throw("too few arguments");
    }
    string pattern = static_cast<string>(argv[1]);
    searcher search(pattern);
    //
    int readen = 0;
    int patt_len = pattern.length();


    //!!!!!! Длина массива обязательно должна быть вдвое больше длины шаблона!!!!!!!
    int read_at_one_time  = max(2*patt_len+1, default_read);
    int SIZE = read_at_one_time;

    char* input = new char[SIZE];
    //

    vector<int> answ;

    int fd = 1;
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    readen = read(STDIN_FILENO, input, SIZE);
    SIZE = readen;

    while(true){

        search.BM(input, SIZE, answ);
        print_modifyed_str(input, SIZE, answ, SIZE-readen);
        if(SIZE < read_at_one_time)
            break;
        for(int j = 0; j < patt_len-1; j++) {
            input[patt_len - j - 2] = input[SIZE - j -1];
        }
        if((readen = read(STDIN_FILENO, input + patt_len - 1, SIZE - patt_len +1)) < 0){
            throw("can't read");
        };
        SIZE = readen + patt_len - 1;
    }
    delete[](input);
    return 0;
}