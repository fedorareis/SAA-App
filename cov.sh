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
touch cov.txt cov.csv
echo "" > cov.txt
echo "" > cov.csv
for cov in $COVFILES
do
	if [ -s $cov.gcov ]; then
	sed 's/\s*-:\s\d+:\/\*EOF\*\/.*//' $cov.gcov > $cov.stripped
	echo "===========\nFILE: $cov\n" >> cov.txt
	LINES=$(expr $( wc -l < $cov.stripped ) - 5) 
	COVERED=$(expr $LINES - $(grep -c "#####:" $cov.stripped))
	
	PCT=$(echo "100 * ($COVERED/($LINES))" | bc -l | cut -b 1-5 )
	echo "$cov : ($COVERED/$LINES) covered. ($PCT %)"
	echo "$cov : ($COVERED/$LINES) covered ($PCT %)" >> cov.txt
	echo $cov,$PCT, >> cov.csv
	
	cat $cov.gcov >> cov.txt
	else
		LINES=$(wc -l < $cov)
		COVERED=0
		PCT=0

		echo "$cov : ($COVERED/$LINES) covered. ($PCT %)"
		echo "$cov : ($COVERED/$LINES) covered ($PCT %)" >> cov.txt
		echo $cov,$PCT, >> cov.csv
	fi
done
vim cov.txt

