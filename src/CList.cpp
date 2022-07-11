//
// Created by tim on 19.5.17.
//

#include <iostream>
#include "CList.hpp"
#include "CCipher.hpp"
#include "CMD5.hpp"
#include "CCaesar.hpp"
#include "CVigener.hpp"
#include "CSha1.hpp"
#include "CBase64.hpp"
#include "CDesCBC.hpp"
#include "CDesECB.hpp"
#include "MyLibrary.hpp"

using namespace std;

CCipher * CList::ChooseCipher(bool & hex, bool & des){
    cout << "Choose a cipher or hash from the list." << endl;
    cout << "1 : MD5" << endl;
    cout << "2 : Caesar" << endl;
    cout << "3 : Vigener" << endl;
    cout << "4 : SHA1" << endl;
    cout << "5 : Base64" << endl;
    cout << "6 : DES-CBC" << endl;
    cout << "7 : DES-ECB" << endl << endl;
    cout << "Your choice: " << endl;
    int choice = ValidNumber("Zadejte prosim cislo dle seznamu.", 1, 7);
    if (choice == 1) {
        CMD5 * cipher = new CMD5;
        hex = true;
        return cipher;
    }
    if (choice == 2) {
        CCaesar * cipher = new CCaesar;
        return cipher;
    }
    if (choice == 3) {
        CVigener * cipher = new CVigener;
        return cipher;
    }
    if (choice == 4){
        CSha1 * cipher = new CSha1;
        hex = true;
        return cipher;
    }
    if (choice == 5){
        CBase64 * cipher = new CBase64;
        return cipher;
    }
    if (choice == 6){
        CDesCBC * cipher = new CDesCBC;
        des = true;
        return cipher;
    }
    if (choice == 7){
        CDesECB * cipher = new CDesECB;
        des = true;
        return cipher;
    }
    return nullptr;
}