#include <iostream>
#include <fstream> // Included for file operations, but not used directly here
#include <map>
#include "DSString.h" // Include DSString for string operations
#include "DSTrainingPhase.h"


// Constructor: Initializes the training phase by loading data from a specified file
DSTrainingPhase::DSTrainingPhase(char* filename) 
{
    loadTrainingData(filename);
}

// Loads training data from a file, parsing each line to update word counts
void DSTrainingPhase::loadTrainingData(DSString fileName) 
{
    FILE* fileStream = fopen(fileName.c_str(), "r");
    if (!fileStream) 
    {
        std::cerr << "Error: Failed to open file!" << std::endl;
        return;
    }

    char myBuffer[1000];
    while (fgets(myBuffer, sizeof(myBuffer), fileStream)) 
    {
        DSString fileLine(myBuffer);
        DSString sentiment = fileLine.substring(0, 1);

        size_t pos = 0;
        int commaCount = 0;
        for (size_t i = 0; i < fileLine.length() && commaCount < 5; ++i) 
        {
            if (fileLine[i] == ',') 
            {
                commaCount++;
                if (commaCount == 4) 
                {
                    pos = i + 1;
                }
            }
        }

        DSString tweet = fileLine.substring(pos, fileLine.length() - pos);
        std::map<DSString, int> tokens = tweet.tokenize(' ');

        for (auto& token : tokens) 
        {
            if (sentiment == "0") // Negative sentiment
            {
                negativeCount[token.first] += 1;
            }
            else if (sentiment == "4") // Positive sentiment
            {
                positiveCount[token.first] += 1;
            }
        }
    }
    fclose(fileStream);
}

// Returns a reference to the map tracking positive word counts
std::map<DSString, int>& DSTrainingPhase::getPosCount() 
{
    return positiveCount;
}

// Returns a reference to the map tracking negative word counts
std::map<DSString, int>& DSTrainingPhase::getNegCount() 
{
    return negativeCount;
}

// Retrieves the count of a word in the positive context
int DSTrainingPhase::getPosCount(const DSString& word) 
{
    if (positiveCount.find(word) != positiveCount.end()) 
    {
        return positiveCount[word];
    }
    return 0;
}

// Retrieves the count of a word in the negative context
int DSTrainingPhase::getNegCount(const DSString& word) 
{
    if (negativeCount.find(word) != negativeCount.end()) 
    {
        return negativeCount[word];
    }
    return 0;
}
