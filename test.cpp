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
    int exp_bmGs[] = {7,7,7,2,7,4,7,1};
    //cout << search1.bmGs[0];
    //sassert( search1.bmBc[static_cast<int>('c')] == 6 &&  search1.bmBc[static_cast<int>('a') == 1]);
    cout << search1.z << endl;
    cout << search1.bmGs << endl;
    //assert(is_eq_arrays(search1.bmGs, exp_bmGs, 8));
}


int main() {
    utest_z_func();
    test_heuristics();
    return 0;
}