#include "Graph.hpp"

// Destructor
Graph::~Graph()
{
	for(auto& x : vert) { delete x; }
	for(auto& x : edges) { delete x; }
    vert.clear();
   	edges.clear();
}

// Throw if string input is null
void Graph::str(std::string inp) {
	if (inp.empty()) {
		throw inp;
	}
}

// Throw if both string input are null
void Graph::sec_str(std::string str1, std::string str2) {
	if (str1.empty()) {
		throw str1;
	}
	else if (str2.empty()) {
		throw str2;
	}
	else if (str1.empty() && str2.empty()) {
		throw ("empty.\n");
	}
}

// Creates and adds new vertex with the label
void Graph::addVertex(std::string label)
{
	str(label); 
	Vertex *new_v = new Vertex; // create a vertex
	new_v->vertex = label; // add label
	new_v->minimum_distance = std::numeric_limits<unsigned long>::max();
	new_v-> adjacencies = { "" };
	new_v->prev = false;
	vert.push_back(new_v); // adds a vertex to the graph
}

// Removes the vertex and the edges between vertex and the other vertices
void Graph::removeVertex(std::string label)
{
	str(label);
	// Removes the vertex
	for (std::deque<Vertex*>::iterator p = vert.begin(); p != vert.end();) {
		if ((*p)->vertex == label) {
			vert.erase(p);
		}
		else {}
		++p;
	}
	// Remove the edges
	for (std::deque<Edge*>::iterator q = edges.begin(); q != edges.end();) {
		if (((*q)->v_start == label) || ((*q)->v_target == label)) {
			edges.erase(q);
		}
		else{}
		++q;
	}
}

// Adds an edge of value weight to the graph 
// between the vertex with label1 and label 2
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
	sec_str(label1, label2);
	Edge *newEdge1 = new Edge(label1, label2, weight);
	Edge *newEdge2 = new Edge(label2, label1, weight);
    
    // adds the edge
	edges.push_back(newEdge1);
	edges.push_back(newEdge2);
}

// Removes the edge from the graph between the vertex with label1 and label2
void Graph::removeEdge(std::string label1, std::string label2)
{
	sec_str(label1, label2);
	for (std::deque<Edge*>::iterator it = edges.begin(); it != edges.end();) {
        // removes the edge
		if (((*it)->v_start == label1) && ((*it)->v_target == label2)) {
			edges.erase(it);
		}
		else{}
		++it;
	}
}

// Calculates the shortest path between the vertex 
// with startLabel and endLabel using Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path)
{
	sec_str(startLabel, endLabel);
	start(startLabel);
	construct(startLabel); 
	lay(endLabel, path);
	path_reset();
	return shortest;
}

// The starting point is set to 0 and set the shortest path
void Graph::start(std::string startLabel){
	for (std::deque<Vertex*>::iterator ver = vert.begin(); ver != vert.end();) {
		if ((*ver)->vertex == startLabel) {
			(*ver)->minimum_distance = 0;
			(*ver)->adjacencies.clear();
			(*ver)->adjacencies.push_back(startLabel);
		}
		else{}
		 ++ver;
	}
	list.push(std::make_pair(0, startLabel));
}

// Find the position that have the minimum distance
void Graph::minimum_vertex(std::string& minimum_element){
	int idx = 0;
	for (std::deque<Vertex*>::iterator ver_r = vert.begin(); ver_r != vert.end();) {
        // if the minimum element matches the vertex, get its position
		if ((*ver_r)->vertex == minimum_element) {
			minimum= idx;
		}
		else{ ++idx;}
		 ++ver_r;
	}
}

// Compute the shortest path from the source vertex to every other vertex
// using priority Queue (heap) data structure
void Graph::get_distance(std::string startLabel){
    // every iteration when we visit, we push vertices onto the heap
    // then every iteration take the minimum distance value from the heap
	for (std::deque<Edge*>::iterator r = edges.begin(); r != edges.end();) {
        // Take two vertices and compare the two vertices accordingly
		if ((*r)->v_start == minimum_ele) { 
			for (std::deque<Vertex*>::iterator vr = vert.begin(); vr != vert.end();) {
				if (((*r)->v_target == (*vr)->vertex) &&
					((vert.at(minimum)->minimum_distance + (*r)->weight) < (*vr)->minimum_distance) &&
					((*vr)->prev == false))
				{
					(*vr)->minimum_distance = vert.at(minimum)->minimum_distance + (*r)->weight;

					if (minimum_ele == startLabel) {
						(*vr)->adjacencies.clear();
						(*vr)->adjacencies.push_back(startLabel);
					}
				    if (minimum_ele != startLabel) {
						(*vr)->adjacencies.clear();
						(*vr)->adjacencies = vert.at(minimum)->adjacencies;
						(*vr)->adjacencies.push_back(vert.at(minimum)->vertex);
					}
                    // update and insert the vertex to the heap
					list.push(std::make_pair((*vr)->minimum_distance, (*vr)->vertex));
				}
				else{}
				++vr;
			}
		}
		else{}
		++r;
	}
}

// visit from start to end via all possible paths
void Graph::construct(std::string startLabel){
	for (;!list.empty();) {
		minimum_ele = list.top().second;
		list.pop();
		minimum_vertex(minimum_ele);
		get_distance(startLabel);
		vert.at(minimum)->prev = true;
	}
}

// Put the nodes in the vector with minimum weight and get shortest distances from start to end
void Graph::lay(std::string endLabel, std::vector<std::string>& path){
	for (std::deque<Vertex*>::iterator vtr = vert.begin(); vtr != vert.end();) {
		if (endLabel == (*vtr)->vertex) { 
			shortest = (*vtr)->minimum_distance; 
			(*vtr)->adjacencies.push_back(endLabel);
			path = (*vtr)->adjacencies;
		}
		else{}
		++vtr;
	}

}

// Reset all of the vertexes of the current graph
void Graph::path_reset(){
	for (std::deque<Vertex*>::iterator ver = vert.begin(); ver != vert.end();) {
		(*ver)->minimum_distance = std::numeric_limits<unsigned long>::max();;
		(*ver)->adjacencies = { "" };
		(*ver)->prev = false;
		++ver;
	}
}
