# typo-poi

Typo/misspell checking library for C/C++ and command-line tool.
It is distributed under the [MIT License](https://opensource.org/licenses/MIT).

## Build and run

**Build:**

```sh
git clone https://github.com/mogemimi/daily-snippets.git
cd daily-snippets/typo-poi

# Setup build tool
make -C ../nori bootstrap

# Build
make xcode

# Run
./bin/typo-poi -help
```

**Run:**

Run:

```sh
./bin/typo-poi YourSourceCode.cpp
```

## Thanks

The following libraries and/or open source projects were used in typo-poi:

* [LLVM Clang](http://clang.llvm.org/)
