echo "Intalling submodules"
git submodule init
echo "Updating submodules"
git submodule update
echo "ML pack dependicies"
sudo apt-get install libarmidillo-dev libboost-all-dev qt5declarative-dev
echo "Now to finish up builing mlpack"
cd lib/mlpack
mkdir build
cd build
cmake ..

