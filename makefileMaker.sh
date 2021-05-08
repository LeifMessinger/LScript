#!/bin/bash
#makefileMaker.sh by Leif Messinger
#Needs getDependencies.sh
echo -n "output:"
for f in *.cpp; do
	echo -n " ${f%.cpp}.o"
done
echo ""

echo -e -n "\tg++ -std=c++17"
for f in *.cpp; do
	echo -n " ${f%.cpp}.o"
done
echo " -o output"
echo ""


for f in *.cpp; do
	echo -n "${f%.cpp}.o: $f"
	./getDependencies.sh < $f
	echo ""

	echo -e "\tg++ -std=c++17 -c $f"
	echo ""


done

#does not work on windows
echo "clean:"
echo -e "\trm -f -v *.o output"
echo ""

echo "run:"
echo -e "\t./output"
echo ""

echo "debug:"
echo -e -n "\tg++ -std=c++17 -g"
for f in *.cpp; do
	echo -n " ${f}"
done
echo " -o output"
echo ""
