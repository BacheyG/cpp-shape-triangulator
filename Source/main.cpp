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
	std::vector<Vector2D<float>> verticesQuad{ {0,0}, {0,1}, {1, 1}, {1, 0} };
	std::vector<int> indices;

	Triangulator::earClipShape(verticesQuad, indices);
	PlotSvg::plotPoligonToSvg("polygonQuad.svg", verticesQuad, indices);

	// Case study: A bit more complex shape: adding a cut to make it concave.
	std::vector<Vector2D<float>> verticesConcave{ {0,0}, {0,1}, {1, 1}, {0.75, 0.5}, {1, 0} };
	indices.clear();

	Triangulator::earClipShape(verticesConcave, indices);
	PlotSvg::plotPoligonToSvg("polygonConcave.svg", verticesConcave, indices);


	// Case study: Another example of handling concave shapes, don't include an ear if other vertices are within the triangle.
	std::vector<Vector2D<float>> verticesConcave2{ {0,1}, {0.5f,0}, {1, 1}, {0.5f, 0.2f} };
	indices.clear();

	Triangulator::earClipShape(verticesConcave2, indices);
	PlotSvg::plotPoligonToSvg("polygonConcave2.svg", verticesConcave2, indices);

	// Case study: Drawing a concave star.
	std::vector<Vector2D<float>> verticesStar{ {26.934f,1.318f}, {35.256f,18.182f}, {53.867f,20.887f}, {40.4f,34.013f}, {43.579f,52.549f}, {26.934f,43.798f}, {10.288f,52.549f}, {13.467f,34.013f}, {0,20.887f}, {18.611f,18.182f} };

	indices.clear();

	Triangulator::earClipShape(verticesStar, indices);
	PlotSvg::plotPoligonToSvg("polygonStar.svg", verticesStar, indices);

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

	// Case study: Drawing a letter A.
	std::vector<Vector2D<float>> verticesA{ { 30.037f, 1.631f}, { 27.470f, 6.078f}, { 16.539f, 30.930f}, { 16.115f, 30.930f}, { 5.276f, 6.750f}, { 2.683f, 2.180f}, { -0.000f, 0.828f}, { -0.000f, 0.000f}, { 10.079f, 0.000f}, { 10.079f, 0.828f}, { 7.107f, 1.363f}, { 6.078f, 3.240f}, { 6.705f, 5.678f}, { 7.978f, 8.627f}, { 18.683f, 8.627f}, { 20.291f, 4.850f}, { 20.961f, 3.174f}, { 21.096f, 2.348f}, { 20.606f, 1.319f}, { 18.126f, 0.831f}, { 17.522f, 0.831f}, { 17.522f, 0.003f}, { 32.181f, 0.003f}, { 32.181f, 0.831f}, { 30.037f, 1.631f} };
	std::vector<std::vector<Vector2D<float>>> holesA{ { {9.6f, 12.5f}, {12.37f, 19.2f}, {14.71f, 19.2f}, {17.03f, 12.5f} } };

	indices.clear();

	Triangulator::earClipShapeWithHole(verticesA, indices, holesA);
	PlotSvg::plotPoligonToSvg("polygonLetterA.svg", verticesA, indices);
	return 0;
}
