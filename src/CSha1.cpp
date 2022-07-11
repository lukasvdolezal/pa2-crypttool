//
// Created by tim on 31.5.17.
//

#include <openssl/sha.h>
#include "CSha1.hpp"
#include "CData.hpp"

bool CSha1::Encrypt(CData & Data) {
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, Data.m_Data, Data.m_Len);
    Data.m_EnSize = 20;
    Data.m_EnLen = 20;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    SHA1_Final(Data.m_Encrypted, &ctx);
    return false;
}

bool CSha1::Decrypt(CData & Data) {
    cout << "Even the length of your encrypted data is " << Data.m_Len <<  " characters, unfortunately, Sha-1 is only one-way hash algorithm." << endl;
    return false;
}