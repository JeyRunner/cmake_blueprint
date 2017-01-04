## cmake blueprint c++ project
This a blueprint c++ project build via cmake. Also included is the continuous integration system [travis-ci](https://travis-ci.org).

### Build status

|Host System | Destination System | Status
|------------|--------------------|-------
|Ubunut 14.04|Ubunut 14.04        | [![Build Status](https://travis-ci.com/JeyRunner/cmake_cpp.svg?token=YoXU2cs1ytyW8AsxssK4&branch=master)](https://travis-ci.com/JeyRunner/cmake_cpp)
|            |Android             | coming soon...

### Download
Here you can download the [latest Release](https://www.github.com/JeyRunner/cmake_cpp/releases/latest).

####Project Structure
``` ruby
├── cmake
│   ├── helper.cmake
|   └── ..
|
├── dependencies
|   ├── SDL2
|   └── ..
|
├── platform
|   ├── android
|   └── ..
|
├── source
|   ├── component1
|   │   ├── include
|   │   │   └── *.h
|   │   ├── source
|   │   |   └── *.cpp
|   │   └── CMakeLists.txt 
|   │
|   ├── component2
|   |   └── ..
|   └── CMakeLists.txt
|
├── CMakeLists.txt
└── build.py

```
* ```cmake``` all cmake helper functions, toolchain files
* ```platform``` platform dependent code (expl.: android java wrapper, manifest.xml)
* ```source``` source components (libraries, binaries)
* ```dependentcies``` source, headers of thirdparty dependencies  
* ```build.py``` used for automatic cmake cross build


### Build
To build for your current host platform just go into source folder and execute:
``` bash
mkdir build
cd build
cmake ..
make
```
If you want to generate a installer from libs, binary use ```make package```
#### Cross compile 
For cross compiling use a toolchain. As example we will do that for android (install android ndk and skd before).
 ([more info of android.toolchain](https://github.com/taka-no-me/android-cmake))
```
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/android.toolchain.cmake \
      -DANDROID_NDK=<ndk_path>                       \
      -DANDROID_ABI="armeabi-v7a with NEON"          \
      ..
make
make BuildApk
```
The ```make BuildApk``` command creates a ready android application file.

**Alternatively** you can use build.py to cross compile.
```
./build.py --android <android_api>
``` 
