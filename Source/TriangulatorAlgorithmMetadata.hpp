// Created by Gábor Bácsi
// 4/7/2024

#pragma once

#include "../Math/Vector.hpp"
#include <vector>

struct TriangulatorAlgorithmMetadata {
	int innerRightmostVertexIndex;
	int outerShapeConnectedVertexIndex;
	float intersectionDistance;
	int outerShapeConnectedVertexIndexBeforeObscureTest;
};

typedef std::vector<TriangulatorAlgorithmMetadata> TriangulatorAlgorithmMetadatas;