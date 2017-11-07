//Algorithm Project 2 Coding Part
//Weiwei Su (The Programmer)
//Kenneth Li
//Antonio Leverghetta
//Last Modification Date: 11/06/2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	unsigned int rows = 0, cols = 0;
	int test = 0;
	//Read input file
	ifstream inputFile;
	inputFile.open("input.txt");
	if (!inputFile) {
		cout << "The file does not exist";
	}
	else {
		//Read Number of Rows and Columns from the first line
		if (inputFile.good()) {
			string sLine;
			getline(inputFile, sLine);
			stringstream ctoi(sLine);
			ctoi >> rows;
			ctoi >> cols;
		}
	}
	//Dynamically allocate memory for the array
	int **arr = new int*[rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	
	//input element into the array to make a matrix
	while (!inputFile.eof()) {
		for (unsigned int i = 0; i < rows; i++)
		{
			string sLine;
			getline(inputFile, sLine); //it will start reading on second line since I didn't rewind
			stringstream ctoi(sLine);
			for (unsigned int j = 0; j < cols; j++)
			{
				ctoi >> arr[i][j];
			}
		}
	}

	//Calculate Distance
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			cout << arr[i][j];
		}
	}
	

	//Deallocate the memory
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	cin.ignore();
	cin.get();
	return 0;
}