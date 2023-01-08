#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <string>
#include <vector>

class Vertex{
private:
    // every single vertex is identified by a string "vertex"
	std::string vertex;
    // store the minimum distance (non-negative)
	unsigned long minimum_distance; 
    // store the adjacencies (neighboring vertices)
	std::vector<std::string> adjacencies;
	bool prev;

public:
	friend class Graph;
	Vertex() { vertex = ""; } // Constructor
	~Vertex() {} // Destructor
};
#endif 
