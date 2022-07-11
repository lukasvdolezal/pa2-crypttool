//
// Created by tim on 30.5.17.
//

#ifndef CRYPTTOOL_CVIGENER_HPP
#define CRYPTTOOL_CVIGENER_HPP

#include "CCipher.hpp"
#include "CData.hpp"

/**
 * This class allows user to encrypt and decrypt data with Vigener's cipher.
 */

class CVigener : public CCipher{
public:
    ~CVigener();
    /**
     * This method initializes matrix for Vigener's cipher.
     */
    void Init();
    virtual void SetParam();
    virtual bool Encrypt(CData & Data);
    virtual bool Decrypt(CData & Data);
private:
    /**
     * This array of arrays contains matrix for Vigener's cipher.
     */
    char ** m_AlfaMatrix;
    /**
     * This string is key for encrypting and decrypting with Vigener's cipher.
     */
    string m_Key;
};

#endif //CRYPTTOOL_CVIGENER_HPP
