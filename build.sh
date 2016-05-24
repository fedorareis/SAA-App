
check_program() {
	command -v $1 >/dev/null 2>&1 || { echo >&2 "this script require $1 but it's not installed. "; return 1; }
	return 0
}

install_homebrew(){
	echo "Checking to see if homebrew is installed..."
	if  check_program brew; then 
		read -p "Install Homebrew? " -n 1 -r
		if [[ ! $REPLY =~ ^[Yy]$ ]]
		then
    			exit 1;
		else
			/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)";
		fi
	fi

}
			

	

check_git() {
     git status > /dev/null; 
}

if check_git; then
	echo "Intalling submodules"
	git submodule init
	echo "Updating submodules"
	git submodule update
else
	echo "Cloning submodules"
	git clone https://github.com/google/googletest.git lib/googletest
	git clone https://github.com/google/protobuf.git  lib/protobuf
	git clone https://github.com/mlpack/mlpack.git   lib/mlpack
fi
echo "Third party libraries installed"
echo "ML pack dependicies\n"

if [ "$OSTYPE" == "linux-gnu" ]; then
	sudo apt-get install libarmadillo-dev libboost-all-dev qtdeclarative5-dev autoconf automake libtool

elif [ "$OSTYPE" == "darwin"* ]; then
	#install_homebrew
	brew install homebrew/science/armadillo boost qt5 autoconf automake libtool 
fi

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
