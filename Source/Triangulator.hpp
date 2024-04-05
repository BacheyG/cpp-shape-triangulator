// Created by Gábor Bácsi
// 4/5/2024

#include <unordered_map>
#include <vector>

template<typename T>
struct Vector2D;

float squareDistance(const Vector2D<float>& p1, const Vector2D<float>& p2);
float pointToHorizontalSegmentIntersectDistance(const Vector2D<float>& origin, const Vector2D<float>& segmentA, const Vector2D<float>& segmentB);
bool getShapeOrientation(const std::vector<Vector2D<float>>& shape);
bool getShapeLinkedOrientation(const std::vector<Vector2D<float>>& shape, const std::vector<int>& nextIndices);
void constructShapeLinkedList(std::vector<int>& nextIndices, int startIndex = 0, int endIndex = 0);
int getRightMostVertexIndex(const std::vector<Vector2D<float>>& shape, int startIndex, int endIndex);
bool pointInTriangle(const Vector2D<float>& p0, const Vector2D<float>& p1, const Vector2D<float>& p2, const Vector2D<float>& p);
bool holeSortFunction(std::pair<float, int> a, std::pair<float, int> b);
void combineSortedHoles(std::vector<Vector2D<float>>& result, const std::vector<std::vector<Vector2D<float>>> holes, std::vector<int>& holeIndices);
void mergeShapeWithHoles(std::vector<Vector2D<float>>& vertices, std::vector<int>& nextIndices, const std::vector<std::vector<Vector2D<float>>>& holes, std::unordered_map<int, int>& clonedIndices, int& endOfOuterShape);
int getOptimizedIndex(const std::unordered_map<int, int>& originalVerticesMap, int index);
bool anyPointInTriangle(const std::vector<Vector2D<float>>& shape, int i1, int i2, int i3, const std::vector<int>& nextIndices);
void earClipWithoutHole(std::vector<Vector2D<float>>& vertices, std::vector<int>& triangles, std::vector<int>& nextIndices, const std::unordered_map<int, int>& originalVerticesMap);
void earClipWithHole(std::vector<Vector2D<float>>& vertices, std::vector<int>& indices, const std::vector<std::vector<Vector2D<float>>>& holes);