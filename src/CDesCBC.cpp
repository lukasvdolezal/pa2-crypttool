//
// Created by tim on 31.5.17.
//

#include "CDesCBC.hpp"
#include "CDes.hpp"
#include <openssl/evp.h>

void CDesCBC::SetParam() {
    SetKey(m_Key);
    SetIV(m_IV);
}

bool CDesCBC::Encrypt(CData &Data) {
    const EVP_CIPHER * cipher = EVP_des_cbc();
    if (EncryptByDes(cipher, Data, m_Key, m_IV))
        return true;
    return false;
}

bool CDesCBC::Decrypt(CData &Data) {
    const EVP_CIPHER * cipher = EVP_des_cbc();
    if (DecryptByDes(cipher, Data, m_Key, m_IV))
        return true;
    return false;
}