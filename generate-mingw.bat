@echo off

REM Set command
set CMAKE_CMD=cmake --preset mingw && cmake --build build-mingw
REM Run command
echo %CMAKE_CMD%
%CMAKE_CMD%

pause