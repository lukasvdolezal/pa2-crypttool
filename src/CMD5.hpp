//
// Created by tim on 19.5.17.
//

#ifndef CRYPTTOOL_CMD5_H
#define CRYPTTOOL_CMD5_H

#include "CCipher.hpp"
#include "CData.hpp"

/**
 * This class is for encrypting and decrypting data in MD5 hash.
 */

class CMD5 : public CCipher{
    virtual bool Encrypt(CData & Data);
    virtual bool Decrypt(CData & Data);
};

#endif //CRYPTTOOL_CMD5_H
