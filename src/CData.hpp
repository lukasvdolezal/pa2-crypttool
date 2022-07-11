//
// Created by tim on 19.5.17.
//

#ifndef CRYPTTOOL_CDATA_HPP
#define CRYPTTOOL_CDATA_HPP

#include <iostream>

using namespace std;
/**
 * Class CData handles and deposits any user data.
 */
class CData{
public:
    CData();
    ~CData();
    /**
    * Method Load loads user data to member array.
    * @param[in] input is a istream file that contains user data to encrypt.
    * @return This method returns possible succes in bool notation.
    */
    void Load(FILE * input);
    /**
     * This is method for visualisation of encrypted data.
     * @param en is used for indication of printing plain or encrypted text
     * @param hex is used for indication of printing in hexadecimals
     * @param des is used for indication of use DES cipher
     */
    void PrintData(bool en, bool hex, int des) const;
    /**
     * This method saves data into output file.
     * @param output is output file
     * @param hex is indication of using hexadecimals
     */
    void Out(FILE * output, bool hex) const;
    /**
     * This array contains original user data.
     */
    unsigned char * m_Data;
    /**
     * This array contains encrypted or decrypted user data.
     */
    unsigned char * m_Encrypted;
    /**
     * This variable is size of allocated memory for original data.
     */
    unsigned int m_Size;
    /**
     * This variable is size of original data.
     */
    unsigned int m_Len;
    /**
     * This variable is size of allocated memory for encrypted or decrypted data.
     */
    unsigned int m_EnSize;
    /**
     * This variable is size of encrypted or decrypted data.
     */
    unsigned int m_EnLen;
};

#endif //CRYPTTOOL_CDATA_HPP
