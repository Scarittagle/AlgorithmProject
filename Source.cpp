//Algorithm Project 2 Coding Part
//Weiwei Su (The Programmer)
//Kenneth Li
//Antonio Leverghetta
//Last Modification Date: 11/06/2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	unsigned int rows = 0, cols = 0;
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
	//locate row to the bottom
	unsigned int i = rows - 1;
	//Allocate vector array to store the result
	vector <string> output;
	for (unsigned int j = 0; j < cols; j++) {
		double temp = double(arr[i][j]);
		while (i >= 0) {
			if (i - 1 == 0) { // first location to cross in diagonal won't be paying penalty
				if (j > 0 && j < cols) { //add left, top, right
					//Compare smallest 
					int smallest = arr[i - 1][j - 1]; //default smallest value is left
					int smallestColIndex = j - 1; //default smallest index is in left
					string direction = "SE"; //default direction is to SE
					if (smallest > arr[i - 1][j]) { //compare top
						smallest = arr[i - 1][j];
						smallestColIndex = j;
						direction = "S";
					}
					if (smallest > arr[i - 1][j + 1]) { //compare right
						smallest = arr[i - 1][j + 1];
						smallestColIndex = j + 1;
						direction = "SW";
					}
					//add smallest to temp
					temp += smallest;
					//save direction to array
					output.push_back(direction);
					output.push_back(" ");
					//also the starting index of col
					string TopColIndex = to_string(smallestColIndex);
					output.push_back(TopColIndex);
				}
				else if (j == 0) {//add top, right
					//Compare smallest 
					int smallest = arr[i - 1][j]; //default smallest value is top
					int smallestColIndex = j; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > arr[i - 1][j + 1]) { //compare right
						smallest = arr[i - 1][j + 1];
						smallestColIndex = j + 1;
						direction = "SW";
					}
					//add smallest to temp
					temp += smallest;
					//save direction to array
					output.push_back(direction);
					output.push_back(" ");
					//also the starting index of col
					string TopColIndex = to_string(smallestColIndex);
					output.push_back(TopColIndex);
				}
				else if (j == cols) {//add top, left
					//Compare smallest 
					int smallest = arr[i - 1][j]; //default smallest value is top
					int smallestColIndex = j; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > arr[i - 1][j - 1]) { //compare left
						smallest = arr[i - 1][j - 1];
						smallestColIndex = j - 1;
						direction = "SE";
					}
					//add smallest to temp
					temp += smallest;
					//save direction to array
					output.push_back(direction);
					output.push_back(" ");
					//also the starting index of col
					string TopColIndex = to_string(smallestColIndex);
					output.push_back(TopColIndex);
				}
			}
			//after first location it will pay 40% penalty with diagonal move.
			else { 
				if (j > 0 && j < cols) {
					//add left, top, right
					//Compare smallest 
					double smallest = double(arr[i - 1][j - 1]) + (double(arr[i - 1][j - 1]) * (0.4)); //default smallest value is left
					int smallestColIndex = j - 1; //default smallest index is in left
					string direction = "SE"; //default direction is to SE
					if (smallest > double(arr[i - 1][j])) { //compare top
						smallest = double(arr[i - 1][j]);
						smallestColIndex = j;
						direction = "S";
					}
					if (smallest > (double(arr[i - 1][j + 1]) + (double(arr[i - 1][j + 1]) * (0.4)))) { //compare right
						smallest = double(arr[i - 1][j + 1]) + ((arr[i - 1][j + 1]) * (0.4));
						smallestColIndex = j + 1;
						direction = "SW";
					}
					//add smallest to temp
					temp += smallest;
					//save direction to array
					output.push_back(direction);
					output.push_back(" ");
				}
				else if (j == 0) {
					//add top, right
					double smallest = double(arr[i - 1][j]); //default smallest value is top
					int smallestColIndex = j; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > (double(arr[i - 1][j + 1]) + (double(arr[i - 1][j + 1]) * (0.4)))) { //compare right
						smallest = double(arr[i - 1][j + 1]) + (double(arr[i - 1][j + 1]) * (0.4));
						smallestColIndex = j + 1;
						direction = "SW";
					}
					//add smallest to temp
					temp += smallest;
					//save direction to array
					output.push_back(direction);
					output.push_back(" ");
				}
				else if (j == cols) {
					//add top, left
					//Compare smallest 
					double smallest = double(arr[i - 1][j]); //default smallest value is top
					int smallestColIndex = j; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > (double(arr[i - 1][j - 1]) + (double(arr[i - 1][j - 1]) * (0.4)))) { //compare left
						smallest = (double(arr[i - 1][j - 1]) + (double(arr[i - 1][j - 1]) * (0.4)));
						smallestColIndex = j - 1;
						direction = "SE";
					}
					//add smallest to temp
					temp += smallest;
					//save direction to array
					output.push_back(direction);
					output.push_back(" ");
				}
			}
			i--;
		}
		//print the array in reverse order
		for (vector<string>::reverse_iterator i = output.rbegin(); i != output.rend(); ++i) {
			cout << *i;
		}
		cout << "\n";
		//Empty out the vector array
		output.clear();
	}



	//Deallocate the memory
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	//cin.get();
	return 0;
}