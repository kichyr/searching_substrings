#include<string>
#include<vector>
//del
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

    void pre_bmBc();
    void pre_bmGs();

    //tests
    friend void utest_z_func();
    friend void test_heuristics();

    /*
    для строки вычисляет массив, в i-ой ячейке которого лежит размер максимального суффикса строки 
    s[1,..i], являющегося также суффиксом всей строки s, здесь s- pattern
    */
    void z_func();

public:
    searcher(std::string _pattern);
    ~searcher();
    int search_it(std::string& sample);// ищет в строке sample подстроку
};
