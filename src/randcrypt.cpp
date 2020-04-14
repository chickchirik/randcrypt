/*
 * randcrypt.cpp
 * Created by <chickchirik> on 09/04/2019.
 * See the description in randcrypt.hpp
*/
#include "randcrypt.hpp"

/* unknown namespace for static-like linker visibility reduction behaviour */
namespace {
    #define ALGO_COUNT 1
    template <typename IntT>
    using UIDistr = std::uniform_int_distribution<IntT>;
    using RanDev = std::random_device;
    using RanGen = std::mt19937;
    using std::string;
    using std::vector;
    using nlohmann::json;

    struct AlgorithmInfo {
        /* AlgorithmInfo data structure holds the information about
         * encryption algorithm, such as:
         *  encryption/decryption callbacks,
         *  name, key, iv,
         *  id(tmp solution for inner-indexing, thinking about better one)
         */
        std::function<string(string fileptahIn, string filepathOut)> encodeFile;
        std::function<string(string data)> encodeData;
        std::function<string(string fileptahIn, string algoSeries)> decodeFile;
        std::function<string(string algoSeries)> decodeData;
        string name = "";
        string key  = "";
        string iv   = "";
        int id      =  0;

        AlgorithmInfo() {} //temporary empty constructor, will be prohibited later
        AlgorithmInfo(
            std::function<string(string fileptahIn, string filepathOut)> encodeF,
            std::function<string(string data)> encodeD,
            std::function<string(string fileptahIn, string algoSeries)> decodeF,
            std::function<string(string algoSeries)> decodeD,
            string algoName
        ) : encodeFile(encodeF), encodeData(encodeD),
            decodeFile(decodeF), decodeData(decodeD),
            name(algoName) {}

        /* returns a json, containing struct data */
        json toJSON() const {
            json result;
            result["name"] = name;
            result["key"]  = key;
            result["iv"]   = iv;
            result["id"]   = id;
            return result;
        }
    };

    /* algorithm-info lookup table */
    const AlgorithmInfo algorithms[ALGO_COUNT];

    vector<AlgorithmInfo> formAlgoSeries() {
        /* creates an arbitary sequence of
         * encryption algorithms with at least
         * one algorithm included
         */
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

    json convertToJSON(vector<AlgorithmInfo> algos) {
        /* converts algoseries to json */
        json result;
        for (const auto& algo : algos) {
            result["series"] += algo.toJSON();
        }
        return result;
    }
}

namespace randcrypt {
    std::string encode(std::string filepathIn, std::string filepathOut) {}
    std::string encode(std::string data) {}
    std::string decode(std::string filepathIn, std::string filepathOut) {}
    std::string decode(std::string data) {}
}
