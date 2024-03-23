#include <unordered_map>
#include <vector>

struct Vertex {
public:
	Vertex(float x, float y) : X(x), Y(y) {};
	float X;
	float Y;
};

float squareDistance(const Vertex& p1, const Vertex& p2);
float pointToHorizontalSegmentIntersectDistance(const Vertex& origin, const Vertex& segmentA, const Vertex& segmentB);
bool getShapeOrientation(const std::vector<Vertex>& shape);
bool getShapeLinkedOrientation(const std::vector<Vertex>& shape, const std::vector<int>& nextIndices);
void constructShapeLinkedList(std::vector<int>& nextIndices, int startIndex = 0, int endIndex = 0);
int getRightMostVertexIndex(const std::vector<Vertex>& shape, int startIndex, int endIndex);
bool pointInTriangle(const Vertex& p0, const Vertex& p1, const Vertex& p2, const Vertex& p);
bool holeSortFunction(std::pair<float, int> a, std::pair<float, int> b);
void combineSortedHoles(std::vector<Vertex>& result, const std::vector<std::vector<Vertex>> holes, std::vector<int>& holeIndices);
void mergeShapeWithHoles(std::vector<Vertex>& vertices, std::vector<int>& nextIndices, const std::vector<std::vector<Vertex>>& holes, std::unordered_map<int, int>& clonedIndices, int& endOfOuterShape);
int getOptimizedIndex(const std::unordered_map<int, int>& originalVerticesMap, int index);
bool anyPointInTriangle(const std::vector<Vertex>& shape, int i1, int i2, int i3, const std::vector<int>& nextIndices);
void earClipWithoutHole(std::vector<Vertex>& vertices, std::vector<int>& triangles, std::vector<int>& nextIndices, const std::unordered_map<int, int>& originalVerticesMap);
void earClipWithHole(std::vector<Vertex>& vertices, std::vector<int>& indices, const std::vector<std::vector<Vertex>>& holes);