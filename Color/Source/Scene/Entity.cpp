#include "EnginePCH.h"
#include "Entity.h"

#include "Scene/Components.h"
#include "Scene/Scene.h"

namespace Color
{
	Entity::Entity(const Scene* scene, const Ent* handle)
		: m_Scene((Scene*) scene), m_Handle((Ent*) handle)
	{
	}

	Entity::Entity(const Scene* scene, const Ent& handle)
		: m_Scene((Scene*) scene), m_Handle(&((Ent&)handle))
	{
	}

	bool Entity::IsValid()
	{
		return m_Scene && m_Scene->OwnsEntity(*this);
	}

	ECSID Entity::GetID() const
	{
		if (HasComponent<IDComponent>())
		{
			return GetComponent<IDComponent>().ID;
		}
		return INVALID_ECS_ID;
	}

	std::string_view Entity::GetName() const
	{
		if (HasComponent<TagComponent>())
		{
			return GetComponent<TagComponent>().Tag;
		}
		return {};
	}
}
