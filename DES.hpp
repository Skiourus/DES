#ifndef DES_E
#define DES_E

#include <bitset>
#include <cstdint>

typedef std::bitset<48> subKey_48;
typedef std::bitset<56> usefulKey_56;
typedef std::bitset<64> key_64;
typedef std::bitset<64> plaintext_64;
typedef std::bitset<64> ciphertext_64;

subKey_48 KeySchedule(const key_64 key_, const uint16_t round);

ciphertext_64 DESencrypt(plaintext_64 message_, key_64 key_);

plaintext_64 DESdecrypt(ciphertext_64 ciphertext_, key_64 key_);

#endif 