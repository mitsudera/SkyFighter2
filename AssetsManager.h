#pragma once
#include "CoreMinimal.h"


class MeshDataList;

class KeyFrameAnimData; 

class SkinMeshDataList;

class SkeletonAnimData;

class GameEngine;

class AssetsManager
{


public:
	AssetsManager();
	AssetsManager(GameEngine* gameEngine);
	~AssetsManager();

	void Init(void);
	void Uninit(void);




	int LoadMesh(string filepath);

	MeshDataList* GetMeshDataList(int n);

	KeyFrameAnimData* GetKeyFrameAnimData(int n);


	GameEngine* GetGameEngine(void);

	int LoadMeshAnim(string filepath);

	SkinMeshDataList* GetSkinMeshDataList(int n);
	int LoadSkinMesh(string filepath);

	SkeletonAnimData* GetSkeletonAnimData(int n);
	int LoadSkeletonAnimData(string filepath);

	


private:

	GameEngine* gameEngine;
	vector<MeshDataList*> MeshDataListArray;
	vector<KeyFrameAnimData*>  KeyFrameAnimDataArray;
	vector<SkinMeshDataList*> SkinMeshDataListArray;
	vector<SkeletonAnimData*> SkeletonAnimDataArray;
};

