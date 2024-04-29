// Created by Gábor Bácsi
// 4/5/2024

#include <unordered_map>
#include <vector>

template<typename T>
struct Vector2D;

struct TriangulatorAlgorithmMetadata;
typedef std::vector<TriangulatorAlgorithmMetadata> TriangulatorAlgorithmMetadatas;

class Triangulator {
private:
	static float pointToHorizontalSegmentIntersectDistance(const Vector2D<float>& origin, const Vector2D<float>& segmentA, const Vector2D<float>& segmentB);
	static bool getShapeOrientation(const std::vector<Vector2D<float>>& shape);
	static bool getShapeLinkedOrientation(const std::vector<Vector2D<float>>& shape, const std::vector<int>& nextIndices);
	static void constructShapeLinkedList(std::vector<int>& nextIndices, int startIndex = 0, int endIndex = 0);
	static int getRightMostVertexIndex(const std::vector<Vector2D<float>>& shape, int startIndex, int endIndex);
	static bool pointInTriangle(const Vector2D<float>& p0, const Vector2D<float>& p1, const Vector2D<float>& p2, const Vector2D<float>& p);
	static bool holeSortFunction(std::pair<float, int> a, std::pair<float, int> b);
	static void combineSortedHoles(std::vector<Vector2D<float>>& result, const std::vector<std::vector<Vector2D<float>>> holes, std::vector<int>& holeIndices);
	static void mergeShapeWithHoles(std::vector<Vector2D<float>>& vertices, std::vector<int>& nextIndices, const std::vector<std::vector<Vector2D<float>>>& holes, std::unordered_map<int, int>& clonedIndices, int& endOfOuterShape, TriangulatorAlgorithmMetadatas* metaDatas = nullptr);
	static int getOptimizedIndex(int index, const std::unordered_map<int, int>* originalVerticesMap);
	static float getTriangleDoubleArea(Vector2D<float> a, Vector2D<float> b, Vector2D<float> c);
	static bool anyPointInTriangle(const std::vector<Vector2D<float>>& shape, int i1, int i2, int i3, const std::vector<int>& nextIndices);
	static void earClipMergedShapes(std::vector<Vector2D<float>>& vertices, std::vector<int>& triangles, std::vector<int>& nextIndices, const std::unordered_map<int, int>* originalVerticesMap = nullptr);
public:
	static void earClipShape(std::vector<Vector2D<float>>& vertices, std::vector<int>& indices);
	static void earClipShapeWithHole(std::vector<Vector2D<float>>& vertices, std::vector<int>& indices, const std::vector<std::vector<Vector2D<float>>>& holes, TriangulatorAlgorithmMetadatas* metaDatas = nullptr);
};