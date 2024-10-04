#ifndef DSTRAININGPHASE_H
#define DSTRAININGPHASE_H

#include "DSString.h"
#include <map>

// Represents the training phase of a sentiment analysis process.
class DSTrainingPhase {
private:
    std::map<DSString, int> positiveCount; // Tracks occurrences of words in positive context
    std::map<DSString, int> negativeCount; // Tracks occurrences of words in negative context

public:
    // Constructor: Initializes the training phase with a path to the training data file
    DSTrainingPhase(char*);

    // Loads training data from a file and populates positive and negative counts
    void loadTrainingData(const DSString filename);

    // Provides direct access to the map tracking positive word occurrences
    std::map<DSString, int>& getPosCount();

    // Provides direct access to the map tracking negative word occurrences
    std::map<DSString, int>& getNegCount();


    // Returns the count of a word in positive context
    int getPosCount(const DSString& word);

    // Returns the count of a word in negative context
    int getNegCount(const DSString& word);

    };

#endif // DSTRAININGPHASE_H
