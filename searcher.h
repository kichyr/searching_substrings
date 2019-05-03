#include<string>
#include<vector>
#include<iostream>
//
class searcher {
private:
    //размер алфавита
    int SIGMA_SIZE = 256;
    std::vector<int> bmBc; //сдвиг плохих символов
    std::vector<int> bmGs; //сдвиг хорошего суффикса
    std::string pattern;
    int len_p;
    std::vector<int> z;

    //вычисление смещения плохого символа, заполняет bmBs
    void pre_bmBc();
    //вычисление смещения хорошего суффикса, заполняет bmGs
    void pre_bmGs();

    //tests
    friend void utest_z_func();
    friend void test_heuristics();
    friend void test_BM();

    /*
    для строки вычисляет массив, в i-ой ячейке которого лежит размер максимального суффикса строки 
    s[1,..i], являющегося также суффиксом всей строки s, здесь s- pattern
    */
    void z_func();

public:
    searcher(std::string _pattern);
    ~searcher();
    /*
    Основной алгоритм, записывает в вектор номера вхождений строки pattern
    в заданную строку s
    */
    void BM(char* s,int size_s, std::vector<int>& answer);
    void BM(std::string s, std::vector<int>& answer);


};
