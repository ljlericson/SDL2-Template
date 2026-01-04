@echo off

REM Set command
set CMAKE_CMD=cmake --preset msvc && cmake --build build-msvc
REM Run command
echo %CMAKE_CMD%
%CMAKE_CMD%

pause