// Created by Gábor Bácsi
// 4/5/2024

#include "Triangulator.hpp"
#include "../Vector/Vector.hpp"
#include "../PlotSvg/PlotSvg.hpp"

#include <iostream>
#include <vector>

int main()
{
	// Case study: A simple convex polygon: a convex quad.
	std::vector<Vector2D<float>> verticesQuad{ {0,0}, {0,1}, {1, 1}, {1, 0}};
	std::vector<int> indices;

	Triangulator::earClipShape(verticesQuad, indices);
	PlotSvg::plotPoligonToSvg("polygonQuad.svg", verticesQuad, indices);

	// Case study: A concave polygon with 2 holes, demonstrating how hole processing order is important: always start with the hole that has the rightmost X coordinate.
	std::vector<Vector2D<float>> vertices1{ {1,1}, {1.7f,0.3f}, {1.9f,0}, {1.1f,0.2f}, {0,0}, {0,1}, {1,1} };
	std::vector<std::vector<Vector2D<float>>> holes1{ { {0.55f,0.55f}, {0.27f,0.55f}, {0.2f,0.2f}, {0.85f,0.45f}, {0.55f,0.55f} },
										    { {1.4f,0.5f}, {1.2f,0.5f}, {1.2f,0.25f}, {1.4f, 0.5f} } };
	indices.clear();

	// Case study: A concave polygon where following the bridging algorithm, the bridge would collide with the outer poligon. Extend the algorithm to look for another vertex that is not occluded.
	Triangulator::earClipShapeWithHole(vertices1, indices, holes1);
	PlotSvg::plotPoligonToSvg("polygon1.svg", vertices1, indices);

	indices.clear();

	std::vector<Vector2D<float>> vertices2{ {1,1}, {1.7f,0.7f}, {1.9f,-0.4f}, {1.3f,0.35f}, {0,0}, {0,1}, {1,1} };
	std::vector<std::vector<Vector2D<float>>> holes2{ { {0.55f,0.55f}, {0.27f,0.55f}, {0.18f,0.18f}, {0.85f,0.45f}, {0.55f,0.55f} } };

	Triangulator::earClipShapeWithHole(vertices2, indices, holes2);
	PlotSvg::plotPoligonToSvg("polygon2.svg", vertices2, indices);
	return 0;
}
