/*
 * randcrypt.cpp
 * Created by <chickchirik> on 09/04/2019.
 * See the description in randcrypt.hpp
*/
#include "randcrypt.hpp"

#include <iostream>

/* unknown namespace for static-like linker visibility reduction behaviour */
namespace {
    using std::string;
    using std::vector;

    /* base interface class. new algorithm must derive from it and override virtual functions */
    class AlgorithmInfo {
    protected:
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv;
        int id = 0;
    public:
        AlgorithmInfo()  = default;
        ~AlgorithmInfo() = default;

        CryptoPP::SecByteBlock getKey() { return key; }
        CryptoPP::SecByteBlock getIV()  { return iv;  }
        string getKeyAsString() { return string(reinterpret_cast<const char*>(&key[0]), key.size()); }
        string getIVAsString()  { return string(reinterpret_cast<const char*>(&iv[0]),  key.size()); }
        int    getID() { return id; }

        virtual string encode(const string& data) = 0;
        virtual string decode(const string& algoSeries) = 0;
        virtual string encode(const string& fileptahIn, const string& filepathOut) = 0;
        virtual string decode(const string& fileptahIn, const string& filepathOut, const string& decodeInfo) = 0;
        virtual void   genKeyWithIV() = 0;
    };

    class AESInfo : public AlgorithmInfo {
    public:
        AESInfo()  = default;
        ~AESInfo() = default;

        virtual string encode(const string& data) override { return ""; }
        virtual string decode(const string& algoSeries) override { return ""; }
        virtual string encode(const string& fileptahIn, const string& filepathOut) override { return ""; }
        virtual string decode(const string& fileptahIn, const string& filepathOut, const string& decodeInfo) override { return ""; }
        virtual void   genKeyWithIV() override {
            CryptoPP::AutoSeededRandomPool rnd;
            key = CryptoPP::SecByteBlock(0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
            iv  = CryptoPP::SecByteBlock(CryptoPP::AES::BLOCKSIZE);
            rnd.GenerateBlock(key, key.size());
            rnd.GenerateBlock(iv, iv.size());
        }
    };

    /* algorithm-info lookup table. new algorithms should be registered in randcrypt::initialize function */
    vector<AlgorithmInfo*> algorithms;

    vector<AlgorithmInfo*> formAlgoSeries() {
        /* creates an arbitary sequence of
         * encryption algorithms with at least
         * one algorithm included
         */
        vector<AlgorithmInfo*> algoSeries;
        CryptoPP::AutoSeededRandomPool rnd;
        int seriesLen = rnd.GenerateWord32(1, algorithms.size());           /* include at least one algorithm   */

        for (int algoNum = 1; algoNum <= seriesLen; ++algoNum) {
            int algoID = rnd.GenerateWord32(0, algorithms.size() - 1);      /* choose algorithm randomly        */
            AlgorithmInfo* currAlgo = algorithms[algoID];
            //currAlgo.id = algoID;
            currAlgo->genKeyWithIV();
            algoSeries.push_back(currAlgo);
        }
        return algoSeries;
    }
}

namespace randcrypt {
    /* randcrypt user API */

    bool initialize() {
        /* register used algorithms */
        algorithms.push_back(new AESInfo());
        return true;
    }

    bool terminate() {
        /* free used memory         */
        for (const auto algo : algorithms) {
            delete algo;
        }
        return true;
    }

    std::vector<std::string> encode(
            const std::string& filepathIn,
            const std::string& filepathOut
    ) {
        /* encodes file using randomly generated algorihm sequence  */
        std::vector<std::string> decodeInfo = {"count", "key", "iv", "id"};
        return decodeInfo;
    }

    std::vector<std::string> encode(const std::string& data) {
        /* encodes data using randomly generated algorihm sequence  */
        std::vector<std::string> decodeInfo = {"count", "key", "iv", "id"};
        return decodeInfo;
    }

    void decode(
        const std::string& filepathIn,
        const std::string& filepathOut,
        const std::vector<std::string>& decodeInfo
    ) {
        /* decodes file using decodeInfo    */
    }

    std::string decode(const std::vector<std::string>& decodeInfo) {
        /* decodes data using decodeInfo    */
        return "";
    }
}
