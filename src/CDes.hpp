//
// Created by tim on 2.6.17.
//

#ifndef CRYPTTOOL_CDES_HPP
#define CRYPTTOOL_CDES_HPP

#include "CCipher.hpp"
#include "CData.hpp"
#include <openssl/evp.h>

/**
 * This class is used for encryption and decryption in DES ciphers. Classes for encrypting in CBC and ECB operation mode inherit from this class.
 */

class CDes : public CCipher{
public:
    /**
     * This method is for setting encrypting key.
     * @param key is used key
     */
    void SetKey(unsigned char * key);
    /**
     * This method is for setting initialization vector.
     * @param iv is used init. vector
     */
    void SetIV(unsigned char * iv);
    /**
     * This method has similar function like fread, but it's made for reading char array.
     * @param data is original array I want to read from
     * @param left is length of data that has been left in string
     * @param pos is position of reading data
     * @param pole is array used for block encryption. Data from "data" are copied here.
     * @return number of read characters.
     */
    int Read(unsigned char * data, int & left, int & pos, unsigned char * pole);
    /**
     * Is used for writing encrypted or decrypted data into output array.
     * @param out is array that contains data we want to write into output array.
     * @param outlen is length of "out".
     * @param enlen is length of output array.
     * @param encrypted is output array.
     */
    void Write(unsigned char * out, int & outlen, int & enlen, unsigned char * encrypted);
    /**
     * This function is special encrypting function for encrypting in DES cipher.
     * @param cipher is used cipher
     * @param Data is class that contains user data
     * @param key is used key
     * @param iv is used init. vector
     * @return invalid encryption indication if needed
     */
    bool EncryptByDes(const EVP_CIPHER * cipher, CData & Data, unsigned char key[], unsigned char iv[]);
    /**
     * This function is special decrypting function for decrypting in DES cipher.
     * @param cipher is used cipher
     * @param Data is class that contains user data
     * @param key is used key
     * @param iv is used init. vector
     * @return invalid decryption indication if needed
     */
    bool DecryptByDes(const EVP_CIPHER * cipher, CData & Data, unsigned char key[], unsigned char iv[]);
    virtual void SetParam() = 0;
    virtual bool Encrypt(CData & Data) = 0;
    virtual bool Decrypt(CData & Data) = 0;
};

#endif //CRYPTTOOL_CDES_HPP
