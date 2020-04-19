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
#include "cryptopp/secblock.h"  /* SecByteBlock         */
#include "cryptopp/filters.h"   /* StringSource         */
#include "cryptopp/osrng.h"     /* AutoSeededRandomPool */
#include <functional>           /* std::function */
#include <string>               /* std::string   */
#include <vector>               /* std::vector   */

namespace randcrypt {
    bool initialize();
    bool terminate();
    std::vector<std::string> encode(const std::string& filepathIn, const std::string& filepathOut);
    std::vector<std::string> encode(const std::string& data);
    void decode(const std::string& filepathIn, const std::string& filepathOut, const std::vector<std::string>& decodeInfo);
    std::string decode(const std::vector<std::string>& decodeInfo);
}
