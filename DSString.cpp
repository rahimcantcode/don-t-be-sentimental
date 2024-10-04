#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <fstream>
#include <cstdlib> // Required for atoi()
#include "DSString.h"

/* Implementation of DSString class without C-String functions */

DSString::DSString() : data(nullptr), len(0) {} // Default constructor

DSString::DSString(const char* cstring) // Constructor from c-string
{
    if (!cstring) // Handle null pointer
    {
        len = 0;
        data = new char[1]{'\0'};
    }
    else
    {
        for (len = 0; cstring[len]; ++len); // Calculate length
        data = new char[len + 1];
        for (size_t i = 0; i <= len; ++i) data[i] = cstring[i]; // Copy data
    }
}

DSString::DSString(const DSString& other) : len(other.len), data(new char[other.len + 1]) // Copy constructor
{
    for (size_t i = 0; i <= len; ++i) data[i] = other.data[i];
}

DSString& DSString::operator=(const DSString& other) // Copy assignment operator
{
    if (this != &other)
    {
        delete[] data;
        len = other.len;
        data = new char[len + 1];
        for (size_t i = 0; i < len; i++) data[i] = other.data[i];
        data[len] = '\0';
    }
    return *this;
}

DSString::~DSString() { delete[] data; } // Destructor

size_t DSString::length() const { return len; } // Length of string

char& DSString::operator[](size_t index) // Subscript operator
{
    if (index >= len) throw std::out_of_range("Index out of bounds");
    return data[index];
}

bool DSString::operator==(const DSString& other) const // Equality comparison
{
    if (len != other.len) return false;
    for (size_t i = 0; i < len; ++i) if (data[i] != other.data[i]) return false;
    return true;
}

bool DSString::operator<(const DSString& other) const // Lexicographical comparison
{
    size_t i = 0;
    while (i < len && i < other.len)
    {
        if (data[i] < other.data[i]) return true;
        if (data[i] > other.data[i]) return false;
        ++i;
    }
    return len < other.len;
}

DSString DSString::substring(size_t startIndex, size_t numChars) const // Substring method
{
    assert(startIndex + numChars <= len);
    char* subData = new char[numChars + 1];
    for (size_t i = 0; i < numChars; ++i) subData[i] = data[startIndex + i];
    subData[numChars] = '\0';
    DSString subString(subData);
    delete[] subData;
    return subString;
}

DSString DSString::toLower() const // Convert to lowercase
{
    DSString result(*this);
    for (size_t i = 0; i < len; ++i)
        if (result.data[i] >= 'A' && result.data[i] <= 'Z')
            result.data[i] += ('a' - 'A');
    return result;
}

const char* DSString::c_str() const { return data; } // C-string conversion

std::ostream& operator<<(std::ostream& os, const DSString& str) // Stream insertion
{
    return os << str.data;
}

size_t DSString::findFirstOf(const DSString& characters, size_t startIndex) const // Find first of any character
{
    for (size_t i = startIndex; i < len; i++)
        for (size_t j = 0; j < characters.len; j++)
            if (data[i] == characters.data[j])
                return i;
    return len;
}

int DSString::toInt() const { return std::atoi(data); } // String to integer conversion

bool DSString::readFromStream(std::ifstream& stream) // Read from stream
{
    delete[] data;
    len = 0;
    char ch;
    if (stream.get(ch))
    {
        std::vector<char> buffer;
        do
        {
            buffer.push_back(ch);
        } while (stream.get(ch) && ch != '\n');
        buffer.push_back('\0');
        len = buffer.size() - 1;
        data = new char[len + 1];
        std::copy(buffer.begin(), buffer.end(), data);
        return true;
    }
    return false;
}

std::map<DSString, int> DSString::tokenize(const char delimiter) const // Tokenize string
{
    std::map<DSString, int> tokens;
    size_t startPos = 0;
    for (size_t currentPosition = 0; currentPosition <= len; ++currentPosition)
    {
        if (currentPosition == len || data[currentPosition] == delimiter)
        {
            if (currentPosition != startPos)
            {
                tokens[substring(startPos, currentPosition - startPos)]++;
            }
            startPos = currentPosition + 1;
        }
    }
    return tokens;
}
