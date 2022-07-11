//
// Created by tim on 31.5.17.
//

#ifndef CRYPTTOOL_CDESCBC_HPP
#define CRYPTTOOL_CDESCBC_HPP

#include "CDes.hpp"
#include "CData.hpp"

class CDesCBC : public CDes{
    virtual void SetParam();
    virtual bool Encrypt(CData & Data);
    virtual bool Decrypt(CData & Data);
private:
    /**
     * This array of char contains encrypting key.
     */
    unsigned char m_Key[EVP_MAX_KEY_LENGTH];
    /**
     * This array of char contains initialization vector.
     */
    unsigned char m_IV[EVP_MAX_IV_LENGTH];
};

#endif //CRYPTTOOL_CDESCBC_HPP
