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
        std::function<string(const string& fileptahIn, const string& filepathOut)> encodeFile;
        std::function<string(const string& data)> encodeData;
        std::function<string(const string& fileptahIn, const string& filepathOut, const string& decodeInfo)> decodeFile;
        std::function<string(const string& algoSeries)> decodeData;
        std::function<void()> genKeyWithIV;
        string name = "";
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv;
        int id      =  0;

        AlgorithmInfo() {} //temporary empty constructor, will be prohibited later
        AlgorithmInfo(
            std::function<string(const string& fileptahIn, const string& filepathOut)> encodeF,
            std::function<string(const string& data)> encodeD,
            std::function<string(const string& fileptahIn, const string& filepathOut, const string& decodeInfo)> decodeF,
            std::function<string(const string& data)> decodeD,
            std::function<void()> genKeyWithIV,
            string algoName
        ) : encodeFile(encodeF), encodeData(encodeD),
            decodeFile(decodeF), decodeData(decodeD),
            name(algoName) {}

        /* returns a json, containing struct data */
        operator json () const {
            json result;
            result["name"] = name;
            result["key"]  = std::string(reinterpret_cast<const char*>(&key[0]), key.size());
            result["iv"]   = std::string(reinterpret_cast<const char*>(&iv[0]), iv.size());
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
            currAlgo.genKeyWithIV();
            algoSeries.push_back(currAlgo);
        }
        return algoSeries;
    }

    json convertToJSON(vector<AlgorithmInfo> algos) {
        /* converts algoseries to json */
        json result;
        for (const auto& algo : algos) {
            result["series"] += algo;
        }
        return result;
    }
}

namespace randcrypt {
    std::string encode(const std::string& filepathIn, const std::string& filepathOut) {}
    std::string encode(const std::string& data) {}
    std::string decode(const std::string& filepathIn, const std::string& filepathOut, const std::string& decodeInfo) {}
    std::string decode(const std::string& data) {}
}
