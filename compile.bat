@echo off
cd src
g++ -std=c++17 main.cpp model/*.cpp view/*.cpp controller/*.cpp util/*.cpp -o Charlie'sChocolateShopPOS.exe
if %errorlevel% neq 0 (
    echo Compilation failed
    pause
    exit /b %errorlevel%
)
echo Compilation successful
ChocolateShopPOS.exe
pause