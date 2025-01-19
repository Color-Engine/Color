#include "EnginePCH.h"
#include "Scene.h"

#include "Scene/Components.h"
#include "Misc/Random.h"

namespace Color
{
	static RandomGenerator s_RNG = RandomGenerator::SeededWithTime();

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Start()
	{
		if (m_Running)
		{
			return;
		}
		m_Running = true;
	}

	void Scene::Update(Timestep ts)
	{
		if (m_Running && !m_Paused)
		{

		}
	}

	void Scene::Stop()
	{
		if (!m_Running)
		{
			return;
		}
		m_Running = false;
	}

	void Scene::SetPaused(bool paused)
	{
	}

	Ref<Scene> Scene::Copy()
	{
		Ref<Scene> scene = MakeRef<Scene>();

		for (auto&& [id, ent] : m_Entities)
		{
			Entity dupe = DuplicateEntityWithID(id);
			dupe.m_Scene = scene.get();
		}

		return scene;
	}

	Entity Scene::CreateEntityWithID(ECSID id, std::string_view name)
	{
		if (HasEntityWithID(id))
		{
			return {};
		}

		Ent& ent = m_Entities[id] = Ent();
		ent.AddComponent<IDComponent>(id);
		ent.AddComponent<TagComponent>(name);
		ent.AddComponent<TransformComponent>();

		return { this, ent };
	}

	Entity Scene::CreateEntity(std::string_view name)
	{
		return CreateEntityWithID(s_RNG.Range<ECSID>(), name);
	}

	template <typename... T>
	static void CopyComponent(Ent& source, Ent& destination)
	{
		([&]()
		{
			if (source.HasComponent<T>())
			{
				destination.AddComponent<T>(source.GetComponent<T>());
			}
		}(), ...);
	}
	
	template <typename... T>
	static void CopyComponent(ComponentCluster<T...>, Ent& source, Ent& destination)
	{
		CopyComponent<T...>(source, destination);
	}

	Entity Scene::DuplicateEntityWithID(ECSID id, ECSID newEntityId)
	{
		if (!HasEntityWithID(id) || HasEntityWithID(newEntityId))
		{
			return {};
		}
		
		Ent& reference = m_Entities[id];
		Ent& duplicate = m_Entities[newEntityId] = Ent();
		
		CopyComponent(AllComponents{}, reference, duplicate);
		duplicate.GetComponent<IDComponent>().ID = newEntityId;

		return { this, duplicate };
	}

	Entity Scene::DuplicateEntityWithID(ECSID id)
	{
		return DuplicateEntityWithID(id, s_RNG.Range<ECSID>());
	}

	Entity Scene::DuplicateEntity(Entity entity, ECSID newEntityId)
	{
		if (!OwnsEntity(entity))
		{
			return {};
		}
		return DuplicateEntityWithID(entity.GetID(), newEntityId);
	}

	Entity Scene::DuplicateEntity(Entity entity)
	{
		return DuplicateEntity(entity, s_RNG.Range<ECSID>());
	}

	bool Scene::DestroyEntityWithID(ECSID id)
	{
		if (!HasEntityWithID(id))
		{
			return false;
		}

		m_Entities.erase(id);
		return true;
	}

	bool Scene::DestroyEntity(Entity entity)
	{
		if (!OwnsEntity(entity))
		{
			return false;
		}
		return DestroyEntityWithID(entity.GetID());
	}

	void Scene::DestroyAllEntities()
	{
		while (m_Entities.size())
		{
			DestroyEntityWithID((*(m_Entities.begin())).first);
		}
	}

	bool Scene::HasEntityWithID(ECSID id) const
	{
		return m_Entities.contains(id);
	}

	bool Scene::HasEntityWithName(std::string_view name) const
	{
		return GetFirstEntityWithName(name) != INVALID_ENTITY_HANDLE;
	}

	Entity Scene::GetFirstEntityWithName(std::string_view name) const
	{
		for (auto&& [id, ent] : m_Entities)
		{
			if (ent.HasComponent<TagComponent>() && ent.GetComponent<TagComponent>().Tag == name)
			{
				return { this, ent };
			}
		}
		return {};
	}

	std::vector<Entity> Scene::GetEntitiesWithName(std::string_view name) const
	{
		std::vector<Entity> entities;
		for (auto&& [id, ent] : m_Entities)
		{
			if (ent.HasComponent<TagComponent>() && ent.GetComponent<TagComponent>().Tag == name)
			{
				entities.push_back({ this, ent });
			}
		}
		return entities;
	}

	bool Scene::OwnsEntity(Entity entity) const
	{
		// Entities without IDComponents are considered non-owned by any scene
		if (!entity.HasComponent<IDComponent>())
		{
			return false;
		}

		return entity.GetScene() == this && m_Entities.contains(entity.GetID());
	}
}
