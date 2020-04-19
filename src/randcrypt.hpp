/*
 * randcrypt.hpp
 * Created by <chickchirik> on 03/04/2019.
 * DESCRIPTION:
 *  randcrypt is an ecryption/decryption software
 *  that uses random algorithm seqences. It is based
 *  on a cryptopp library and provides a some kind of
 *  wrapper. Current API offers four functions:
 *      encode (for files and for raw data) - randomly chooses
 *              encryption algorithms and encodes the file or raw
 *              data returning an information about which
 *              algorithms and in what order were used, including
                such info as key and initialization vector.
 *      decode (for files and for raw data) - decodes the information
 *      back based on an information returned from previous function.
*/
#pragma once
#include "cryptopp/cryptlib.h"
#include "cryptopp/secblock.h"  /* SecByteBlock             */
#include "cryptopp/filters.h"   /* StringSource             */
#include "cryptopp/osrng.h"     /* AutoSeededRandomPool     */
#include "cryptopp/modes.h"     /* encryptoion modes        */
#include "cryptopp/aes.h"       /* AES encryptor            */
#include <string>               /* std::string              */
#include <vector>               /* std::vector              */

namespace randcrypt {
    /* randcrypt user API */
    bool initialize();  /* register used algorithms */
    bool terminate();   /* free used memory         */

    /* encodes file using randomly generated algorihm sequence  */
    std::vector<std::string> encode(
        const std::string& filepathIn,
        const std::string& filepathOut
    );

    /* encodes data using randomly generated algorihm sequence  */
    std::vector<std::string> encode(const std::string& data);

    /* decodes file using decodeInfo    */
    void decode(
        const std::string& filepathIn,
        const std::string& filepathOut,
        const std::vector<std::string>& decodeInfo
    );

    /* decodes data using decodeInfo    */
    std::string decode(const std::vector<std::string>& decodeInfo);
}
