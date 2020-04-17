/*
 * randcrypt.cpp
 * Created by <chickchirik> on 09/04/2019.
 * See the description in randcrypt.hpp
*/
#include "randcrypt.hpp"

#include <iostream>

/* unknown namespace for static-like linker visibility reduction behaviour */
namespace {
    template <typename IntT>
    using UIDistr = std::uniform_int_distribution<IntT>;
    using RanDev = std::random_device;
    using RanGen = std::mt19937;
    using std::string;
    using std::vector;

    class AlgorithmInfo {
    protected:
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv;
        int id =  0;
    public:
        AlgorithmInfo() {} //temporary empty constructor, will be prohibited later

        virtual string encode(const string& data) = 0;
        virtual string decode(const string& algoSeries) = 0;
        virtual string encode(const string& fileptahIn, const string& filepathOut) = 0;
        virtual string decode(const string& fileptahIn, const string& filepathOut, const string& decodeInfo) = 0;
        virtual void   genKeyWithIV() = 0;
    };

    class AESInfo : public AlgorithmInfo {
    public:
        virtual string encode(const string& data) override { return ""; }
        virtual string decode(const string& algoSeries) override { return ""; }
        virtual string encode(const string& fileptahIn, const string& filepathOut) override { return ""; }
        virtual string decode(const string& fileptahIn, const string& filepathOut, const string& decodeInfo) override { return ""; }
        virtual void   genKeyWithIV() override {}
    };

    /* algorithm-info lookup table */
    const vector<AlgorithmInfo*> algorithms;

    vector<AlgorithmInfo*> formAlgoSeries() {
        /* creates an arbitary sequence of
         * encryption algorithms with at least
         * one algorithm included
         */
        vector<AlgorithmInfo*> algoSeries;
        UIDistr<int> algoIdDistr(0, algorithms.size());
        UIDistr<int> lenDistr(1, algorithms.size());
        RanDev randomDevice;
        RanGen generator(randomDevice());
        int seriesLen = lenDistr(generator);
        for (int algoNum = 1; algoNum != seriesLen; ++algoNum) {
            int algoID = algoIdDistr(generator);
            AlgorithmInfo* currAlgo = algorithms[algoID];
            //currAlgo.id = algoID;
            currAlgo->genKeyWithIV();
            algoSeries.push_back(currAlgo);
        }
        return algoSeries;
    }
}

namespace randcrypt {
    std::string encode(const std::string& filepathIn, const std::string& filepathOut) { return ""; }
    std::string encode(const std::string& data) { return ""; }
    std::string decode(const std::string& filepathIn, const std::string& filepathOut, const std::string& decodeInfo) { return ""; }
    std::string decode(const std::string& data) { return ""; }
}
