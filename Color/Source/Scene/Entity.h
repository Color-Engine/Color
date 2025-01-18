#pragma once

#include "Core/Assert.h"
#include "Scene/ECS.h"

namespace Color
{
	class Scene;

	// A wrapper around an Ent residing in a Scene.
	class Entity
	{
		friend class Scene;
	public:
		Entity() = default;
		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;
		Entity(const Scene* scene, const Ent* handle);
		Entity(const Scene* scene, const Ent& handle);

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			CL_CORE_ASSERT(!HasComponent<T>(), "Component already exists!");
			return m_Handle->AddComponent<T>(std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			// Will overwrite the existing component, the difference between AddComponent and this is that this obviously doesn't assert.
			return m_Handle->AddComponent<T>(std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		T& GetOrAddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				return GetComponent<T>();
			}
			else
			{
				return AddComponent<T>(std::forward<Args>(args)...);
			}
		}

		template <typename T>
		void RemoveComponent()
		{
			CL_CORE_ASSERT(HasComponent<T>(), "Component doesn't exist!");
			m_Handle->RemoveComponent<T>();
		}

		template <typename T>
		T& GetComponent() const
		{
			CL_CORE_ASSERT(HasComponent<T>(), "Component doesn't exist!");
			return m_Handle->GetComponent<T>();
		}

		template <typename T>
		bool HasComponent() const
		{
			return m_Handle->HasComponent<T>();
		}

		// Will crash if the owning Scene is deleted. Otherwise will validate if this entity reference is valid.
		bool IsValid();

		ECSID GetID() const;
		std::string_view GetName() const;

		Scene* GetScene() const { return m_Scene; }
		Ent* GetHandle() const { return m_Handle; }

		explicit operator bool() { return IsValid(); }
		explicit operator ECSID() { return GetID(); }
		explicit operator Ent() { return *m_Handle; }

		bool operator==(const Entity&) const = default;
		bool operator!=(const Entity&) const = default;
	private:
		Scene* m_Scene = nullptr;
		Ent*   m_Handle = nullptr;
	};

	inline Entity INVALID_ENTITY_HANDLE = { nullptr, nullptr };
}

template <typename OStream>
inline OStream& operator<<(OStream& stream, const Color::Entity& e)
{
	return stream << "Entity(" << e.GetID() << ", " << e.GetName() << ')';
}
