@echo off

REM Set command
set CMAKE_CMD=cmake -B ./build .

REM Run command
echo %CMAKE_CMD%
%CMAKE_CMD%

pause