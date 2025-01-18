#pragma once

#include "Core/Base.h"
#include "Scene/ECSID.h"

#include <unordered_map>

namespace Color
{
	struct Ent
	{
		struct Component
		{
			ECSID TypeID = 0;
			void* Object = nullptr;

			Component() = default;
			Component(const Component&) = default;
			Component& operator=(const Component&) = default;

			Component(Component&& other) noexcept
				: TypeID(other.TypeID), Object(other.Object)
			{
				other.TypeID = 0;
				other.Object = nullptr;
			}

			Component& operator=(Component&& other) noexcept
			{
				delete Object;

				TypeID = other.TypeID;
				Object = other.Object;

				other.TypeID = 0;
				other.Object = nullptr;

				return *this;
			}

			Component(ECSID typeId, void* object)
				: TypeID(typeId), Object(object) {}

			~Component()
			{
				delete Object;
			}
		};
		std::unordered_map<ECSID, Component> Components;
		
		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ECSID TypeID = GetTypeComponentID<T>();
			Component& Comp = Components[TypeID] = { TypeID, new T(std::forward<Args>(args)...) };
			return *((T*) Comp.Object);
		}

		template <typename T>
		void RemoveComponent()
		{
			Components.erase(GetTypeComponentID<T>());
		}

		template <typename T>
		T& GetComponent() const
		{
			return *(T*) Components.at(GetTypeComponentID<T>()).Object;
		}

		template <typename T>
		bool HasComponent() const
		{
			return Components.contains(GetTypeComponentID<T>());
		}
	};
}
