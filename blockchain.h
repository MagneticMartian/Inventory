#include "block.h"

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

class Blockchain {
public:
    Blockchain();
    void AddBlock(Block bNew);
private:
    uint32_t nDifficulty;
    std::forward_list<Block> flM5Block;
};

#endif
