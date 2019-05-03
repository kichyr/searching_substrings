#include"searcher.h"

searcher::searcher(std::string _pattern): pattern(_pattern) {
    len_p = pattern.length();
    bmBc.resize(SIGMA_SIZE);
    bmGs.resize(len_p+1, len_p);
    pre_bmBc();
    pre_bmGs();
};

searcher::~searcher() {
}

void searcher::pre_bmBc() {
    for(int i = 0; i < SIGMA_SIZE; i++)
        bmBc[i] = len_p;
    
    for(int i = 0; i < len_p-1; i++)
        bmBc[static_cast<int>(pattern[i])] = len_p-i-1;
};

void searcher::z_func() {
    int fl = 0;
    z.resize(len_p);
    int l = 0, r = 0;
    for(int i = 0; i < len_p; i++) {
        if(i > l) {
            fl = 1;
            int k;
            for(k = 0; ((len_p-1) - k -i) >= 0 && 
                (pattern[(len_p-1) - k] == pattern[(len_p-1) - k -i]); k++);
            z[len_p-i-1] = k;
            l = i+k-1;
            r = i;
        }
        else if(z[(len_p-1) - (i-r)]+i <= l) {
            fl = 2;
            z[len_p-i-1] = z[(len_p-1) - (i-r)];
        }
        else {
            //not
            fl = 3;
            int k;
            for (k = 0; pattern[(len_p-1) - l - k] != pattern[(len_p-1) - (i-r) - (l - i) - k] && ((len_p-1) - l - k) >= 0; k++);
            z[len_p-i-1] = k +1 + (l - i);
            l += k;
            r = i;
        }
    }
}


void searcher::pre_bmGs() {
    z_func();

    for (int j = 0; j < len_p; j++) bmGs[z[j]] = len_p - 1 - j; //цикл №1
    for (int j = 0, r = 0; j <= len_p - 1; j++) //цикл №2
    if (j + z[j] == len_p)
        for (; r <= j; r++)
        if (bmGs[r] == len_p) bmGs[r] = j;
    //добвляем первй элемент 
    int i;
    for(i = 1; i < len_p && pattern[len_p - i -1] == pattern[len_p - i]; i++);
    bmGs[0] = i;
}

void searcher::BM(char* s, int size_s, std::vector<int>& answer) {
    if(size_s < pattern.length()) return;

    if(!answer.empty())
        answer.clear();

    int k = 0;
    //std::cout << bmGs << std::endl;

    for(int i = len_p-1; i < size_s;) {
        int j, fl = 0;
        for(j = i; j > i-len_p; j--)
            if(s[j] != pattern[len_p - (i - j) -1]) {
                //std::cout << i << " " << j<< " " << std::max(bmBc[s[j]], bmGs[i-j+1]) << std::endl;
                i += std::max(bmBc[s[j]]-(i-j)-1, bmGs[i-j]);
                fl = 1;
                break;
            }
        if(fl == 0)
            answer.push_back(i++);
    }
    //answer.push_back(-1);
}

void searcher::BM(std::string s, std::vector<int>& answer) {
    if(s.length() < pattern.length()) return;

    if(!answer.empty())
        answer.clear();

    int k = 0;
    //std::cout << bmGs << std::endl;

    for(int i = len_p-1; i < s.length();) {
        int j, fl = 0;
        for(j = i; j > i-len_p; j--)
            if(s[j] != pattern[len_p - (i - j) -1]) {
                //std::cout << i << " " << j<< " " << std::max(bmBc[s[j]], bmGs[i-j+1]) << std::endl;
                i += std::max(bmBc[s[j]]-(i-j)-1, bmGs[i-j]);
                fl = 1;
                break;
            }
        if(fl == 0)
            answer.push_back(i++);
    }
    //answer.push_back(-1);
}