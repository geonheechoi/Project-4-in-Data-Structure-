#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Edge.hpp"
#include "GraphBase.hpp"
#include "Vertex.hpp"

#include <iostream>
#include <iterator>
#include <queue>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>

class Graph : public GraphBase {
private:
	std::deque<Vertex*> vert; //List of vertexes with distances
	std::deque<Edge*> edges; //List of edges and weight
	unsigned long shortest = 0; //Keeps the shortest even after operation
	int minimum = 0; /*get index of node and minimum distances*/
	std::string minimum_ele = ""; 
	//PQ with vector as asending order
	        std::priority_queue<std::pair<unsigned long, std::string>,
					std::vector<std::pair<unsigned long, std::string>>,
					std::greater<std::pair<unsigned long, std::string>>> list;

protected:
	
	void str(std::string inp); // single string input
	void sec_str(std::string str1, std::string str2); //two string inputs
	void start(std::string startLabel); //Starts the path
	void construct(std::string startLabel);//construct the path using the PQ
	void minimum_vertex(std::string& minimum_element); // the minimum index for a vertex
	void get_distance(std::string startLabel); //get distances from the string
	void lay(std::string endLabel, std::vector<std::string>& path); //make a path 
	void path_reset(); //reset the path

public:
	Graph() {} //Constructor for Graph
	~Graph(); //Distructor for Graph
	
	void addVertex(std::string label);
	void removeVertex(std::string label);
	void addEdge(std::string label1, std::string label2, unsigned long weight);
	void removeEdge(std::string label1, std::string label2);
	unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};
#endif 
