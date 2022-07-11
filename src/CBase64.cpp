//
// Created by tim on 31.5.17.
//

#include "CBase64.hpp"
#include "CData.hpp"
#include <cstring>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

bool CBase64::Encrypt(CData & Data) {
    BIO * bio, * b64;
    BUF_MEM * buffer;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, Data.m_Data, Data.m_Len);
    if (!BIO_flush(bio)) return true;
    BIO_get_mem_ptr(bio, &buffer);
    if (!BIO_set_close(bio, BIO_NOCLOSE)) return true;
    BIO_free_all(bio);

    Data.m_EnLen = buffer->length;
    Data.m_Encrypted = (unsigned char *) buffer->data;
    return false;
}

bool CBase64::Decrypt(CData & Data) {
    int len = Data.m_Len;
    int pad = 0;
    if (Data.m_Data[len - 1] == '=') {
        pad++;
        if (Data.m_Data[len - 2] == '=')
            pad++;
    }
    Data.m_EnLen = (len*3)/4 - pad;
    Data.m_EnSize = Data.m_EnLen + 1;

    BIO * bio, * b64;
    unsigned char * buffer = new unsigned char[Data.m_EnSize];
    buffer[Data.m_EnLen] = '\0';

    bio = BIO_new_mem_buf(Data.m_Data, Data.m_Len);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_read(bio, buffer, Data.m_Len);
    BIO_free_all(bio);
    Data.m_Encrypted = buffer;
    return false;
}