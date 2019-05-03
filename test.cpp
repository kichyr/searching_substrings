#include<iostream>
#include<string>
#include<search.h>
#include<vector>
#include<map>
#include<cassert>
#include"searcher.h"
#include<iterator>
using namespace std;

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
//

void print_modifyed_str(string& s, vector<int>& answ) {
    int i = 0;
    auto iterator = s.begin();
    while(i < answ.size()) {
        std::copy (iterator, s.begin()+answ[i]+1, std::ostream_iterator<char>(std::cout));
        std::cout << "*";
        iterator = s.begin() + answ[i] +1;
        i++;
    }
    std::copy (iterator, s.end(), std::ostream_iterator<char>(std::cout));
}

void utest_z_func() {

    searcher search1("aaa");
    search1.z_func();
    vector<int> expected1 = {1,2,0};
    assert(search1.z == expected1);

    //abcdabscabcdabia
    searcher search2("aibadcbacsbadcba");
    search2.z_func();
    vector<int> expected2 = {1,0,0,2,0,0,0,6,0,0,0,2,0,0,0,0};
    assert(search2.z == expected2);

    searcher search3("aaccbccbcc");
    search3.z_func();
    vector<int> expected3 = {0, 0, 1, 2, 0, 1, 5, 0, 1, 0};
    assert(search3.z == expected3);

    cout << "utest_z_func OK" << endl;
}

void test_heuristics() {
    searcher search1("aaccbccbcc");

    search1.pre_bmBc();
    search1.z_func();
    search1.pre_bmGs();
    vector<int> exp_bmGs = {2, 1, 6, 10, 10, 3, 10, 10, 10, 10, 10};
    assert( search1.bmBc[static_cast<int>('c')] == 1 &&  search1.bmBc[static_cast<int>('a') == 9]);
    //cout << search1.bmGs << endl;
    assert(search1.bmGs == exp_bmGs);

    cout << "utest_test_heuristics OK" << endl;
}


void hand_test_BM() {
    string s1 = "dsfjdksolololofaasdololo";
    vector<int> answ;
    searcher search1("ololo");
    search1.BM(s1, answ);
    vector<int> expected1 = {11,13,23};
    assert(answ == expected1);
    
    string s2 = "aaaaaaaaaa";
    searcher search2("aa");
    search2.BM(s2, answ);
    vector<int> expected2 = {1,2,3,4,5,6,7,8,9};
    assert(answ == expected2);
    
    string s3 = "BBBBBBBBB";
    searcher search3("aa");
    search3.BM(s3, answ);
    vector<int> expected3 = {};
    assert(answ == expected3);

    string s4 = "";
    searcher search4("aa");
    search3.BM(s4, answ);
    vector<int> expected4 = {};
    assert(answ == expected4);

    cout << "hand_test_BM OK" << endl;
}

void tests() {
    utest_z_func();
    test_heuristics();
    hand_test_BM();
}




int main() {
    tests();
    return 0;
}