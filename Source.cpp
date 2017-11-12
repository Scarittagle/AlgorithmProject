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
	//Set Penalty Value
	double penalty = 0.4;
	//For distinguish for loop iter
	unsigned int s = 0;
	//For reseting row index
	unsigned int r = i;
	//Allocate vector array to store the result
	vector <string> output;
	for (unsigned int j = 0; j < cols; j++) {
		double temp = double(arr[i][j]);
		//Col op
		s = j;
		while (r >= 0) {
			if (r == 1) { // first location to cross in diagonal won't be paying penalty
				if (s > 0 && s < cols) { //add left, top, right
					//Compare smallest 
					double smallest = (temp + arr[r - 1][s - 1]); //default smallest value is left
					int smallestColIndex = s - 1; //default smallest index is in left
					string direction = "SE"; //default direction is to SE
					if (smallest >(temp + arr[r - 1][s])) { //compare top
						smallest = (temp + arr[r - 1][s]);
						smallestColIndex = s;
						direction = "S";
					}
					if (smallest > (temp + arr[r - 1][s + 1])) { //compare right
						smallest = (temp + arr[r - 1][s + 1]);
						smallestColIndex = s + 1;
						direction = "SW";
					}
					//
					temp = smallest;
					s = smallestColIndex;
					//save direction to array
					output.push_back(direction);
					cout << direction << endl;
					output.push_back(" ");
					//also the starting index of col
					string TopColIndex = to_string(smallestColIndex);
					output.push_back(TopColIndex);
					//break out of while loop
					break;
				}
				else if (s == 0) {//add top, right
					//Compare smallest 
					double smallest = (temp + arr[r - 1][s]); //default smallest value is top
					int smallestColIndex = s; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > (temp + arr[r - 1][s + 1])) { //compare right
						smallest = (temp + arr[r - 1][s + 1]);
						smallestColIndex = s + 1;
						direction = "SW";
					}
					//
					temp = smallest;
					s = smallestColIndex;
					//save direction to array
					output.push_back(direction);
					cout << direction << endl;
					output.push_back(" ");
					//also the starting index of col
					string TopColIndex = to_string(smallestColIndex);
					output.push_back(TopColIndex);
					//break out of while loop
					break;
				}
				else if (s == cols) {//add top, left
					//Compare smallest 
					double smallest = (temp + arr[r - 1][s]); //default smallest value is top
					int smallestColIndex = s; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > (temp + arr[r - 1][s - 1])) { //compare left
						smallest = (temp + arr[r - 1][s - 1]);
						smallestColIndex = s - 1;
						direction = "SE";
					}
					//
					temp = smallest;
					s = smallestColIndex;
					//save direction to array
					output.push_back(direction);
					cout << direction << endl;
					output.push_back(" ");
					//also the starting index of col
					string TopColIndex = to_string(smallestColIndex);
					output.push_back(TopColIndex);
					//break out of while loop
					break;
				}
			}
			//after first location it will pay 40% penalty with diagonal move.
			else { 
				if (s > 0 && s < cols) {
					//add left, top, right
					//Compare smallest
					double smallest = temp + (double(arr[r - 1][s - 1]) + (double(arr[r - 1][s - 1]) * penalty)); //default smallest value is left
					int smallestColIndex = s - 1; //default smallest index is in left
					string direction = "SE"; //default direction is to SE
					if (smallest > (temp + double(arr[r - 1][s]))) { //compare top
						smallest = (temp + double(arr[r - 1][s]));
						smallestColIndex = s;
						direction = "S";
					}
					if (smallest > (temp + (double(arr[r - 1][s + 1]) + (double(arr[r - 1][s + 1]) * penalty)))) { //compare right
						smallest = (temp + (double(arr[r - 1][s + 1]) + (double(arr[r - 1][s + 1]) * penalty)));
						smallestColIndex = s + 1;
						direction = "SW";
					}
					//
					temp = smallest;
					s = smallestColIndex;
					//save direction to array
					output.push_back(direction);
					cout << direction << endl;
					output.push_back(" ");
				}
				else if (s == 0) {
					//add top, right
					double smallest = temp + (double(arr[r - 1][s])); //default smallest value is top
					int smallestColIndex = s; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > (temp + (double(arr[r - 1][s + 1]) + (double(arr[r - 1][s + 1]) * penalty)))) { //compare right
						smallest = (temp + (double(arr[r - 1][s + 1]) + (double(arr[r - 1][s + 1]) * penalty)));
						smallestColIndex = s + 1;
						direction = "SW";
					}
					//
					temp = smallest;
					s = smallestColIndex;
					//save direction to array
					output.push_back(direction);
					cout << direction << endl;
					output.push_back(" ");
				}
				else if (s == cols) {
					//add top, left
					//Compare smallest 
					double smallest = (temp + double(arr[r - 1][s])); //default smallest value is top
					int smallestColIndex = s; //default smallest index is in top
					string direction = "S"; //default direction is to S
					if (smallest > (temp + (double(arr[r - 1][s - 1]) + (double(arr[r - 1][s - 1]) * penalty)))) { //compare left
						smallest = (temp + (double(arr[r - 1][s - 1]) + (double(arr[r - 1][s - 1]) * penalty)));
						smallestColIndex = s - 1;
						direction = "SE";
					}
					//
					temp = smallest;
					s = smallestColIndex;
					//save direction to array
					output.push_back(direction);
					cout << direction << endl;
					output.push_back(" ");
				}
			}
			if (r != 0) {
				r--;
			}
		}
		//reset Row index
		r = i;
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

	cin.get();
	return 0;
}