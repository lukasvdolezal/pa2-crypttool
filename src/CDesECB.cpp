//
// Created by tim on 2.6.17.
//

#include "CDesECB.hpp"
#include "CDes.hpp"
#include <openssl/evp.h>

void CDesECB::SetParam() {
    SetKey(m_Key);
    SetIV(m_IV);
}

bool CDesECB::Encrypt(CData &Data) {
    const EVP_CIPHER * cipher = EVP_des_ecb();
    if (EncryptByDes(cipher, Data, m_Key, m_IV))
        return true;
    return false;
}

bool CDesECB::Decrypt(CData &Data) {
    const EVP_CIPHER * cipher = EVP_des_ecb();
    if (DecryptByDes(cipher, Data, m_Key, m_IV))
        return true;
    return false;
}