//
// Created by tim on 19.5.17.
//
#include <fstream>
#include <iostream>
#include "CData.hpp"

using namespace std;

CData::CData() {
    m_Encrypted = nullptr;
    m_Data = nullptr;
}

CData::~CData(){
    delete[] m_Data;
    if (m_Encrypted != nullptr)
        delete[] m_Encrypted;
}

void CData::Load(FILE * input){
    m_Size = 100;
    m_Len = 0;
    m_Data = new unsigned char[m_Size];
    while(fread((void *)&m_Data[m_Len++], 1, sizeof(char), input)){
        if (m_Len == m_Size - 1) {
            m_Size *= 2;
            unsigned char *tmp = new unsigned char[m_Size];
            for (uint i = 0; i < m_Size/2; i++)
                tmp[i] = m_Data[i];
            delete[] m_Data;
            m_Data = tmp;
        }
    }
    m_Len--;
}

void CData::PrintData(bool en, bool hex, int des) const {
    if (en) {
        if (des) {
            cout
                    << "Because of better interpretation and comparison, the original and encrypted data will be printed in hexadecimals."
                    << endl;
            cout << "Original:" << endl;
            for (uint i = 0; i < m_Len; i++)
                printf("%02x", m_Data[i]);
            cout << endl << "Encrypted:" << endl;
            for (uint i = 0; i < m_EnLen; i++)
                printf("%02x", m_Encrypted[i]);
            cout << endl;
            return;
        }
        for (uint i = 0; i < m_EnLen; i++)
            if (hex)
                printf("%02x", m_Encrypted[i]);
            else
                cout << m_Encrypted[i];
    }else {
        for (uint i = 0; i < m_Len; i++)
            cout << m_Data[i];
    }
    cout << endl;
}

void CData::Out(FILE * output, bool hex) const {
    if (hex){
        for (uint i = 0; i < m_EnLen; i++){
            fprintf(output, "%02x", m_Encrypted[i]);
        }
    }else {
        for (uint i = 0; i < m_EnLen; i++) {
            fprintf(output, "%c", m_Encrypted[i]);
        }
    }
}