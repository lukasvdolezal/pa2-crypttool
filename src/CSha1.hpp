//
// Created by tim on 31.5.17.
//

#ifndef CRYPTTOOL_CSHA1_HPP
#define CRYPTTOOL_CSHA1_HPP

#include "CCipher.hpp"
#include "CData.hpp"

/**
 * This class is for encrypting and decrypting data in SHA1 hash.
 */

class CSha1 : public CCipher {
    virtual bool Encrypt(CData & Data);
    virtual bool Decrypt(CData & Data);
};

#endif //CRYPTTOOL_CSHA1_HPP
