/*
 * This file should help you to create a minimal interface for your string class based on
 * a dynamically allocated char array. Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-string.
 */

#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <map>



class DSString
{

private:
    char *data; // a pointer to a character array containing the string with a `\0` terminator
    size_t len; // the length of the string (without the terminator)
    // Note: we keep the terminator only so we can return a c-string version in function c_str().

public:
    /**
     * Make sure you implement the rule-of-three and use proper memory management.
     * To help you get started, you can implement the following:
     **/

    DSString();
    DSString(const char *); // constructor that converts a cstring
    // you can also provide  DSString(const std::string &); for std::string

    // Rule of three is needed if dynamic memory allocation is used
    DSString(const DSString &);            // copy constructor
    DSString &operator=(const DSString &); // copy assignment operator
    ~DSString();                           // destructor

    // you can also implement the move versions for the big 5 (C+11)

    size_t length() const; // returns the length of the string

    char &operator[](size_t); // returns a reference to the character at the given index

    /**
     * Overloaded operator+ which appends the string in the argument to this string
     */
    DSString operator+(const DSString &) const;

    /**
     * Standard relational operators to compare and order your strings.
     * Feel free to add more.
     **/
    bool operator==(const DSString &) const;
    bool operator<(const DSString &) const;

    /**
     * The substring method returns a new string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(size_t start, size_t numChars) const;

    /**
     * @brief Returns a new string object with all characters in lowercase
     *
     * @return DSString
     */
    DSString toLower() const; // look at the ASCII table for this!

    /**
     * the c_str function returns a pointer a null-terminated c-string holding the
     * contents of this object. Since data already has a `\0`
     * at the end of the string in DSString so you can just return a pointer to data.
     **/
    const char *c_str() const;

    // a conversion to std::string would also be nice to have: string string() const;


    /**
     * Function to convert the string to an integer
    */
    int toInt() const;

    
    // Find the last occurrence of character 'c' in the string
    size_t findLastOf(char c) const;

    // Read from ifstream into DSString
    bool readFromStream(std::ifstream& stream);

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument. Remember:
     * This operator needs to be implemented outside of the class (and outside the class
     * namespace) as a friend because it operates on the stream and not the DSString object.
     **/
    friend std::ostream &operator<<(std::ostream &, const DSString &);

    
    
    /**
     * @brief Finds the position of the first occurrence of any character from the given set of characters.
     * 
     * @param characters The DSString containing characters to search for.
     * @param startIndex The index to start searching from.
     * @return size_t The position of the first occurrence of any character from the given set, or DSString::npos if not found.
     */
    size_t findFirstOf(const DSString &characters, size_t startIndex = 0) const;

    
    
    /**
     * Splits the string into parts based on a delimiter and counts how often each part appears.
     * 
     * @param delimiter The character used to split the string.
     * @return A map with each distinct part of the string as a key and its occurrence count as the value.
     */
     std::map<DSString, int> tokenize(const char) const;


    // You are free to add more functionality to the class.  For example,
    // you may want to add a find(...) function that will search for a
    // substring within a string or a function that breaks a string into words.
    // You will need a split or tokenize function.

    
};



#endif
