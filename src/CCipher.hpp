//
// Created by tim on 19.5.17.
//

#ifndef CRYPTTOOL_CCIPHER_H
#define CRYPTTOOL_CCIPHER_H

#include "CData.hpp"

class CCipher{
public:
    virtual ~CCipher();
    /**
     * This method loads external file with parameters and user can choose one of them.
     * Parametres will be stored in private variable in each cipher.
     */
    virtual void SetParam();
    /**
     * This method encrypts user data using chosen parameters.
     * @param Data is class with user data
     * @return indicates unsuccessful encryption, if needed
     */
    virtual bool Encrypt(CData & Data) = 0;
    /**
     * This method decrypts user data using chosen parameters.
     * @param Data is class with user data
     * @return indicates unsuccessful decryption, if needed
     */
    virtual bool Decrypt(CData & Data) = 0;
};

#endif //CRYPTTOOL_CCIPHER_H
