//
// Created by tim on 30.5.17.
//

#include <fstream>
#include <iostream>
#include "CVigener.hpp"
#include "MyLibrary.hpp"

CVigener::~CVigener() {
    for (int i = 0; i < 26; i++)
        delete[] m_AlfaMatrix[i];
    delete[] m_AlfaMatrix;
}

void CVigener::SetParam() {
    string * params;
    string file = "src/params/vigener.par";
    ifstream saved_params;
    ofstream out_params;
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
        while(1) {
            cin >> m_Key;
            bool br = true;
            if (m_Key.size() != 0){
                for (uint i = 0; i < m_Key.size(); i++) {
                    if ((int) m_Key.at(i) > 96 && (int) m_Key.at(i) < 123)
                        m_Key.at(i) = toupper(m_Key.at(i));
                    else if ((int) m_Key.at(i) < 65 || (int) m_Key.at(i) > 90)
                        br = false;
                }
                if (br) break;
            }
            cout << "Please, type a key." << endl;
        }
    }else{
        cout << "Select a number of the key, please:" << endl;
        cout << "<For default value type \"0\">" << endl;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ": " << params[i] << endl;
        }
        int tmp = ValidNumber("Please enter valid number:", 0, count);
        if (tmp == 0)
            m_Key = "KEY";
        else
            m_Key = params[tmp-1];
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

void CVigener::Init() {
    m_AlfaMatrix = new char * [26];
    for (int i = 0; i < 26; i++)
        m_AlfaMatrix[i] = new char[26];
    int first = 65;
    for (int i = 0; i < 26; i ++ ){
        int second = first;
        for (int j = 0; j < 26; j++){
            m_AlfaMatrix[i][j] = (char) second;
            second++;
            if (second == 91) second = 65;
        }
        first++;
    }
}

bool CVigener::Encrypt(CData &Data) {
    Init();
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] > 96 && (int)Data.m_Data[i] < 123) {
            Data.m_Data[i] = toupper(Data.m_Data[i]);
        }else if ((int)Data.m_Data[i] == 10 || (int)Data.m_Data[i] == 32){
            continue;
        }else if ((int)Data.m_Data[i] < 65 || (int)Data.m_Data[i] > 90){
            return true;
        }
    }
    Data.m_EnLen = Data.m_Len;
    Data.m_EnSize = Data.m_Size;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    //cout << m_Key << endl;
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] == 10 || Data.m_Data[i] == ' ') {
            Data.m_Encrypted[i] = ' ';
            continue;
        }
        //cout << ((int)Data.m_Data[i] - 65) << " " << ((int)m_Key.at(i % m_Key.size()) - 65) << endl;
        Data.m_Encrypted[i] = m_AlfaMatrix[((int)Data.m_Data[i] - 65)][((int)m_Key.at(i % m_Key.size()) - 65)];
    }
    return false;
}

bool CVigener::Decrypt(CData &Data) {
    Init();
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] > 96 && (int)Data.m_Data[i] < 123) {
            Data.m_Data[i] = toupper(Data.m_Data[i]);
        }else if ((int)Data.m_Data[i] == 10 || Data.m_Data[i] == ' '){
            continue;
        }else if ((int)Data.m_Data[i] < 65 || (int)Data.m_Data[i] > 90)
            return true;
    }
    Data.m_EnSize = Data.m_Size;
    Data.m_EnLen = Data.m_Len;
    Data.m_Encrypted = new unsigned char[Data.m_EnSize];
    int k = 0;
    for (uint i = 0; i < Data.m_Len; i++){
        if ((int)Data.m_Data[i] == 10 || Data.m_Data[i] == ' ')
            Data.m_Encrypted[k++] = ' ';
        else{
            for (int j = 0; j < 26; j++){
                if (m_AlfaMatrix[((int)m_Key.at(i % m_Key.size()) - 65)][j] == Data.m_Data[i]){
                    Data.m_Encrypted[k++] = (char)(j + 65);
                    break;
                }
            }
        }
    }
    return false;
}