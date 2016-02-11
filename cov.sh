if [ ! -d _build_cov ]; then
	mkdir _build_cov
fi
cd _build_cov
cmake -DPROFILE=ON -DBUILD_PROTOBUF=OFF ..
make
./test/test_all
if [ -d covInfo ] ; then
	rm -r covInfo
fi
mkdir covInfo
SOURCES=$(find ../src -name "*.cpp")
cp $SOURCES ./covInfo 
find . -name "*.gc*"  -print0 | xargs -0 -I{} cp {} ./covInfo
cd covInfo
find . -name "*.gc*" -print0 | xargs -0 -I{} echo mv {} {} | sed 's/\.cpp//2' | bash
COVFILES=$(find . -name "*.cpp")
xcrun llvm-cov gcov $COVFILES
touch cov.txt
for cov in $COVFILES
do
	echo "===========\nFILE: $cov\n" >> cov.txt
	cat $cov.gcov >> cov.txt
done
vim cov.txt

