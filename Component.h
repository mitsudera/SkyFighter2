#pragma once
#include "Object.h"

class GameObject;
class Component : public Object
{
public:
	void SetOwner(GameObject* owner);
	GameObject* GetOwner(void);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Uninit(void);
	virtual void BeginPlay(void);
	virtual void UpdatePlay(void);
	virtual void EndPlay(void);

	virtual void SetName(string name) override;
private:
	GameObject* ownerGameObject;
};