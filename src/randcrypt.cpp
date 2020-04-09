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
    using std::string;

    struct AlgorithmInfo {
        std::function<char*(char* fileptahIn, char* filepathOut)> encodeFile;
        std::function<char*(char* data)> encodeData;
        std::function<void(char* fileptahIn, char* algoSeries)> decodeFile;
        std::function<char*(char* algoSeries)> decodeData;
        string algName = "";
        string key = "";
        string iv  = "";
        int algID  =  0;
    };

    const AlgorithmInfo algorithms[ALGO_COUNT];
}

namespace randcrypt {
    char* encode(char* filepathIn, char* filepathOut) {}
    char* encode(char* data) {}
    void  decode(char* filepathIn, char* filepathOut, char* algoSeriesHash) {}
    char* decode(char* algoSeriesHash) {}
}
