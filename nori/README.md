# nori

A Clang/GCC-compatible C/C++ project file generator for coding sketch.

It is distributed under the [MIT License](https://opensource.org/licenses/MIT).

## Features

- Easily generate Xcode project (`.xcodeproj`)
- Easily generate Visual Studio solution (`sln`) and project (`vcxproj`) files

## Build and run

```sh
# Build
make bootstrap
make xcode

# Run
./bin/nori -help
```

## Usage

```sh
# Generate myapp.xcodeproj file
nori -generator=xcode -o myapp myapp.cpp

# Generate myapp.sln and myapp.vcxproj file
nori -generator=msbuild -o myapp myapp.cpp
```

### To build your application with Xcode

```sh
nori \
  -generator=xcode \
  -o myapp \
  -std=c++14 \
  -stdlib=libc++ \
  -Ipath/to/include \
  *.cpp
@xcodebuild -project myapp.xcodeproj -configuration Release
```

The command-line tool is Clang/GCC-compatible, so it is the same as running the following commands in terminal:

```sh
clang \
  -o myapp \
  -std=c++14 \
  -stdlib=libc++ \
  -Ipath/to/include \
  *.cpp
```
