#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

vector<double> readFile(string);
void quickSort(vector<double>&, int, int);
void writeSorted(vector<double>,string);
void cleanSS(stringstream&);

int main(int argc, char* argv[])
{
	stringstream ss;
	ss << argv[1];
	string inputFile = ss.str();
	cleanSS(ss);
	vector<double> vect = readFile(inputFile);
	
	//sort and measure the time
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	quickSort(vect, 0, vect.size()-1);
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	double timeMilli = time_span.count()*1000;

	ss << argv[2];
	string outputFile = ss.str();
	cleanSS(ss);
	writeSorted(vect,outputFile);

	cout << "Sorted: " << inputFile << ". Wrote sorted numbers to: " << outputFile << endl;
	cout << "Took " << timeMilli << " milliseconds to sort the numbers." << endl;
}

//modifies the arguement array and sorts it
void quickSort(vector<double>& array, int left, int right)
{
    int i = left;
    int j = right;
    double temp;
    double pivot = array[(left + right)/2];
 
	//partition
    while(i <= j)
	{
		while (array[i] < pivot)
		{
			i++;
		}  
        while (array[j] > pivot)
		{
			j--;
		}  
        if (i <= j) 
		{
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
	
	//quicksort
    if (left < j)
        quickSort(array, left, j);
    if (i < right)
        quickSort(array, i, right);
}

//read the file into a vector
vector<double> readFile(string file)
{
	ifstream fin;
	string line;
	vector<double> vect;
	stringstream ss;
	
	//try to open file, if no file, return empty vector
	fin.open(file.c_str());
	if(fin.fail())
	{
		fin.close();
		return vect;
	}

	//get the entire length of unsorted numbers
	getline(fin,line);
	
	//put the numbers in a vector
	for(int i = 0; i<line.length();)
	{
		if(i+1==line.length())
		{
			ss << line.at(i);
			vect.push_back(atof(ss.str().c_str()));
			cleanSS(ss);
			fin.close();
			return vect;
		}
		if(line.at(i) != ' ' && line.at(i+1) == ' ') 
		{	
			ss << line.at(i);
			i++;
			vect.push_back(atof(ss.str().c_str()));
			cleanSS(ss);
		}
		else if(line.at(i) != ' ' && line.at(i+1) != ' ') 
		{
			ss << line.at(i);
		}
		i++;
	}
	return vect;
}

void writeSorted(vector<double> vect, string file)
{
	ofstream fout;
	stringstream ss;

	//create a blank file
	ss << "cat > " << file;

	//attempt to open the file, if fail create a blank one
	fout.open(file.c_str());
	if(fout.fail())
		system(ss.str().c_str());
	cleanSS(ss);

	//write the sorted vector to file
	for(int i = 0; i<vect.size(); i++)
	{
		if(i == vect.size()-1)
			ss << vect[i];
		else
			ss << vect[i] << " ";
		fout << ss.str();
		cleanSS(ss);
	}
	fout.close();
}

//cleans stringstream of any inputs
void cleanSS(stringstream& ss)
{
	ss.str("");
	ss.clear();
}
