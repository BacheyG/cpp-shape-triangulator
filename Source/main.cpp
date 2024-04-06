// Created by Gábor Bácsi
// 4/5/2024

#include "Triangulator.hpp"
#include "../Vector/Vector.hpp"
#include "../PlotSvg/PlotSvg.hpp"

#include <iostream>
#include <vector>

int main()
{
	std::vector<Vector2D<float>> vertices{ {1,1}, {1.7f,0.3f}, {1.9f,0}, {1.1f,0.2f}, {0,0}, {0,1}, {1,1} };
	std::vector<std::vector<Vector2D<float>>> holes{ { {0.55f,0.55f}, {0.27f,0.55f}, {0.2f,0.2f}, {0.85f,0.45f}, {0.55f,0.55f} },
										    { {1.4f,0.5f}, {1.2f,0.5f}, {1.2f,0.25f}, {1.4f, 0.5f} } };
	std::vector<int> indices;

	earClipWithHole(vertices, indices, holes);
	PlotSvg::plotPoligonToSvg("polygon1.svg", vertices, indices);
	return 0;
}
