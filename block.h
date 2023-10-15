#include <cstdint>
#include <sstream>
#include "m5_data.h"

#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
    std::string prevHash;

    Block(uint32_t nIndexIn, const m5Data& m5dIn);
    std::string getHash();
    void MineBlock(uint32_t nDifficulty);
private:
    uint32_t nIndex;
    int64_t  nNonce;
    m5Data   m5d;
    std::string sHash;
    time_t   tTime;

    std::string calculateHash();
};

#endif
