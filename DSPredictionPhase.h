#include <map>
#include "DSString.h"

// Defines a phase in a sentiment prediction process
class DSPredictionPhase 
{
private:
    std::map<int, int> sentimentMap; // Stores the sentiment data
    std::map<int, int> predictionMap; // Stores the prediction data

public:
    // Constructor: Initializes prediction phase with file paths and sentiment data
    DSPredictionPhase(char* sentimentFile, char* predictionFile, char* accuracyFile, std::map<int, int> sentimentData);

    // Loads sentiment data from a file
    void loadSentimentData(DSString filename);

    // Sets the prediction data
    void setPredictedData(const std::map<int, int>& predictions);

    // Outputs the classification results to a file
    void outputClassification(const char* filename);

    // Outputs the prediction accuracy to a file
    void outputAccuracy(const char* filename);
};
