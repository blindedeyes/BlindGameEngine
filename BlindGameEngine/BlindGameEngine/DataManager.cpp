#include "stdafx.h"
#include "DataManager.h"

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
			tempVerts[i].position.x = fVert[0];
			tempVerts[i].position.y = fVert[1];
			tempVerts[i].position.z = fVert[2];
			tempVerts[i].position.w = 1;
		}

		//Get Poly info
		unsigned int polyCnt = fMesh->GetPolygonCount();

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

				Vertex vert;
				vert.position = tempVerts[indx].position;
				vert.uv.x = UV[0];
				vert.uv.y = UV[1];
				vert.uv.z = 0;
				vert.uv.w = 1;
				tMesh->Verts.push_back(vert);
			}
		}
		return tMesh;
	}
	else
	{
		for (unsigned int i = 0; i < node->GetChildCount(); ++i)
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

Mesh * DataManager::LoadMesh(const char * path)
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
				return nMesh;
			}
		}
	}
	manager->Destroy();
	return nMesh;
}
