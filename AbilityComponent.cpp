#include "AbilityComponent.h"

void AbilityComponent::Init(void)
{
	Component::Init();
	SetName("Ability");
}

void AbilityComponent::Update(void)
{
	Component::Update();

}

void AbilityComponent::Uninit(void)
{
	Component::Uninit();

}

void AbilityComponent::BeginPlay(void)
{
	Component::BeginPlay();

}


void AbilityComponent::UpdatePlay(void)
{
	Component::UpdatePlay();

	switch (this->state)
	{
	case STATE::DISABLE:

		break;

	case STATE::TRY:
		tryCnt -= 1;
		if (tryCnt<=0)
		{
			if (coolTimeCnt<=0)
			{

				this->Activate();
				this->state = STATE::ACTIVE;
			}
			else
			{

				//ŽÀsŽ¸”s
				this->state = STATE::DISABLE;

			}


		}
		break;

	case STATE::ACTIVE:

		this->activeCnt -= 1;
		if (activeCnt<=0)
		{
			this->state = STATE::DISABLE;
		}
		break;

	default:

		break;
	}

	coolTimeCnt -= 1;
	if (coolTimeCnt<0)
	{
		coolTimeCnt = 0;
	}
}

void AbilityComponent::EndPlay(void)
{
	Component::EndPlay();

}
