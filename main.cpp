#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const int n = 4;
vector<int> SBOX = {0xE, 4, 0xD, 1, 2, 0xF, 0xB, 8, 3, 0xA, 6, 0xC, 5, 9, 0, 7};
vector<int> PERMUTATION = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
vector<string> SUBKEY = {"33ad8723258f090c", "9052653aa9514744", "39b72d5ca62ada15", "d67f50b671754c8b", "1db2004dd278a498"};

vector<int> round(vector<int> input, string subkey){
    vector<int> result(16);
    for (int i = 0; i < n*n; ++i){
        int place = PERMUTATION[i] - 1;
        stringstream ss;
        ss << hex << subkey[i];
        int key_bit;
        ss >> key_bit;
        result[place] = SBOX[input[i] ^ key_bit];
    }
    return result;
}

vector<int> TOY(vector<int> pt){
    vector<int> ct(16);
    for (int i = 0; i < 5; ++i){
        ct = round(pt, SUBKEY[i]);
    }
    ct = round(ct, SUBKEY[4]);
    return ct;
}


int main() {
    
    vector<int> t = TOY({0xc, 0xa, 3, 0xb, 8, 0xd, 0, 8, 0xa, 0xa, 0xe, 2, 5, 0xb, 1, 0xc});
    cout << "Ciphertext: ";
    for (int i = 0; i < n*n; ++i){
        cout << t[i] << ' ';
    }
    cout << endl;
    
    int diff_table[n*n][n*n] {};
    
    for (int i = 0; i < n*n; ++i){
        for (int j = 0; j < n*n; ++j){
            int in_diff = i ^ j;
            int out_diff = SBOX[i] ^ SBOX[j];
            diff_table[in_diff][out_diff]++;
        }
    }
    
    cout << "Distribution Table: \n";
    
    for (int i = 0; i < n*n; ++i){
        for (int j = 0; j < n*n; ++j){
            std::cout << diff_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
