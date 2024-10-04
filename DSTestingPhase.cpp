#include "DSTestingPhase.h"
#include <iostream>
#include <map>

// Constructor initializes the testing phase with training data and a file path for testing data
DSTestingPhase::DSTestingPhase(char* filename, std::map<DSString, int>& positive, std::map<DSString, int>& negative)
{
    setTrainedData(positive, negative); // Sets the trained data for sentiment analysis
    loadTestingData(filename); // Loads the testing data from the specified file
}

// Loads testing data from a file and stores it in the tweets map
void DSTestingPhase::loadTestingData(DSString filename)
{
    FILE* stream = fopen(filename.c_str(), "r"); // Attempt to open the file
    if (!stream) // Check for file open failure
    {
        std::cerr << "Error: Failed to open file!" << std::endl;
        return; // Exit if the file cannot be opened
    }

    char buffer[1000]; // Buffer to store lines read from the file
    while (fgets(buffer, sizeof(buffer), stream)) // Read each line into the buffer
    {
        DSString line(buffer); // Convert the buffer to a DSString
        size_t pos = 0; // Position to start extracting the tweet text
        int commaCount = 0; // Count of commas encountered (used to find tweet text position)
        int tweetID = 0; // Store tweet ID

        // Parse the line for the tweet ID and the start of the tweet text
        for (size_t i = 0; i < line.length() && commaCount < 5; ++i)
        {
            if (line[i] == ',')
            {
                commaCount++;
                if (commaCount == 1) // The first comma indicates the end of the tweet ID
                {
                    DSString idStr = line.substring(0, i);
                    tweetID = idStr.toInt(); // Convert tweet ID to integer
                }
                else if (commaCount == 4) // The fourth comma indicates the start of the tweet text
                {
                    pos = i + 1; // Set the position to extract the tweet text
                }
            }
        }

        // Extract the tweet text and store it in the tweets map with the tweet ID as the key
        DSString tweet = line.substring(pos, line.length() - pos);
        tweets[tweetID] = tweet;
    }

    fclose(stream); // Close the file stream
}

// Sets the trained data for use in sentiment prediction
void DSTestingPhase::setTrainedData(const std::map<DSString, int>& positive, const std::map<DSString, int>& negative)
{
    positiveCount = positive; // Set the positive sentiment data
    negativeCount = negative; // Set the negative sentiment data
}

// Predicts sentiments for the loaded testing data and returns a map of tweet IDs to sentiment predictions
std::map<int, int> DSTestingPhase::predictSentiments()
{
    std::map<int, int> predictions; // Map to store predictions

    // Iterate through each tweet in the testing data
    for (auto& tweetEntry : tweets)
    {
        int tweetID = tweetEntry.first; // Extract the tweet ID
        DSString tweetText = tweetEntry.second; // Extract the tweet text

        // Tokenize the tweet text to analyze individual words
        std::map<DSString, int> tokens = tweetText.tokenize(' ');

        int positiveScore = 0; // Initialize positive score
        int negativeScore = 0; // Initialize negative score

        // Score the tweet based on the trained data
        for (auto& token : tokens)
        {
            if (positiveCount.find(token.first) != positiveCount.end())
            {
                positiveScore += positiveCount[token.first]; // Increment positive score for each positive word found
            }
            if (negativeCount.find(token.first) != negativeCount.end())
            {
                negativeScore += negativeCount[token.first]; // Increment negative score for each negative word found
            }
        }

        // Determine the sentiment based on the comparison of positive and negative scores
        if (positiveScore > negativeScore)
        {
            predictions[tweetID] = 4; // Assign positive sentiment
        }
        else
        {
            predictions[tweetID] = 0; // Assign negative sentiment
        }
    }

    return predictions; // Return the map of predictions
}
