#include "Component.h"
#include "GameObject.h"

void Component::SetOwner(GameObject* owner)
{
	this->ownerGameObject = owner;
}

GameObject* Component::GetOwner(void)
{
	return this->ownerGameObject;
}

void Component::Init(void)
{
}

void Component::Update(void)
{
}

void Component::Uninit(void)
{
}

void Component::BeginPlay(void)
{
}

void Component::UpdatePlay(void)
{
}

void Component::EndPlay(void)
{
}

void Component::SetName(string name)
{
	if (name.empty())
	{
		name = "Component";
	}
	int max = 0;
	for (Component* component : GetOwner()->GetAllComponents() )
	{
		if (dynamic_cast<Object*>(component) == this) continue;

		string objName = component->GetName();

		if (objName.compare(0, name.length(), name) != 0) continue;

		if (objName == name)
		{
			max++;
			continue;
		}
		string temp = objName.substr(name.length(), objName.length() - name.length());
		if (temp.find_first_not_of("0123456789") != std::string::npos) continue;

		int num = stoi(temp);
		if (num >= max)
		{
			max = num + 1;
		}
	}

	if (max == 0)
	{
		Object::SetName(name);
	}
	else
	{
		Object::SetName(name + to_string(max));
	}
}
