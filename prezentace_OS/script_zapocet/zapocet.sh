#!/bin/bash

: '
To use this script:
1. put in in a folder where your .cpp files reside
2. create a sub-folder in that folder called tests
	alternativly change the contents of variable dirname
3. put pub*.in and pub*.out files in folder tests (* represents integer number; i.e. pub1.in, pub2.in etc.)
4. run script in terminal (./zapocet.sh)
5. to remove all create files by script run it with argument "clear all" (./zapocet.sh clear all)
6. to remove all create files but executable file run the script with argument "clear" only
'

filename=main.out
dirname="tests/" #dir contating our pub tests + .out file
line="-----------------------------------" # line for making output nicer

if [ "$1" == "clear" ] ; then ## if ./zapocet.sh get clear as an argument it removes files starting with diff, output and program
	echo "Clearing... "
	cd $dirname
	for file in *; do
		if [[ -f "$file" && ($file == diff* || $file == output* || $file == program* )  ]]; then
			rm $file
		fi
	done

	if [ "$2" == "all" ]; then
		rm $filename
	fi

	cd ..

else

	#Flags for compilations
	CFLAGS='-std=c++20 -O -Wall -pedantic'
	fileOs=""
	for file in *; do
		if [[ -f "$file" && $file == *.cpp ]]; then
			g++ -c $file  # creates .o files from .cpp files
			fileOName=${file%.cpp}  # removes .cpp
			fileOName=${fileOName}.o  # adds .o
			fileOs+=$fileOName
			fileOs+=" "
		fi
	done


	g++ $CFLAGS $fileOs -o $filename

	for file in $fileOs; do
		rm $file
	done

	chmod +x $filename

	if [ $? -eq 0 ]; then
		echo "Compilation successful"
		echo "Running test cases:"
		echo $line

		mv $filename $dirname
		cd $dirname
		numOfTestsPassed=0
		numOfTestsFailed=0
		for pubFileIn in *;
		do 
			if [[ -f "$pubFileIn" && $pubFileIn == pub*.in ]]; then
				numOfFileOut=${pubFileIn%%.in} # removes .in extension
				numOfFileOut=${numOfFileOut#pub}
				fileOut="output"
				extensionOut=".out"
				fileOut="${fileOut}${numOfFileOut}${extensionOut}"
				pubFileOut="pub"
				pubFileOut="${pubFileOut}${numOfFileOut}${extensionOut}"
				./$filename < $pubFileIn > $fileOut

				if diff -q $pubFileOut $fileOut >/dev/null; then #redirects output of diff to /dev/null which is basically discarted
					echo "Test $numOfFileOut result: ✅"
					rm $fileOut
					numOfTestsPassed="$((numOfTestsPassed+1))"
				else
					echo "Test $numOfFileOut result: ❌"
					differenceOut="diff"
					differenceOut="${differenceOut}${numOfFileOut}${extensionOut}"
					#differenceOut file only displays lines side by side that are not same 
					sdiff -s <(cat -n $pubFileOut) <(cat -n $fileOut) > $differenceOut 
					numOfTestsFailed="$((numOfTestsFailed+1))"
				fi
			fi
		done

		#numOfTestsFailed+numOfTestsPassed is number of tests
		echo $line
		numOfTests=$((numOfTestsFailed+numOfTestsPassed))
		echo "Number of tests passed ✅: $numOfTestsPassed/$numOfTests"
		#scale 2 means 2 decimal places
		successRate=$(echo "scale=2; $numOfTestsPassed * 100 / $numOfTests" | bc)
		echo "Success rate: $successRate%"
		cd ..

	fi
fi
