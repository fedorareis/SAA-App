echo "Intalling submodules"
git submodule init
echo "Updating submodules"
git submodule update
echo "ML pack dependicies"
sudo apt-get install lib-armidillo-dev libboost-all-dev
echo "Now to finish up builing mlpack"
cd lib/mlpack
mkdir build
cd build
cmake ..
make
cd ../../..
echo "NOW, to build the actual project"
mkdir build
cd build
cmake ..
make


