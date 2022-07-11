//
// Created by tim on 27.5.17.
//

#include "MyLibrary.hpp"

bool YNChoice(const char * question){
    bool result = false;
    string choice;
    while(1) {
        cout << question;
        cin >> choice;
        if (!choice.compare("y")){
            result = true;
            break;
        }
        if (!choice.compare("n")){
            break;
        }
        cout << "Type \"y\" or \"n\" please." << endl << endl;
        choice.clear();
    }
    return result;
}

int ValidNumber(const char * warning, int border_low, int border_high){
    int tmp;
    string tmp_s;
    while(1) {
        cin >> tmp_s;
        try{tmp = stoi(tmp_s);}
        catch(...){
            cout << warning << endl;
            continue;
        }
        if (tmp <= border_high && border_low <= tmp)
            break;
        cout << warning << endl;
    }
    return tmp;
}