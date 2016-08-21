#include "DES.hpp"

#include <iostream>
#include <vector>

using namespace std;

// for key scheduling

int left_permutation_table[28] = {56, 48, 40, 32, 24, 16, 8,
                                     0, 57, 49, 41, 33, 25, 17,
                                     9, 1, 58, 50, 42, 34, 26,
                                     18, 10, 2, 59, 51, 43, 35};

int right_permutation_table[28] = {62, 54, 46, 38, 30, 22, 14,
                                     6, 61, 53, 45, 37, 29, 21,
                                     13, 5, 60,  52, 44, 36, 28,
                                     20, 12, 4, 27, 19, 11, 3};

int second_permutation_table[48] = {13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9,
                                    22, 18, 11, 3, 25, 7, 15, 6, 26, 19, 12, 1,
                                    40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
                                    43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31};
                                    
int left_shift[16] = {1, 2, 4, 6, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27, 28};


// for encrypting

//initial permutation chart
const std::vector<int> permutArray {58, 50, 42, 34, 26, 18, 10, 2,
                                    60, 52, 44, 36, 28, 20, 12, 4,
                                    62, 54, 46, 38, 30, 22, 14, 6,
                                    64, 56 ,48, 40, 32, 24, 16, 8,
                                    57, 49, 41, 33, 25, 17, 9, 1,
                                    59, 51, 43, 35, 27, 19, 11, 3,
                                    61, 53, 45, 37, 29, 21, 13, 5,
                                    63,55,47,39,31,23,15,7};

//reverse permutation chart
const std::vector<int> reverseArray {40, 8, 48, 16, 56, 24, 64, 32,
                                     39, 7, 47, 15, 55, 23, 63, 31,
                                     38, 6, 46, 14, 54, 22, 62, 30,
                                     37, 5, 45, 13, 53, 21, 61, 29,
                                     36, 4, 44, 12, 52, 20, 60, 28,
                                     35, 3, 43, 11, 51, 19, 59, 27,
                                     34, 2, 42, 10, 50, 18, 58, 26,
                                     33,1,41,9,49,17,57,25};

const std::vector<int> expandTable{32, 1, 2, 3, 4, 5, 4, 5,
                                   6, 7, 8, 9, 8, 9, 10, 11,
                                   12, 13, 12, 13, 14, 15, 16,
                                   17, 16, 17, 18, 19, 20, 21,
                                   20, 21, 22, 23, 24, 25, 24,
                                   25, 26, 27, 28, 29, 28, 29,
                                   30, 31, 32, 1};

