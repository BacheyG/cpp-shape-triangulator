#include <iostream>
#include <vector>
#include "earcut.hpp"

void printGeometry(const std::vector<Vertex> vertices, const std::vector<int> indices) {
	std::cout << "Vertices: ";
	for (const auto& vertex : vertices) {
		std::cout << "{" << vertex.X << ", " << vertex.Y << "} ";
	}
	std::cout << std::endl;
	std::cout << "Indices: [";
	int counter = 0;
	for (const auto& index : indices) {
		if (counter++ > 0) {
			std::cout << ", ";
		}
		std::cout << index;
	}
	std::cout << "]";

	std::cout << std::endl;
}

int main()
{
	std::vector<Vertex> vertices{ {1,1}, {1.7f,0.3f}, {1.9f,0}, {1.1f,0.2f}, {0,0}, {0,1}, {1,1} };
	std::vector<std::vector<Vertex>> holes{ { {0.55f,0.55f}, {0.27f,0.55f}, {0.2f,0.2f}, {0.85f,0.45f}, {0.55f,0.55f} }, 
										    { {1.4f,0.5f}, {1.2f,0.5f}, {1.2f,0.25f}, {1.4f, 0.5f} } };
	std::vector<int> indices;

	earClipWithHole(vertices, indices, holes);
	printGeometry(vertices, indices);
	return 0;
}