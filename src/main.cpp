#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CData.hpp"
#include "CList.hpp"
#include "CCipher.hpp"
#include "MyLibrary.hpp"

using namespace std;

void error(const int & cause){
    if (cause == 1) {
        cout << "Invalid input data" << endl;
        return;
    }
}

int main(int argc, char * argv[]) {
    system("clear");
    cout << "Cryptool" << endl << endl;
    FILE * input_file = nullptr;
    string input_file_dir;
    bool en = true;
    bool hex = false;
    bool des = false;
    CData Data;
    if (argc > 1){
        input_file_dir = argv[1];
        input_file = fopen(input_file_dir.c_str(), "r");
        if (input_file == nullptr)
            cout << "cannot read" << endl;
        cout << "File was passed as an argument." << endl;
    }else {
        cout << "Path: ";
        getline(std::cin, input_file_dir);
        input_file = fopen(input_file_dir.c_str(), "r");
        while (input_file == nullptr) {
            cout << endl << "Cannot open the file." << endl;
            cout << "Please, write the right path to a file or command \"quit\": ";
            cin >> input_file_dir;
            if (!input_file_dir.compare("quit")) {
                return 0;
            }
            input_file = fopen(input_file_dir.c_str(), "w");
        }
    }
    Data.Load(input_file);
    fclose(input_file);
    CList List;
    CCipher * Cipher = List.ChooseCipher(hex, des);
    if (Cipher == nullptr)
        return 1;
    Cipher->SetParam();
    en = YNChoice("Do you want to encrypt (y) or decrypt (n)? ");
    string output_name;
    if (en) {
        if (Cipher->Encrypt(Data)) {
            error(1);
            return 1;
        }
        output_name = input_file_dir += ".encrypted";
    }else{
        if (Cipher->Decrypt(Data)) {
            error(1);
            delete Cipher;
            return 1;
        }
        output_name = input_file_dir += ".decrypted";
    }
    Data.PrintData(true, hex, des);
    FILE * output_file = nullptr;
    output_file = fopen(output_name.c_str(), "w");
    Data.Out(output_file, hex);
    fclose(output_file);
    delete Cipher;
    return 0;
}