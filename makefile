all: masssort quicksort gen

masssort: Newman_Jared_MassSort.cpp
	g++ -o Newman_Jared_MassSort Newman_Jared_MassSort.cpp

quicksort: Newman_Jared_QuickSort.cpp
	g++ -o Newman_Jared_QuickSort Newman_Jared_QuickSort.cpp

gen: Newman_Jared_Generator.cpp
	g++ -o Newman_Jared_Generate Newman_Jared_Generator.cpp

clean:
	rm -f f*/*.txt
	rm -df f*
	rm -f s*/*.txt
	rm -df s*
	rm -f t*.txt
	rm -f Newman_Jared_MassSort
	rm -f Newman_Jared_QuickSort
	rm -f Newman_Jared_Generate
