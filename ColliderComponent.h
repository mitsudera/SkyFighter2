#pragma once
#include "TransformComponent.h"

class GameObject;	// overlapÇ™ìoò^ÇµÇΩé©ï™ÅAotherÇ™Ç‘Ç¬Ç©Ç¡ÇΩëäéË
DECLARE_DELEGATE_2_Params(OnComponentBeginOverlapDelegate, Component* overlapComponent, Component* otherComponent)
DECLARE_DELEGATE_2_Params(OnComponentOverlapDelegate, Component* overlapComponent, Component* otherComponent)
DECLARE_DELEGATE_2_Params(OnComponentEndOverlapDelegate, Component* overlapComponent, Component* otherComponent)

class ColliderComponent : public TransformComponent
{
public:
	ColliderComponent();
	~ColliderComponent();

	OnComponentBeginOverlapDelegate OnComponentBeginOverlapEvent;
	OnComponentOverlapDelegate OnComponentOverlapEvent;
	OnComponentEndOverlapDelegate OnComponentEndOverlapEvent;

	void OnComponentBeginOverlap(ColliderComponent* otherCollider);
	void OnComponentOverlap(ColliderComponent* otherCollider);
	void OnComponentEndOverlap(ColliderComponent* otherCollider);

	vector<GameObject*>& GetOverlapGameObject(void);
	vector<ColliderComponent*>& GetOverlapColliderComponent(void);
	BOOL IsOverlap(void);

	BOOL IsTrigger(void);
	void SetTrigger(BOOL isTrigger);

protected:
	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;
	virtual void BeginPlay(void) override;
	virtual void UpdatePlay(void) override;
	virtual void EndPlay(void) override;

private:
	vector<GameObject*> overlapGameObjects;
	vector<ColliderComponent*> overlapColliderComponents;
	BOOL m_isTrigger;
};