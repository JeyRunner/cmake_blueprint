### cmake blueprint c++ project
This a blueprint c++ project build via cmake. Also included is the continuous integration system [travis-ci](https://travis-ci.org).

#### Build status

|Host System | Destination System | Status
|------------|--------------------|-------
|Ubunut 14.04|Ubunut 14.04        | [![Build Status](https://travis-ci.com/JeyRunner/cmake_cpp.svg?token=YoXU2cs1ytyW8AsxssK4&branch=master)](https://travis-ci.com/JeyRunner/cmake_cpp)
|            |Android             | coming soon...

#### Download
Here you can download the [latest Release](https://www.github.com/JeyRunner/cmake_cpp/releases/latest).

#### Project Structure
``` ruby
├── cmake
│   ├── helper.cmake
|   └── ..
├── CMakeLists.txt
├── platform
|   ├── android
|   └── ..
└── source
    ├── component1
    │   ├── CMakeLists.txt
    │   ├── include
    │   │   └── *.h
    │   └── source
    │       └── *.cpp
    ├── component2
    |   └── ..
    └── CMakeLists.txt
```
* ```cmake``` all cmake helper functions, toolchain files
* ```platform``` platform dependent code (expl.: android java wrapper, manifest.xml)
* ```source``` source components (libraries, binaries)
 