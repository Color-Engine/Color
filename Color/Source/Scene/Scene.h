#pragma once

#include "Scene/Entity.h"

#include <unordered_set>

namespace Color
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		// Creates a copy of the scene.
		Ref<Scene> Copy();

		Entity CreateEntityWithID(ECSID id, std::string_view name = "Unnamed Entity");
		Entity CreateEntity(std::string_view name = "Unnamed Entity");

		Entity DuplicateEntityWithID(ECSID id, ECSID newEntityId);
		Entity DuplicateEntityWithID(ECSID id);
		Entity DuplicateEntity(Entity entity, ECSID newEntityId);
		Entity DuplicateEntity(Entity entity);

		bool DestroyEntityWithID(ECSID id);
		bool DestroyEntity(Entity entity);
		void DestroyAllEntities();

		bool HasEntityWithID(ECSID id) const;
		bool OwnsEntity(Entity entity) const;

		bool HasEntityWithName(std::string_view name) const;
		Entity GetFirstEntityWithName(std::string_view name) const;
		std::vector<Entity> GetEntitiesWithName(std::string_view name) const;

		template <typename T>
		std::vector<Entity> GetAllEntitiesWithComponent() const
		{
			std::vector<Entity> entities;

			for (auto&& [id, ent] : m_Entities)
			{
				if (ent.HasComponent<T>())
				{
					entities.push_back({ this, ent });
				}
			}

			return entities;
		}

		const std::unordered_map<ECSID, Ent>& GetEntities() const { return m_Entities; }
	private:
		std::unordered_map<ECSID, Ent> m_Entities;
	};
}
