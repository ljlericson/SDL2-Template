@echo off

REM Set command
set CMAKE_CMD=cmake -S . -B build -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
REM Run command
echo %CMAKE_CMD%
%CMAKE_CMD%

pause