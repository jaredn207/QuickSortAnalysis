#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

vector<double> readFile(string);
void quickSort(vector<double>&, int, int);
void writeTime(string,double);
void writeSorted(vector<double>,string);
void cleanSS(stringstream&);

int main(int argc, char* argv[])
{
	stringstream ss;
	
	//save time file name
	char* sampleSize = argv[1];
	ss << "t" << sampleSize << ".txt";
	string timeFile = ss.str();
	cleanSS(ss);
	
	//create directory for sorted vectors
	ss << "mkdir s" << sampleSize;
	system(ss.str().c_str());
	cleanSS(ss);
	
	//loop through every generated file
	for(int i = 0; i<100; i++)
	{
		//read the files from the fX folder
		ss << "f" << sampleSize << "/f" << i << ".txt";
		vector<double> vect = readFile(ss.str());
		cleanSS(ss);
		
		//sort and measure the time of the quicksort, then write it to file tX.txt
		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		quickSort(vect, 0, vect.size()-1);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		double timeMilli = time_span.count()*1000;
		writeTime(timeFile,timeMilli);
		
		//write sorted vector to sX.txt
		ss << "s" << sampleSize << "/" << "s" << i << ".txt";
		writeSorted(vect,ss.str());
		cleanSS(ss);
	}
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

//writes the time of a quicksort to file tX.txt
void writeTime(string file, double time)
{
	ofstream fout;
	stringstream ss;
	
	//create blank file
	ss << "cat > " << file;

	//open the file with argument to append
	fout.open(file.c_str(),ios::app);

	//if fail create the blank file
	if(fout.fail())
		system(ss.str().c_str());
	cleanSS(ss);

	//write a time to the file
	ss << time << endl;
	fout << ss.str();
	fout.close();
}

//writes sorted vector to sX/sX.txt
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
