@echo off
setlocal

if not exist build mkdir build

g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 ^
    src\main.cpp src\calculator.cpp ^
    -o build\calculator.exe

if %errorlevel% neq 0 exit /b %errorlevel%

echo Build complete: build\calculator.exe
