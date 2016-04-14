echo "Intalling submodules"
git submodule init
echo "Updating submodules"
git submodule update
echo "ML pack dependicies"
sudo apt-get install libarmadillo-dev libboost-all-dev qtdeclarative5-dev
echo "Now to finish up builing mlpack"
cd lib/mlpack
if [ ! -d "build" ]; then
	mkdir build
fi
cd build
cmake ..
make -j4
cd ../../../
if [ ! -d "build" ]; then
	mkdir build
fi
cd build
cmake ..
make -j4
