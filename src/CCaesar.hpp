//
// Created by tim on 25.5.17.
//

#ifndef CRYPTTOOL_CCAESAR_HPP
#define CRYPTTOOL_CCAESAR_HPP

#include "CCipher.hpp"

/**
 * This class is for encryption and decryption in Caesar's cipher.
 * It includes parameters shift (for shift of letters) and params (for storing saved parameters during setting parameters.
 */

class CCaesar : public CCipher{
public:
    CCaesar();
    ~CCaesar();
    virtual void SetParam();
    virtual bool Encrypt(CData & Data);
    virtual bool Decrypt(CData & Data);

private:
    int shift;
    int * params;
};

#endif //CRYPTTOOL_CCAESAR_HPP
