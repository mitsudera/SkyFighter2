#pragma once
#include "ColliderComponent.h"
#include "World.h"
#include "DebugHelper.h"

ColliderComponent::ColliderComponent()
{

}

ColliderComponent::~ColliderComponent()
{

}

void ColliderComponent::Init(void)
{
	TransformComponent::Init();
	SetName("Collider");

}

void ColliderComponent::Update(void)
{
	TransformComponent::Update();

	GetWorld()->GetDebugHelper()->DebugBox(GetWorldMatrix(), XMFLOAT4(1, 0, 0, 1), 1);

	GetWorld()->GetDebugHelper()->DebugSphere(GetWorldLocation(), 6, 8, GetWorldScale().x , XMFLOAT4(1, 1, 1, 1), 1);
}

void ColliderComponent::Uninit(void)
{
	TransformComponent::Uninit();
	this->overlapGameObjects.clear();
}

void ColliderComponent::BeginPlay(void)
{
	TransformComponent::BeginPlay();
}

void ColliderComponent::UpdatePlay(void)
{
	TransformComponent::UpdatePlay();
}

void ColliderComponent::EndPlay(void)
{
	TransformComponent::EndPlay();
}


void ColliderComponent::OnComponentBeginOverlap(ColliderComponent* otherCollider)
{
	this->overlapColliderComponents.push_back(otherCollider);
	this->overlapGameObjects.push_back(otherCollider->GetOwner());

	if (this->OnComponentBeginOverlapEvent.IsValid())
	{
		this->OnComponentBeginOverlapEvent.Execute(this, otherCollider);
	}
}

void ColliderComponent::OnComponentOverlap(ColliderComponent* otherCollider)
{
	if (this->OnComponentOverlapEvent.IsValid())
	{
		this->OnComponentOverlapEvent.Execute(this, otherCollider);
	}
}

void ColliderComponent::OnComponentEndOverlap(ColliderComponent* otherCollider)
{
	for (int i = 0; i < this->overlapColliderComponents.size(); i++)
	{
		if (this->overlapColliderComponents[i] == otherCollider)
		{
			this->overlapColliderComponents.erase(overlapColliderComponents.begin() + i);
		}
		break;
	}
	
	for (int i = 0; i < this->overlapGameObjects.size(); i++)
	{
		if (this->overlapGameObjects[i] == otherCollider->GetOwner())
		{
			this->overlapGameObjects.erase(overlapGameObjects.begin() + i);
		}
		break;
	}

	if (this->OnComponentEndOverlapEvent.IsValid())
	{
		this->OnComponentEndOverlapEvent.Execute(this, otherCollider);
	}
}

vector<GameObject*>& ColliderComponent::GetOverlapGameObject(void)
{
	return this->overlapGameObjects;
}

vector<ColliderComponent*>& ColliderComponent::GetOverlapColliderComponent(void)
{
	return this->overlapColliderComponents;
}

BOOL ColliderComponent::IsOverlap(void)
{
	return !this->overlapColliderComponents.empty();
}

BOOL ColliderComponent::IsTrigger()
{
	return m_isTrigger;
}

void ColliderComponent::SetTrigger(BOOL isTrigger)
{
	m_isTrigger = isTrigger;
}
