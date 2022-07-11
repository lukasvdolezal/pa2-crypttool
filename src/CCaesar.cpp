//
// Created by tim on 25.5.17.
//

#include "CCaesar.hpp"
#include "MyLibrary.hpp"
#include <iostream>
#include <fstream>

using namespace std;

CCaesar::CCaesar() {
    params = nullptr;
}

CCaesar::~CCaesar() {
    if (params != nullptr)
        delete[] params;
}

void CCaesar::SetParam() {
    string file = "src/params/caesar.par";
    ifstream saved_params;
    ofstream out_params;
    int count = 0;
    string choice;
    bool own = false;
    bool save = false;
    saved_params.open(file, ios::binary);
    if (saved_params >> count) {
        params = new int[count];
        for (int i = 0; i < count; i++) {
            saved_params >> params[i];
        }
    }
    saved_params.close();
    own = YNChoice("Do you want to choose your own shift? (y/n) ");
    if(own){
        cout << "Type a shift: ";
        shift = ValidNumber("Please enter valid number between 0 and 25 (included): ", 0, 25);
    }else{
        cout << "Select a number of the shift please:" << endl;
        cout << "<For default value type \"0\">" << endl;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ": " << params[i] << endl;
        }
        int tmp = ValidNumber("Please enter valid number:", 0, count);
        if (tmp == 0)
            shift = 3;
        else
            shift = params[tmp-1];
    }
    if (own)
        save = YNChoice("Do you want to save parameter? (y/n): ");
    if (save){
        out_params.open(file, ios::binary);
        count++;
        out_params << count << endl;
        for (int i = 0; i < count - 1; i++)
            out_params << params[i] << endl;
        out_params << shift << endl;
        out_params.close();
    }
}

bool CCaesar::Encrypt(CData & Data) {
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] > 96 && (int)Data.m_Data[i] < 123) {
            Data.m_Data[i] = toupper(Data.m_Data[i]);
        }
    }
    Data.m_EnSize = Data.m_Size;
    Data.m_EnLen = Data.m_Len;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] > 64 && (int)Data.m_Data[i] < 91) {
            Data.m_Data[i] = (int) Data.m_Data[i] - 65;
            Data.m_Encrypted[i] = (((int) Data.m_Data[i] + shift) % 26) + 65;
        }else{
            Data.m_Encrypted[i] = Data.m_Data[i];
        }
    }
    return false;
}

bool CCaesar::Decrypt(CData &Data) {
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] > 96 && (int)Data.m_Data[i] < 123) {
            Data.m_Data[i] = toupper(Data.m_Data[i]);
        }
    }
    Data.m_EnSize = Data.m_Size;
    Data.m_EnLen = Data.m_Len;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] > 64 && (int)Data.m_Data[i] < 91) {
            Data.m_Data[i] = (int) Data.m_Data[i] - 65;
            int tmp = ((int) Data.m_Data[i] - shift);
            if (tmp < 0) tmp += 26;
            Data.m_Encrypted[i] = tmp + 65;
        }else{
            Data.m_Encrypted[i] = Data.m_Data[i];
        }
    }
    return false;
}