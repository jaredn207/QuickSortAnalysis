#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

void mkFile(double,string);
void cleanSS(stringstream&);

int main(int argc, char* argv[])
{
	//amount of numbers in each file
	double size = stod(argv[1]);

	stringstream ss;
	ss << "mkdir f" << (int)(size);
	system(ss.str().c_str());
	for(int i=0; i<100; i++)
	{
		cleanSS(ss);
		ss << "f" << size << "/" << "f" << i << ".txt";
		mkFile(size,ss.str());
	}
}

void mkFile(double size, string name)
{
	ofstream fout;
	stringstream ss;
	
	//make blank file
	ss << "cat > " << name;
	
	//attempt to open file, if fail, create a blank one
	fout.open(name.c_str());
	if(fout.fail())
		system(ss.str().c_str());
	
	//create random float point numbers between 0.1 and size(10.0, 100.0, 1000.0, ect)
	random_device rd;
	default_random_engine generator(rd());
	uniform_real_distribution<double> distribution(0.1,size);
	double random = distribution(generator);

	//write to the file the random numbers
	for(int i=0; i<size;i++)
	{
		cleanSS(ss);
		if(i < size)
			ss << random << " ";
		else
			ss << random;
		fout << ss.str();
		random = distribution(generator);
	}
	fout.close();
}

//cleans the arguement stringstream
void cleanSS(stringstream& ss)
{
	ss.str("");
	ss.clear();
}
