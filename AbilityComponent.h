#pragma once
#include "Component.h"

class AbilityComponent : public Component
{
public:
	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Uninit(void) override;
	virtual void BeginPlay(void) override;
	virtual void UpdatePlay(void) override;
	virtual void EndPlay(void) override;

	virtual void TryActivate(void) = 0;
	virtual void Activate(void) = 0;

	enum class STATE
	{
		DISABLE,
		TRY,
		ACTIVE,
	};



protected:




	STATE state;
	int coolTimeCnt;
	int coolTimeCntMax;
	int tryCnt;
	int tryCntMax;
	int activeCnt;
	int activeCntMax;




};

