## Concept

- makes build settings more simple

## Draft

```yaml
---
my_config_debug:
  type: "configuration"
  name: "Debug"
  defines:
    - "DEBUG=1"

targets:
  mylib:
    product_name: "MyLib"
    type: "shared_library"
    configurations:
      Debug:
        defines:
          - "DEBUG=1"
  myapp:
    product_name: "MyLib"
    type: "shared_library"
    configurations:
      Debug:
        defines:
          - "DEBUG=1"
      Release:
        defines:
          - "NDEBUG=1"

include_dirs:
- "../dependencies/vendor/glew/include"

headers:
- "include/HttpService.h"

sources:
- "src/HttpService.cpp"
- "src/main.cpp"

msbuild_settings:
  ClCompile:
    TreatWarningAsError: true # /WX
    PreprocessorDefinitions:
      - "_WIN32_WINNT=0x0601" # Windows 7 or later
      - "WIN32_LEAN_AND_MEAN"
      - "NOMINMAX"
  Link:
    GenerateDebugInformation: true # /DEBUG

xcode_settings:
  CLANG_CXX_LANGUAGE_STANDARD: "c++14"
  CLANG_CXX_LIBRARY: "libc++"
  GCC_WARN_64_TO_32_BIT_CONVERSION: "YES"
  GCC_WARN_ABOUT_DEPRECATED_FUNCTIONS: "YES"
  GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS: "YES"
  GCC_WARN_ABOUT_MISSING_NEWLINE: "YES"
  GCC_WARN_ABOUT_RETURN_TYPE: "YES"
  GCC_WARN_CHECK_SWITCH_STATEMENTS: "YES"
  GCC_WARN_HIDDEN_VIRTUAL_FUNCTIONS: "YES"
```

## Settings

- Build Configuration(s)
  - Debug
  - Release

- Targets
  - Executable (Mac/iOS/tvOS)
  - Library (Mac/iOS/tvOS)

- Platform(s)
  - Windows
  - Mac
  - iOS
  - Android

- Underlying build tool
  - Xcode (Xcodebuild)
  - Visual Studio (MSBuild)
  - CMake
  - Make
