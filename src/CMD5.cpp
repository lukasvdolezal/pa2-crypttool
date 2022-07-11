//
// Created by tim on 19.5.17.
//

#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include "CMD5.hpp"
#include "CData.hpp"

using namespace std;

bool CMD5::Encrypt(CData & Data) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, Data.m_Data, Data.m_Len);
    Data.m_EnSize = 16;
    Data.m_EnLen = 16;
    Data.m_Encrypted = new unsigned char[16];
    MD5_Final(Data.m_Encrypted, &ctx);
    return false;
}

bool CMD5::Decrypt(CData & Data) {
    cout << "Even the length of your data is " << Data.m_Len << " characters, unfortunately, MD5 is only one-way hash algorithm." << endl;
    return false;
}