//
// Created by tim on 31.5.17.
//

#ifndef CRYPTTOOL_CBASE64_HPP
#define CRYPTTOOL_CBASE64_HPP

#include "CCipher.hpp"
#include "CData.hpp"

/**
 * This class is for encryption and decryption in Base64.
 */

class CBase64 : public CCipher{
    virtual bool Encrypt(CData & Data);
    virtual bool Decrypt(CData & Data);
};

#endif //CRYPTTOOL_CBASE64_HPP
