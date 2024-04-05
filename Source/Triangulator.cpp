// Created by Gábor Bácsi
// 4/5/2024

#include "Triangulator.hpp"

#include "../Vector/Vector.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

float squareDistance(const Vector2D<float>& p1, const Vector2D<float>& p2) {
	return (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
}

float pointToHorizontalSegmentIntersectDistance(const Vector2D<float>& origin, const Vector2D<float>& segmentA, const Vector2D<float>& segmentB) {
	float result = -1;
	float denominator = segmentA.Y - segmentB.Y;
	if (denominator != 0) {
		float xPos = origin.Y * (segmentA.X - segmentB.X) - (segmentA.X * segmentB.Y - segmentA.Y * segmentB.X);
		result = xPos / denominator - origin.X;
	}
	return result;
}

bool getShapeOrientation(const std::vector<Vector2D<float>>& shape) {
	float areaSum = 0.0f;
	for (int i = 0; i < shape.size(); ++i) {
		int iNext = (i + 1) % static_cast<int>(shape.size());
		areaSum += (shape[iNext].X - shape[i].X) * (shape[iNext].Y + shape[i].Y);
	}
	return (areaSum >= 0);
}

bool getShapeLinkedOrientation(const std::vector<Vector2D<float>>& shape, const std::vector<int>& nextIndices) {
	float areaSum = 0.0f;
	int i = -1;
	while (i != 0) {
		if (i == -1) {
			i = 0;
		}
		int iNext = nextIndices[i];

		areaSum += (shape[iNext].X - shape[i].X) * (shape[iNext].Y + shape[i].Y);
		i = nextIndices[i];
	}
	return (areaSum >= 0);
}

void constructShapeLinkedList(std::vector<int>& nextIndices, int startIndex, int endIndex) {
	for (int i = startIndex; i < endIndex; ++i) {
		nextIndices.push_back((i + 1 < endIndex) ? i + 1 : startIndex);
	}
}

int getRightMostVertexIndex(const std::vector<Vector2D<float>>& shape, int startIndex, int endIndex) {
	Vector2D<float> rightMostVertex = shape[startIndex];
	int rightMostIndex = startIndex;

	for (int i = startIndex; i < endIndex; ++i) {
		if (shape[i].X >= rightMostVertex.X) {
			rightMostVertex = shape[i];
			rightMostIndex = i;
		}
	}
	return rightMostIndex;
}

bool pointInTriangle(const Vector2D<float>& p0, const Vector2D<float>& p1, const Vector2D<float>& p2, const Vector2D<float>& p) {
	if (squareDistance(p0, p) == 0.0 || squareDistance(p1, p) == 0.0 || squareDistance(p2, p) == 0.0) {
		return false;
	}
	float s = (p0.X - p2.X) * (p.Y - p2.Y) - (p0.Y - p2.Y) * (p.X - p2.X);
	float t = (p1.X - p0.X) * (p.Y - p0.Y) - (p1.Y - p0.Y) * (p.X - p0.X);

	if ((s < 0) != (t < 0) && s != 0 && t != 0) {
		return false;
	}

	float d = (p2.X - p1.X) * (p.Y - p1.Y) - (p2.Y - p1.Y) * (p.X - p1.X);
	return d == 0.0 || (d < 0) == (s + t <= 0.0);
}

bool holeSortFunction(std::pair<float, int> a, std::pair<float, int> b) { return (a.first > b.first); }


void combineSortedHoles(std::vector<Vector2D<float>>& result, const std::vector<std::vector<Vector2D<float>>> holes, std::vector<int>& holeIndices) {

	std::vector<std::pair<float, int>> rightMostPositions;
	int count = 0;
	for (const auto& hole : holes) {
		int rightMostIndex = getRightMostVertexIndex(hole, 0, static_cast<int>(hole.size()));
		rightMostPositions.push_back(std::make_pair(hole[rightMostIndex].X, count));
		++count;
	}
	sort(rightMostPositions.begin(), rightMostPositions.end(), holeSortFunction);
	for (const auto& rightMostPosition : rightMostPositions) {
		for (const Vector2D<float>& vertex : holes[rightMostPosition.second]) {
			result.push_back(vertex);
		}
		holeIndices.push_back(static_cast<int>(result.size()));
	}
}

void mergeShapeWithHoles(std::vector<Vector2D<float>>& vertices, std::vector<int>& nextIndices, const std::vector<std::vector<Vector2D<float>>>& holes, std::unordered_map<int, int>& clonedIndices, int& endOfOuterShape) {
	endOfOuterShape = static_cast<int>(vertices.size());
	int outerOffset = endOfOuterShape;
	std::vector<int> holeIndices;
	combineSortedHoles(vertices, holes, holeIndices);
	for (const auto& holeIndex : holeIndices) {
		int endOfCurrentInner = holeIndex;
		constructShapeLinkedList(nextIndices, endOfOuterShape, endOfCurrentInner);
		endOfOuterShape = endOfCurrentInner;
	}
	endOfOuterShape = outerOffset;
	for (const auto& holeIndex : holeIndices) {
		int endOfCurrentInner = holeIndex;
		int innerIndex = getRightMostVertexIndex(vertices, endOfOuterShape, endOfCurrentInner);

		// Find the vertex in the outer circle to connect with inner : cast a ray to the right.
		float t = std::numeric_limits<float>::max();
		int outerIndex = 0;
		int iCurrent = -1;
		while (iCurrent != 0) {
			if (iCurrent == -1) {
				iCurrent = 0;
			}
			int iNext = nextIndices[iCurrent];

			if ((vertices[iCurrent].Y > vertices[innerIndex].Y && vertices[iNext].Y <= vertices[innerIndex].Y) || (vertices[iCurrent].Y < vertices[innerIndex].Y && vertices[iNext].Y >= vertices[innerIndex].Y)) {
				float currt = pointToHorizontalSegmentIntersectDistance(vertices[innerIndex], vertices[iCurrent], vertices[iNext]);
				if (currt > 0 && currt < t) {
					t = currt;
					// If we intersect with a vertex, we consider this the vertex we were looking for
					if (squareDistance(vertices[iNext], Vector2D<float>(vertices[innerIndex].X + t, vertices[innerIndex].Y)) < std::numeric_limits<float>::epsilon()) {
						outerIndex = iNext;
						// We look for the adjacent vertex on the intersected segment that has larger X
					}
					else {
						outerIndex = (vertices[iCurrent].X > vertices[iNext].X) ? iCurrent : iNext;
					}
				}
			}
			iCurrent = nextIndices[iCurrent];
		}
		// Check if found outer vertex is obscuredand get the vertex that is visible.
		float dOuterPoint = abs(vertices[innerIndex].Y - vertices[outerIndex].Y);
		for (int i = 0; i < endOfOuterShape; ++i) {
			if (pointInTriangle(Vector2D<float>(vertices[innerIndex].X + t, vertices[innerIndex].Y), vertices[innerIndex], vertices[outerIndex], vertices[i])) {
				float newDouterPoint = abs(vertices[innerIndex].Y - vertices[i].Y);
				if (newDouterPoint < dOuterPoint) {
					dOuterPoint = newDouterPoint;
					outerIndex = i;
				}
			}
		}

		vertices.push_back(vertices[innerIndex]);
		vertices.push_back(vertices[outerIndex]);
		int clonedInnerIndex = static_cast<int>(nextIndices.size());
		int clonedOuterIndex = static_cast<int>(nextIndices.size()) + 1;
		clonedIndices[clonedInnerIndex] = innerIndex;
		clonedIndices[clonedOuterIndex] = outerIndex;
		// Add clone of inner vertex and next directs to original inner circle, this will be when we enter the inner circle
		nextIndices.push_back(nextIndices[innerIndex]);
		// Add clone of outer vertex and next directs to original outer circle, this will be when we leave the inner circle
		nextIndices.push_back(nextIndices[outerIndex]);
		// Make the original outer vertex point to the cloned inner vertex, this will be when we enter the inner circle
		nextIndices[outerIndex] = clonedInnerIndex;
		// Make the original inner vertex point to the outer vertex, this will be when we leave the inner circle
		nextIndices[innerIndex] = clonedOuterIndex;

		endOfOuterShape = endOfCurrentInner;
	}
}

int getOptimizedIndex(const std::unordered_map<int, int>& originalVerticesMap, int index) {
	const auto& record = originalVerticesMap.find(index);
	return record != originalVerticesMap.end() ? record->second : index;
}

bool anyPointInTriangle(const std::vector<Vector2D<float>>& shape, int i1, int i2, int i3, const std::vector<int>& nextIndices) {
	int current = nextIndices[i3];
	while (current != i1) {
		if (pointInTriangle(shape[i1], shape[i2], shape[i3], shape[current])) {
			return true;
		}
		current = nextIndices[current];
	}
	return false;
}

void earClipWithoutHole(std::vector<Vector2D<float>>& vertices, std::vector<int>& triangles, std::vector<int>& nextIndices, const std::unordered_map<int, int>& originalVerticesMap) {
	bool globalOrientation = getShapeLinkedOrientation(vertices, nextIndices);
	if (vertices.size() >= 3) {
		int i1 = 0;
		int i2 = nextIndices[i1];
		int i3 = nextIndices[i2];
		while (i1 != i3 && i2 != i1) {
			if (getShapeOrientation({ vertices[i1], vertices[i2], vertices[i3] }) == globalOrientation && !anyPointInTriangle(vertices, i1, i2, i3, nextIndices)) {

				triangles.push_back(getOptimizedIndex(originalVerticesMap, i1));
				triangles.push_back(getOptimizedIndex(originalVerticesMap, i2));
				triangles.push_back(getOptimizedIndex(originalVerticesMap, i3));
				nextIndices[i1] = i3;
				i2 = i3;
				i3 = nextIndices[i2];
			}
			else {
				i1 = i2;
				i2 = i3;
				i3 = nextIndices[i3];
			}
		}
	}
}

void earClipWithHole(std::vector<Vector2D<float>>& vertices, std::vector<int>& indices, const std::vector<std::vector<Vector2D<float>>>& holes) {
	if (vertices.size() > 0) {
		std::vector<int> nextIndices;
		std::unordered_map<int, int> originalVerticesMap;
		int endIndexOfOptimizedShape;
		constructShapeLinkedList(nextIndices, 0, static_cast<int>(vertices.size()));
		mergeShapeWithHoles(vertices, nextIndices, holes, originalVerticesMap, endIndexOfOptimizedShape);
		earClipWithoutHole(vertices, indices, nextIndices, originalVerticesMap);
	}
}