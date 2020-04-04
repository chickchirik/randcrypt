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

- Crypto++: https://cryptopp.com/
- CMake: https://cmake.org/
- CMake documentation: https://cmake.org/documentation/
- CMake FAQ: https://gitlab.kitware.com/cmake/community/wikis/FAQ
- Conan introduction: https://docs.conan.io/en/latest/getting_started.html
