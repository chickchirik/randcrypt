/*

    randcrypt.cpp

    Created by <chickchirik> on 09/04/2019.

    DESCRIPTION:
    randcrypt is an ecryption/decryption software
    that uses random algorithms.

*/
#include "randcrypt.hpp"

namespace {
    #define ALGO_COUNT 1
    template <typename IntT>
    using UIDistr = std::uniform_int_distribution<IntT>;
    using RanDev = std::random_device;
    using RanGen = std::mt19937;
    using std::string;
    using std::vector;

    struct AlgorithmInfo {
        std::function<char*(char* fileptahIn, char* filepathOut)> encodeFile;
        std::function<char*(char* data)> encodeData;
        std::function<void(char* fileptahIn, char* algoSeries)> decodeFile;
        std::function<char*(char* algoSeries)> decodeData;
        string name = "";
        string key  = "";
        string iv   = "";
        int id      =  0;

        AlgorithmInfo() {} //temporary empty constructor, will be prohibited later
        AlgorithmInfo(
            std::function<char*(char* fileptahIn, char* filepathOut)> encodeF,
            std::function<char*(char* data)> encodeD,
            std::function<void(char* fileptahIn, char* algoSeries)> decodeF,
            std::function<char*(char* algoSeries)> decodeD,
            char* algoName
        ) : encodeFile(encodeF), encodeData(encodeD),
            decodeFile(decodeF), decodeData(decodeD),
            name(algoName) {}
    };

    const AlgorithmInfo algorithms[ALGO_COUNT];

    std::vector<AlgorithmInfo> formAlgoSeries() {
        vector<AlgorithmInfo> algoSeries;
        UIDistr<int> algoIdDistr(0, ALGO_COUNT);
        UIDistr<int> lenDistr(1, ALGO_COUNT);
        RanDev randomDevice;
        RanGen generator(randomDevice());
        int seriesLen = lenDistr(generator);
        for (int algoNum = 1; algoNum != seriesLen; ++algoNum) {
            int algoID = algoIdDistr(generator);
            AlgorithmInfo currAlgo = algorithms[algoID];
            currAlgo.id = algoID;
            algoSeries.push_back(currAlgo);
        }
        return algoSeries;
    }
}

namespace randcrypt {
    char* encode(char* filepathIn, char* filepathOut) {}
    char* encode(char* data) {}
    void  decode(char* filepathIn, char* filepathOut, char* algoSeriesHash) {}
    char* decode(char* algoSeriesHash) {}
}
