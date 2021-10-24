#pragma once

#include "mathematics.hpp"
#include "mesh_part.hpp"

#include <memory>
#include <map>

using std::map;
using std::pair;
using std::shared_ptr;

class MeshLoader final
{
public:
	// Voids
	void cacheMeshesMultiThreaded(const vector<string>& meshPaths);
	void clearMeshCache(const string& filePath);

	// Miscellaneous
	const vector<shared_ptr<MeshPart>>* loadMesh(const string& filePath);

private:
	// Miscellaneous
	pair<string, vector<shared_ptr<MeshPart>>> _loadMesh(const string& filePathe);
	map<string, vector<shared_ptr<MeshPart>>> _meshCache;
};