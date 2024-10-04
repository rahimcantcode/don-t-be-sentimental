#include "DSString.h"
#include <vector>
#include <map>

class DSTestingPhase {
    private:
        std::map<int, DSString> tweets;
        std::map<DSString, int> positiveCount;
        std::map<DSString, int> negativeCount;
    public:
        // Constructor
        DSTestingPhase(char* filename, std::map<DSString, int>& , std::map<DSString, int>& );
        // Function to load testing data from a file
        void loadTestingData(DSString);
        // Function to predict sentiments for loaded testing data
        std::map<int, int> predictSentiments();
        // Function to set trained sentiment data
        void setTrainedData(const std::map<DSString, int>& pos, const std::map<DSString, int>& neg);
};