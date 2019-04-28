#include"searcher.h"

searcher::searcher(std::string _pattern): pattern(_pattern) {
    len_p = pattern.length();
    bmBc.resize(SIGMA_SIZE);
    bmGs.resize(len_p+1);
};

searcher::~searcher() {
}

void searcher::pre_bmBc() {
    for(int i = 0; i < SIGMA_SIZE; i++)
        bmBc[i] = len_p;
    
    for(int i = 0; i < len_p; i++)
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
        std::cout << l << " " << r << " flag: " << fl << std::endl;
    }
}



void searcher::pre_bmGs() {
    for (int j = len_p - 1; j > 0; j--) bmGs[len_p - z[j]] = j; //цикл №1
    for (int j = 1, r = 0; j <= len_p - 1; j++) //цикл №2
    if (j + z[j] == len_p)
        for (; r <= j; r++)
        if (bmGs[r] == len_p) bmGs[r] = j;
}