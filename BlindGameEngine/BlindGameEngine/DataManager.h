#pragma once
#include <fbxsdk.h>
#include <vector>
class DataManager
{
	
	std::vector<Mesh*> meshes;

	Mesh* LoadMeshFromNode(FbxNode * node);
public:
	DataManager();
	~DataManager();

	enum class datatype
	{
		Mesh
	};

	//Takes in a path to a mesh, FBX format, and loads it into our mesh structure.
	int LoadMesh(const char * path);
	//returns the pointer requested, null if bad
	Mesh* GetMesh(int index);

};

