/*
 * randcrypt.hpp
 * Created by <chickchirik> on 03/04/2019.
 * DESCRIPTION:
 *  randcrypt is an ecryption/decryption software
 *  that uses random algorithms. It is based on a
 *  cryptopp library and provides a some kind of
 *  wrapper. Current API offers four functions:
 *      encode (for files and for raw data) - randomly chooses
 *              encryption algorithms and encodes the file or raw
 *              data returning a hashed information about which
 *              algorithms and in what order were used.
 *      decode (for files and for raw data) - decodes the information
 *      back based on a hash returned from previous function.
*/
#pragma once
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include <functional>           /* std::function */
#include <string>               /* std::string   */
#include <random>               /* std::uniform_int_distribution; std::mersenne_twister_generator; */
#include "nlohmann/json.hpp"    /* nlohmann::json*/

namespace randcrypt {
    void encode(char* filepathIn, char* filepathOut, char* encodedDataInfo);
    void encode(char* data, char* encodedData);
    void decode(char* filepathIn, char* filepathOut, char* encodedDataInfo);
    void decode(char* encodedData, char* decodedData);
}
