# randcrypt
encryption/decryption library that uses random algorithms

## build Instructions

### requirements

- [git](https://git-scm.com/)
- [cmake](https://cmake.org/)
- [conan](https://conan.io/)
- [gcc](https://www.gnu.org/software/gcc/) or [clang](https://clang.llvm.org/) or [msvc](https://visualstudio.microsoft.com/)

### building

downloading dependencies via conan:
```bash
$ mkdir build; cd build
$ conan install ..
$ cd ..
```

building the project via CMake:
```bash
$ mkdir bin
$ cd build
$ cmake -G="Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../
$ make
$ make install
$ cd ..
```

### running

run the tests:
```bash
$ ./bin/t
```

### links

- Nlohmann::JSON: https://cryptopp.com/
- Crypto++:       https://cryptopp.com/
- Conan:          https://conan.io/
- CMake:          https://cmake.org/
