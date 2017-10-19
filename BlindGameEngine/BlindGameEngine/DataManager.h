#pragma once
#include <fbxsdk.h>
#include <vector>
#include <map>
class DataManager
{
public:
	enum class datatype
	{
		Mesh
	};
private:
	struct dataobject
	{
		datatype type;
		void* data;
	};

	//std::vector<Mesh*> meshes;

	std::map<std::string, dataobject> datamap;
	Mesh* LoadMeshFromNode(FbxNode * node);
	DataManager();
public:
	~DataManager();



	//Takes in a path to a mesh, FBX format, and loads it into our mesh structure.
	//returns true if success
	bool LoadMesh(const char * path, const char* name);
	//returns the pointer requested, null if bad
	Mesh* GetMesh(const char* name);

	static DataManager* getInstance()
	{
		static DataManager* me = new DataManager();
		return me;
	}
};

