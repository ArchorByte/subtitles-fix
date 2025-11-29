clear

mkdir -p build
cd build

mkdir -p linux
cd linux

mkdir -p cmake
mkdir -p out
cd cmake

cmake ../../../
make

chmod +x subfix
mv subfix ../out

cd ../out
echo ""

./subfix
