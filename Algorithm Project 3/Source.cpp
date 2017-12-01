//Algorithm Project 3
//Building Word Ladder App with using Boost Graph Libraries
//WEIWEI SU
//U17420699
//Date: 11/30/2017

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;

//This will check whether if two words are adjacent to each other even with different length
bool isAdjacent(string s1, string s2)
{
	int s1Length = s1.length();
	int	s2Length = s2.length();
	
	//If two string's length difference is more than one...
	if (abs(s1Length - s2Length) > 1) {
		return false;
	}

	//set count of differences
	int count = 0; 

	int i = 0, j = 0;
	while (i < s1Length && j < s2Length){
		//If current char of two strings doesn't match
		if (s1[i] != s2[j]){
			if (count == 1) {
				return false;
			}
			if (s1Length > s2Length) {
				i++;
			}
			else if (s1Length < s2Length) {
				j++;
			}
			else{
				i++;
				j++;
			} 
			count++;
		}
		else{ //If current char of two strings are match
			i++;
			j++;
		}
	}
	// If last character is extra in any string
	if (i < s1Length || j < s2Length) {
		count++;
	}
	return count == 1;
}

//Define structures for graph properties
typedef struct vertexProps {
	string name;

}vProp;

typedef struct edgeProps {
	int weight = 1; //Default is 1 and only be 1
}eProp;

//use to store startword and endword(target)
struct linkwords {
	string startword;
	string endword;
};

//Driver
int main()
{
	//Define & initialize graph structure.
	int numOfinput;
	typedef adjacency_list<vecS, vecS, undirectedS, vProp, eProp> graph;
	typedef graph::vertex_descriptor vertexDes;
	typedef graph::edge_descriptor edgeDes;
	graph g; //Graph Object

	//Read input file
	ifstream inputFile;
	inputFile.open("input.txt");
	if (!inputFile) {
		cout << "The file does not exist";
	}
	else {
		//Read Number of inputs from the first line
		if (inputFile.good()) {
			string sLine;
			getline(inputFile, sLine);
			stringstream ctoi(sLine);
			ctoi >> numOfinput;
		}
	}

	//Load Dictionary
	ifstream dictionary;
	//vertexDes t;
	vector<vertexDes>vertexIndex;
	dictionary.open("dictionary.txt");
	if (!dictionary) {
		cout << "The file does not exist";
	}
	else {
		int i = 0; //Index for vertexIndex
		string sLine;
		while (getline(dictionary, sLine)) {
			sLine.pop_back();
			vertexIndex.push_back(add_vertex(g));
			g[vertexIndex[i]].name = sLine;
			i++;
		}
	}

	//add edges into the graph, edge weight is set in edgeProp
	for (unsigned int i = 0; i != num_vertices(g); i++) {
		for (unsigned int j = 0; j != num_vertices(g); j++) {
			if (isAdjacent(g[vertexIndex[i]].name, g[vertexIndex[j]].name)) {
				add_edge(vertexIndex[i], vertexIndex[j], g);
			}
		}
	}

	//plug start word and end word to perform ladder
	vector<linkwords>inputs;
	int first = -1; //Default -1 states the word does not exist on current dictionary.
	int second = -1;

	while (numOfinput > 0) {
		string sLine;
		getline(inputFile, sLine);
		istringstream seperate(sLine);
		istream_iterator<string> begin(seperate), end;
		vector<string>words(begin, end);
		linkwords w{
			words[0],
			words[1]
		};
		inputs.push_back(w);
		numOfinput--;
	}

	//Setup the output file here.
	ofstream output;
	output.open("output.txt");

	//iter the vector
	for (auto && w : inputs) {
		//Check whether the start word and endword is in the dictionary otherwise it won't work
		for (unsigned int i = 0; i < num_vertices(g); i++){
			if (g[vertexIndex[i]].name == w.startword){
				first = i;
				break;
			}
		}
		for (unsigned int j = 0; j < num_vertices(g); j++){
			if (g[vertexIndex[j]].name == w.endword){
				second = j;
				break;
			}
		}

		if (first == (-1)) {
			cout << "Starting word is not in the dictionary" << endl;
			return 0;
		}
		else if (second == (-1)) {
			cout << "Ending word is not in the dictionary" << endl;
			return 0;
		}
		else {
			//Call Algorithm here
			vector<int> distances(num_vertices(g));
			vector<vertexDes> predecessors(boost::num_vertices(g));

			dijkstra_shortest_paths(g, vertexIndex[first],
				weight_map(get(&edgeProps::weight, g))
				.distance_map(make_iterator_property_map(distances.begin(), get(vertex_index, g)))
				.predecessor_map(make_iterator_property_map(predecessors.begin(), get(vertex_index, g)))
			);

			//Output the result into text file
			typedef vector<edgeDes> pathfinder;
			pathfinder path;
			vertexDes vertex = vertexIndex[second];
			//push vertex into the pathfinder
			for (vertexDes i = predecessors[vertex]; i != vertex; vertex = i, i = predecessors[vertex]) {
				pair<edgeDes, bool> edgePair = edge(i, vertex, g);
				path.push_back(edgePair.first);
			}
			//Reverse print it since the path order is backwards
			for (pathfinder::reverse_iterator i = path.rbegin(); i != path.rend(); ++i) {
				vertexDes link = source(*i, g); //starts from start word till one word before end word				
				output << g[link].name << " ";
			}
			output << w.endword << endl; //finally set end word in here.
			output << endl << endl;
		}
	}

	//close up all file objects
	inputFile.close();
	dictionary.close();
	output.close();

	return 0;
}