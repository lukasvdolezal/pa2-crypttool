//
// Created by tim on 2.6.17.
//

#include "CDes.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <openssl/evp.h>
#include "MyLibrary.hpp"
#include "CData.hpp"

void CDes::SetKey(unsigned char * m_Key) {
    string file = "src/params/Key.par";
    ifstream saved_params;
    ofstream out_params;
    string * params;
    int count = 0;
    bool own = false;
    bool save = false;
    saved_params.open(file, ios::binary);
    if (saved_params >> count) {
        params = new string[count];
        for (int i = 0; i < count; i++) {
            saved_params >> params[i];
        }
    }
    saved_params.close();
    own = YNChoice("Do you want to choose your own key? (y/n) ");
    if(own){
        cout << "Type a key: ";
        cin >> m_Key;
    }else{
        cout << "Select a number of the key please:" << endl;
        cout << "<For default value type \"0\">" << endl;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ": " << params[i] << endl;
        }
        int tmp = ValidNumber("Please enter valid number:", 0, count);
        if (tmp == 0)
            strcpy((char *) m_Key, "key");
        else
            strcpy((char *) m_Key, params[tmp-1].c_str());
    }
    if (own)
        save = YNChoice("Do you want to save parameter (y/n): ");
    if (save){
        out_params.open(file, ios::binary);
        count++;
        out_params << count << endl;
        for (int i = 0; i < count - 1; i++)
            out_params << params[i] << endl;
        out_params << m_Key << endl;
        out_params.close();
    }
    delete[] params;
}

void CDes::SetIV(unsigned char * m_IV) {
    string file = "src/params/IV.par";
    ifstream saved_params;
    ofstream out_params;
    int count = 0;
    bool own = false;
    bool save = false;
    string * params;
    saved_params.open(file, ios::binary);
    if (saved_params >> count) {
        params = new string[count];
        for (int i = 0; i < count; i++) {
            saved_params >> params[i];
        }
    }
    saved_params.close();
    own = YNChoice("Do you want to choose your own initialization vector? (y/n) ");
    if(own){
        cout << "Type a vector: ";
        cin >> m_IV;
    }else{
        cout << "Select a number of the vector please:" << endl;
        cout << "<For default value type \"0\">" << endl;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ": " << params[i] << endl;
        }
        int tmp = ValidNumber("Please enter valid number:", 0, count);
        if (tmp == 0)
            strcpy((char *) m_IV, "vector");
        else
            strcpy((char *) m_IV, params[tmp-1].c_str());
    }
    if (own)
        save = YNChoice("Do you want to save parameter (y/n): ");
    if (save){
        out_params.open(file, ios::binary);
        count++;
        out_params << count << endl;
        for (int i = 0; i < count - 1; i++)
            out_params << params[i] << endl;
        out_params << m_IV << endl;
        out_params.close();
    }
    delete[] params;
}

int CDes::Read(unsigned char * data, int & left, int & pos, unsigned char * pole){
    if (left == 0)
        return 0;
    if (left > 8){
        for (int i = 0; i < 8; i++)
            pole[i] = data[pos + i];
        pos += 8;
        left -= 8;
        return 8;
    }else{
        int tmp = left;
        for (int i = 0; i < left; i++)
            pole[i] = data[pos + i];
        left = 0;
        return tmp;
    }
}

void CDes::Write(unsigned char * out, int & outlen, int & poslen, unsigned char * encrypted){
    for (int i = 0; i < outlen; i++)
        encrypted[poslen + i] = out[i];
    poslen += outlen;
}

bool CDes::EncryptByDes(const EVP_CIPHER * cipher, CData & Data, unsigned char key[], unsigned char iv[]) {
    OpenSSL_add_all_ciphers();

    EVP_CIPHER_CTX ctx;
    unsigned char tkey[EVP_MAX_KEY_LENGTH] = "k";
    unsigned char tiv[EVP_MAX_IV_LENGTH] = "i";
    strcpy((char *)tkey,(char *) key);
    strcpy((char *)tiv,(char *) iv);

    unsigned char pole[8];
    unsigned char out[8];

    Data.m_EnSize = Data.m_Size + 8;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    EVP_EncryptInit(&ctx, cipher, tkey, tiv);
    int res, left = Data.m_Len, pos = 0, outlen = 0, poslen = 0;
    while((res = Read(Data.m_Data, left, pos, pole))){
        cout << "O: ";
        for (int j = 0; j < res; j++) {
            printf("%02x", pole[j]);
        }
        cout << endl;
        EVP_EncryptUpdate(&ctx, out, &outlen, pole, res);
        Write(out, outlen, poslen, Data.m_Encrypted);
        cout << "S: ";
        for (int j = 0; j < outlen; j++) {
            printf("%02x", out[j]);
        }
        cout << endl;
    }
    EVP_EncryptFinal(&ctx, out, &outlen);
    Write(out, outlen, poslen, Data.m_Encrypted);
    cout << "F: ";
    for (int j = 0; j < outlen; j++) {
        printf("%02x", out[j]);
    }
    cout << endl;
    Data.m_EnLen = poslen;
    EVP_CIPHER_CTX_cleanup(&ctx);
    return false;
}

bool CDes::DecryptByDes(const EVP_CIPHER * cipher, CData & Data, unsigned char key[], unsigned char iv[]) {
    OpenSSL_add_all_ciphers();

    EVP_CIPHER_CTX ctx;
    unsigned char tkey[EVP_MAX_KEY_LENGTH] = "k";
    unsigned char tiv[EVP_MAX_IV_LENGTH] = "i";
    strcpy((char *)tkey,(char *) key);
    strcpy((char *)tiv,(char *) iv);

    unsigned char pole[8];
    unsigned char out[8];

    Data.m_EnSize = Data.m_Size + 8;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    EVP_EncryptInit(&ctx, cipher, tkey, tiv);
    int res, left = Data.m_Len, pos = 0, outlen = 0, poslen = 0;
    while((res = Read(Data.m_Data, left, pos, pole))){
        cout << "O: ";
        for (int j = 0; j < res; j++) {
            printf("%02x", pole[j]);
        }
        cout << endl;
        EVP_EncryptUpdate(&ctx, out, &outlen, pole, res);
        Write(out, outlen, poslen, Data.m_Encrypted);
        cout << "S: ";
        for (int j = 0; j < outlen; j++) {
            printf("%02x", out[j]);
        }
        cout << endl;
    }
    EVP_EncryptFinal(&ctx, out, &outlen);
    Write(out, outlen, poslen, Data.m_Encrypted);
    cout << "F: ";
    for (int j = 0; j < outlen; j++) {
        printf("%02x", out[j]);
    }
    cout << endl;
    Data.m_EnLen = poslen;
    EVP_CIPHER_CTX_cleanup(&ctx);
    return false;
}
