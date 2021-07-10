# PolarUV-client
This software is the part of PolarUV-project, and runs on the pilot's computer

# Dependencied
- Qt >= 5.15.2
- gcc >= 12.1.0
- conan >= 1.48
- Windows

# Pre-Built binaries
If you want pre-buil binaries add this repo
   
    conan remote add starwalker https://polarrov.jfrog.io/artifactory/api/conan/windows-clang-conan
    
This is profile for the pre-build binaries
    
    [settings]
    os=Windows
    os_build=Windows
    arch=x86_64
    arch_build=x86_64
    compiler=gcc
    compiler.cppstd=20
    compiler.version=11.3
    compiler.threads=win32
    compiler.libcxx=libstdc++11
    build_type=Release

    [options]

    [build_requires]

    [env]
    CC=C:/msys64/mingw64/bin/gcc.exe
    CXX=C:/msys64/mingw64/bin/g++.exe
    
    
