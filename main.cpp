#include <iostream>
#include "DSString.h"
#include "DSTrainingPhase.h"
#include "DSTestingPhase.h"
#include "DSPredictionPhase.h"

using namespace std;

int main(int argc, char** argv)
{  
   std::cout << "I will be a sentiment analyzer!" << std::endl;

   if(argc != 6) {
        std::cerr << "Usage: " << argv[0] << " <train_dataset> <test_dataset> <test_dataset_sentiment>" << std::endl;
        return 1;
   }

   DSTrainingPhase trainingObj(argv[1]);
   DSTestingPhase testingObj(argv[2], trainingObj.getPosCount(), trainingObj.getNegCount());
   DSPredictionPhase predictionObj(argv[3], argv[4], argv[5], testingObj.predictSentiments());

   return 0;
}