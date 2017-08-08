#pragma once
#include <fbxsdk.h>

class DataManager
{
	Mesh* LoadMeshFromNode(FbxNode * node);
public:
	DataManager();
	~DataManager();

	//Takes in a path to a mesh, FBX format, and loads it into our mesh structure.
	Mesh * LoadMesh(const char * path);
};