const std::vector<int> s1 {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                           0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                           4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                           15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

const std::vector<int> s2 {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                           3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                           0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                           13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

const std::vector<int> s3 {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                           13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                           13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                           1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

const std::vector<int> s4 {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                           13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                           10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                           3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

const std::vector<int> s5 {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                           14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                           4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                           11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};

const std::vector<int> s6 {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                           10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                           9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                           4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

const std::vector<int> s7 {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                           13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                           1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                           6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

const std::vector<int> s8 {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                           1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                           7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                           2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

const std::vector<int> permut{16, 7, 20, 21, 29, 12, 28, 17,
                              1, 15, 23, 26, 5, 18, 31, 10,
                              2, 8, 24, 14, 32, 27, 3, 9, 19,
                              13, 30, 6, 22, 11, 4, 25};

std::vector<std::vector<int>> subBox(9, std::vector<int>(64));


                                                        
subKey_48 KeySchedule(key_64 key_, uint16_t round_n){

    subBox[1] = s1;
    subBox[2] = s2;
    subBox[3] = s3;
    subBox[4] = s4;
    subBox[5] = s5;
    subBox[6] = s6;
    subBox[7] = s7;
    subBox[8] = s8;
    
    std::bitset<28> left;
    std::bitset<28> right;

    // the 56 bits useful key we are going to use for the permutations
    usefulKey_56 base_key;

    // the 48 bits sub key of the round "round" that we are going to return                                       
    subKey_48 returned_key;
    
    // first permutation, gets rid of the parity bits
    for(size_t j = 0; j < 28; ++j)
        right[27 - j] = key_[63 - right_permutation_table[j]];

    for(size_t i = 0; i < 28; ++i)
        left[27 - i] = key_[63 - left_permutation_table[i]];

    // the number of bits that we have to shift in the left direction
    size_t n_iterations = left_shift[round_n-1];

    // left permutation
    for(size_t j = 0; j < n_iterations; ++j){
        int tmp1(left[27]);
        int tmp2(right[27]);
 
        for(size_t i = 1; i < 28 ; ++i){
            left[28-i] = left[28-i-1];
            right[28-i] = right[28-i-1];
        }

        left[0] = tmp1;
        right[0] = tmp2;
    }

    // rebuild the 56 bits useful key
    for(size_t i = 0; i < 28; ++i){
        base_key[i] = right[i];
        base_key[i + 28] = left[i];
    }

  //  cout << "base key " << base_key << std::endl;
    // second permutation
    for(size_t m = 0; m < 48; ++m){
        returned_key[47 - m] = base_key[55 - second_permutation_table[m]];
    }

    return returned_key;
}


ciphertext_64 DESencrypt(plaintext_64 message, key_64 key){
    

    ciphertext_64 ciphertext;

    plaintext_64 mPermuted;
    bitset<32> Left;
    bitset<32> Right;
    bitset<32> RightSub;
    bitset<32> RightPerm;
    bitset<48> RightExpand;
    subKey_48 subKey;

    for(size_t i = 0; i < 24; i++){
        subKey[i] = 1;
    };

    //initial permutation
    for(size_t i = 0; i < 64; i++){
        mPermuted[63-i] = message[64-permutArray[i]];
    }

    //separate Left and Right
    for(size_t i = 0; i < 64; i++){
        if(i < 32) Right[i] = mPermuted[i]; 
        if(i >= 32) Left[i-32] = mPermuted[i]; 
    }

  //  cout << "Left\t" << Left << "\nRight\t" << Right  << endl;

    //round start
    for(size_t round_j = 1; round_j < 17; round_j++){       // 1 to 16
    //expand Right
  //      cout << "Round\t" << round_j << endl;
        for(size_t i = 0; i < 48; i++){
            RightExpand[47-i] = Right[32-expandTable[i]];
        }

        //cout << "RightExpand " << RightExpand << endl;

        subKey = KeySchedule(key, round_j);
  //      cout << "subKey\t" << subKey << endl;

        for(size_t i = 0; i < 48; i++)
            RightExpand[i] = RightExpand[i] ^ subKey[i];
        
        //cout << "RightExpand " << RightExpand << endl;
        int lign(0), val(0), col(0);

        for(size_t i = 0; i < 8; i++){
            lign = 0;
            val = 0;
            col = 0;
            lign = RightExpand[i * 6 + 0] + RightExpand[i * 6 + 5] * 2; //give line number
            col = RightExpand[i * 6 + 1] + RightExpand[i * 6 + 2] * 2 + RightExpand[i * 6 + 3] * 4 + RightExpand[i * 6 + 4] * 8;//give column number
            val = subBox[8-i][lign * 16 + col];//value
            RightSub[i * 4 + 3] = val / 8;
            val = val % 8;
            RightSub[i * 4 + 2] = val / 4;
            val = val % 4;
            RightSub[i * 4 + 1] = val / 2;
            RightSub[i * 4] = val % 2;
        }

        //cout << "Right substituted " << RightSub << endl;
        for(size_t i = 0; i < 32; i++)
            RightPerm[31-i] = RightSub[32-permut[i]];
        
        //xor with Left
        //swap Left and Right;
        for(size_t i = 0; i < 32; i++){
            RightPerm[i] = Left[i] ^ RightPerm[i];
            Left[i] = Right[i];
            Right[i] = RightPerm[i];
        }

 //       cout << "Left\t" << Left << "\tRight\t" << Right << endl;
    }

    //bind Left and Right
    for(size_t i = 0; i < 64; i++){
        if(i < 32) { mPermuted[i] = Left[i]; }
        if(i >= 32) { mPermuted[i] = Right[i-32]; }
    }

 //   cout << "mPermuted\t" << mPermuted << endl;

    //reverse permutation
    for(size_t i = 0; i < 64; i++){
        ciphertext[63-i] = mPermuted[64-reverseArray[i]];
    }
   // cout << "ciphertext\t" << ciphertext<< endl;

    return ciphertext;
}

plaintext_64 DESdecrypt(ciphertext_64 ciphertext_, key_64 key_){

    plaintext_64 plaintext;

    ciphertext_64 cPermuted;
    bitset<32> Left;
    bitset<32> Right;
    bitset<32> RightSub;
    bitset<32> RightPerm;
    bitset<48> RightExpand;
    subKey_48 subKey;
   // cout << "ciphertext\t" << ciphertext_ << endl;
    for(size_t i = 0; i < 24; i++){
        subKey[i] = 1;
    };

    //initial permutation
    for(size_t i = 0; i < 64; i++){
        cPermuted[63-i] = ciphertext_[64-permutArray[i]];
    }

    //separate Left and Right
    for(size_t i = 0; i < 64; i++){
        if(i < 32) Right[i] = cPermuted[i]; 
        if(i >= 32) Left[i-32] = cPermuted[i]; 
    }

    //round start
    for(size_t round_j = 1; round_j < 17; round_j++){       // 1 à 16 ou 0 à 15 ? 
    //expand Right

        for(size_t i = 0; i < 48; i++){
            RightExpand[47-i] = Right[32-expandTable[i]];
        }

        //cout << "RightExpand " << RightExpand << endl;

        subKey = KeySchedule(key_, 17 - round_j);
       // cout << "subKey " << subKey << endl;

        for(size_t i = 0; i < 48; i++)
            RightExpand[i] = RightExpand[i] ^ subKey[i];
        
        //cout << "RightExpand " << RightExpand << endl;
        int lign(0), val(0), col(0);

        for(size_t i = 0; i < 8; i++){
            lign = 0;
            val = 0;
            col = 0;
            lign = RightExpand[i * 6 + 0] + RightExpand[i * 6 + 5] * 2; //give line number
            col = RightExpand[i * 6 + 1] + RightExpand[i * 6 + 2] * 2 + RightExpand[i * 6 + 3] * 4 + RightExpand[i * 6 + 4] * 8;//give column number
            val = subBox[8-i][lign * 16 + col];//value
            RightSub[i * 4 + 3] = val / 8;
            val = val % 8;
            RightSub[i * 4 + 2] = val / 4;
            val = val % 4;
            RightSub[i * 4 + 1] = val / 2;
            RightSub[i * 4] = val % 2;
        }

        //cout << "Right substituted " << RightSub << endl;
        for(size_t i = 0; i < 32; i++)
            RightPerm[31-i] = RightSub[32-permut[i]];
        
        //xor with Left
        //swap Left and Right;
        for(size_t i = 0; i < 32; i++){
            RightPerm[i] = Left[i] ^ RightPerm[i];
            Left[i] = Right[i];
            Right[i] = RightPerm[i];
        }

     //   cout << "Left = " << Left << " Right = " << Right << " Round " << round_j << endl;
    }

    //bind Left and Right
    for(size_t i = 0; i < 64; i++){
        if(i < 32) { cPermuted[i] = Left[i]; }
        if(i >= 32) { cPermuted[i] = Right[i-32]; }
    }

  //  cout << "cPermuted = " << cPermuted << endl;

    //reverse permutation
    for(size_t i = 0; i < 64; i++){
        plaintext[63-i] = cPermuted[64-reverseArray[i]];
    }
   // cout << "plaintext\t" << plaintext<< endl;

    return plaintext;
}