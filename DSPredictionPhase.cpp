#include "DSPredictionPhase.h"
#include <fstream>
#include <cstdio>

// Constructor
DSPredictionPhase::DSPredictionPhase(char* sentimentFile, char* predictionFile, char* accuracyFile, std::map<int, int> sentimentData)
{
    predictionMap = sentimentData;
    loadSentimentData(sentimentFile);
    outputClassification(predictionFile);
    outputAccuracy(accuracyFile);
}

// Function to load sentiment data from a file
void DSPredictionPhase::loadSentimentData(DSString filename)
{
    FILE* stream = fopen(filename.c_str(), "r");
    if (!stream)
    {
        std::cerr << "Error: Failed to open sentiment file!" << std::endl;
        return;
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), stream))
    {
        int sentiment, tweetID;
        sscanf(buffer, "%d, %d", &sentiment, &tweetID);
        sentimentMap[tweetID] = sentiment;
    }
    fclose(stream);
}

// Setter for predicted data
void DSPredictionPhase::setPredictedData(const std::map<int, int>& predictions)
{
    predictionMap = predictions;
}



// Function to output accuracy results to a file
void DSPredictionPhase::outputAccuracy(const char* filename)
{
    int correctCount = 0;
    std::ofstream out(filename);

    // Calculate accuracy
    for (const auto& prediction : predictionMap)
    {
        if (sentimentMap[prediction.first] == prediction.second)
        {
            correctCount++;
        }
    }

    double accuracy = correctCount / (double)predictionMap.size();
    out.precision(3);
    out << std::fixed << "Accuracy: " << accuracy << "\n";

    // Output incorrect predictions
    for (const auto& prediction : predictionMap)
    {
        if (sentimentMap[prediction.first] != prediction.second)
        {
            out << "Incorrect prediction: Predicted " << prediction.second << ", Actual " << sentimentMap[prediction.first] << ", Tweet ID " << prediction.first << "\n";
        }
    }
    out.close();
}


// Function to output classification results to a file
void DSPredictionPhase::outputClassification(const char* filename)
{
    std::ofstream out(filename);
    for (const auto& prediction : predictionMap)
    {
        out << prediction.second << ", " << prediction.first << "\n";
    }
    out.close();
}