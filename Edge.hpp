#ifndef EDGE_HPP
#define EDGE_HPP
#include <string>

class Edge {
private:
	std::string v_start; // starting vertex
	std::string v_target; // target vertex
    // every single edge has weight (non-negative)
	unsigned long weight;
public:
	friend class Graph;
	// Constructor ()
	Edge(std::string a = "", std::string b = "", unsigned long w = 0) {
		v_start = a;
		v_target = b;
		weight = w;
	}
    // Destructor
	~Edge() {} 
};
#endif 
