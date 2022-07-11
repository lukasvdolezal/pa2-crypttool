//
// Created by tim on 26.5.17.
//

#include <iostream>
#include <string>

/**
 * Class MyLibrary is used like a library of my functions used in many classes.
 */

using namespace std;

/**
 * YN choice is used for asking user for simple yes or no answer
 * @param question is string with question, different for each class
 * @return bool indicating positive or negative answer
 */
bool YNChoice(const char * question);
/**
 * ValidNumber is for loading user input of integer. It doesn't allow user to load invalid data.
 * @param warning is warning sentence for typing valid data
 * @param border_low is lower border for integer
 * @param border_high is higher border for integer
 * @return The method returns valid integer data.
 */
int ValidNumber(const char * warning, int border_low, int border_high );