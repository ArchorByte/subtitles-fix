@echo off
cls

if not exist "build" (mkdir "build")
cd build

if not exist "win" (mkdir "win")
cd win

if not exist "cmake" (mkdir "cmake")
cd cmake

cmake ../../../ -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/MinGW/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/MinGW/bin/g++.exe
C:/MinGW/bin/mingw32-make.exe

if not exist "out" (mkdir "out")
move subfix.exe ../out/
cd ../out

pause
start subfix.exe

cd ../../../
pause
