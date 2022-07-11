//
// Created by tim on 19.5.17.
//

#ifndef CRYPTTOOL_CLIST_HPP
#define CRYPTTOOL_CLIST_HPP

#include "CCipher.hpp"

class CList{
public:
    /**
     * This method allows user to choose anz cipher program offers.
     * @param hex indicates if chosen cipher should be printed in hexadecimals.
     * @param des indicates if chosen cipher is DES cipher
     * @return object of chosen cipher
     */
    CCipher * ChooseCipher(bool & hex, bool & des);
};

#endif //CRYPTTOOL_CLIST_HPP
