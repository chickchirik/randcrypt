/*

    randcrypt.hpp

    Created by <chickchirik> on 03/04/2019.

    DESCRIPTION:
    randcrypt is an ecryption/decryption software
    that uses random algorithms.

*/
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include <functional>
#include <string>
#include <random>

/**/

namespace randcrypt {
    char* encode(char* filepathIn, char* filepathOut);
    char* encode(char* data);
    void  decode(char* filepathIn, char* filepathOut, char* algoSeriesHash);
    char* decode(char* algoSeriesHash);
}
