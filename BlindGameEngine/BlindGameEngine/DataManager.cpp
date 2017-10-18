#include "stdafx.h"
#include "DataManager.h"

//Recursive function that loads a mesh from a node.
//If a mesh was within said node, it stops loading.
Mesh * DataManager::LoadMeshFromNode(FbxNode * node)
{
	FbxMesh * fMesh = node->GetMesh();
	Mesh * tMesh;
	if (fMesh)
	{
		tMesh = new Mesh();

		//Get vertex positions temporary
		unsigned int vertCnt = fMesh->GetControlPointsCount();
		Vertex * tempVerts = new Vertex[vertCnt];
		for (unsigned int i = 0; i < vertCnt; ++i)
		{
			FbxVector4 fVert = fMesh->GetControlPointAt(i);
			tempVerts[i].position.x = (float)fVert[0];
			tempVerts[i].position.y = (float)fVert[1];
			tempVerts[i].position.z = (float)fVert[2];
			tempVerts[i].position.w = 1.0f;
		}

		//Get Poly info
		unsigned int polyCnt = fMesh->GetPolygonCount();
		tMesh->Verts.reserve(polyCnt);
		FbxStringList uvsetlist;
		fMesh->GetUVSetNames(uvsetlist);
		//For each poly
		for (unsigned int i = 0; i < polyCnt; ++i)
		{
			//For each vert in poly
			for (unsigned int vId = 0; vId < 3; ++vId)
			{
				FbxVector2 UV;
				bool unmapped;
				fMesh->GetPolygonVertexUV(i, vId, uvsetlist[0], UV, unmapped);
				int indx = fMesh->GetPolygonVertex(i, vId);
				FbxVector4 norm;
				fMesh->GetPolygonVertexNormal(i, vId, norm);
				Vertex vert;
				vert.position = tempVerts[indx].position;

				vert.uv.x = (float)UV[0];
				vert.uv.y = (float)UV[1];
				vert.uv.z = 0;
				vert.uv.w = 1;

				vert.normal.x = (float)norm[0];
				vert.normal.y = (float)norm[1];
				vert.normal.z = (float)norm[2];
				vert.normal.w = (float)norm[3];

				//=====================================================================
				//Unique check
				//O(n) solution, could possibly work on speeding this up, 
				//but at this point, this is the best solution, and it only
				//affects load times, not gameplay.
				bool unique = true;
				unsigned int tempindx = 0;
				for (; tempindx < tMesh->Verts.size(); tempindx++)
				{
					if (vert == tMesh->Verts[tempindx])
					{
						unique = false;
						break;
					}
				}

				if (unique)
				{
					tMesh->Indices.push_back(tMesh->Verts.size());
					tMesh->Verts.push_back(vert);
				}
				else
				{
					tMesh->Indices.push_back(tempindx);
				}
				//=====================================================================
			}
		}
		tMesh->Verts.shrink_to_fit();
		tMesh->Indices.shrink_to_fit();

		//cleanup a leaky array
		delete tempVerts;

		return tMesh;
	}
	else
	{
		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			tMesh = LoadMeshFromNode(node->GetChild(i));
			if (tMesh)
			{
				break;
			}
		}
	}

	return tMesh;
}

DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

int DataManager::LoadMesh(const char * path)
{
	Mesh * nMesh = nullptr;
	//Creating the manager for FBX
	FbxManager * manager = FbxManager::Create();
	//Creating settings for FBX
	FbxIOSettings * ios = FbxIOSettings::Create(manager, IOSROOT);
	//Setting settings for fbx
	manager->SetIOSettings(ios);
	//Set up importer
	FbxImporter * importer = FbxImporter::Create(manager, "");
	//Initilze the importer, if failed, return
	if (importer->Initialize(path, -1, manager->GetIOSettings()))
	{
		//setup a new scene
		FbxScene * scene = FbxScene::Create(manager, "newScene");
		//Import the data into the scene
		importer->Import(scene);
		//Clean up the importer
		importer->Destroy();

		FbxGeometryConverter conv(manager);
		if (conv.Triangulate(scene, true))
		{
			FbxNode * root = scene->GetRootNode();
			nMesh = LoadMeshFromNode(root);
			if (nMesh)
			{
				//Do stuff here.
				meshes.push_back(nMesh);

				return (meshes.size()-1);
			}
		}
	}
	manager->Destroy();
	return -1;
}

Mesh * DataManager::GetMesh(int index)
{
	return meshes[index];
}
