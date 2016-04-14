echo "Intalling submodules"
git submodule init
echo "Updating submodules"
git submodule update
echo "ML pack dependicies\n\n"
sudo apt-get install libarmadillo-dev libboost-all-dev qtdeclarative5-dev
echo "Now to finish up building mlpack\n\n"
cd lib/mlpack
if [ ! -d "build" ]; then
	mkdir build
fi
cd build
cmake ..
make -j4
make install
cd ../../../
echo "MLPack is in!\n\n"
echo "going into protobuf to autogen it"
cd lib/protobuf
./autogen.sh
echo "Okay! now the project is ready to build!"
cd ../../
if [ ! -d "build" ]; then
	mkdir build
fi
cd build
cmake ..
make -j4
