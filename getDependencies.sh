#!/bin/bash
#getDependencies.sh by Leif Messinger
 grep -Po '#include\s*"\K.+(?=")' | while read -r line ; do
	echo -n " $line"
	./getDependencies.sh < $line
done
