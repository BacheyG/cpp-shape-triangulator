// Created by Gábor Bácsi
// 4/7/2024

#pragma once

#include "../Vector/Vector.hpp"
#include <vector>

struct TriangulatorAlgorithmMetadata {
	Vector2D<float> innerRightmostVertex;
	Vector2D<float> outerShapeConnectedVertex;
	Vector2D<float> intersectionPoint;
};

typedef std::vector<TriangulatorAlgorithmMetadata> TriangulatorAlgorithmMetadatas;