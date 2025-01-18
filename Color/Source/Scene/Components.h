#pragma once

#include "Core/Base.h"
#include "Scene/ECSID.h"

#include <glm/glm.hpp>

#include <string>

namespace Color
{
	struct IDComponent
	{
		ECSID ID = 0;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
		IDComponent& operator=(const IDComponent&) = default;
		IDComponent(ECSID id)
			: ID(id) {}
	};
	
	struct TagComponent
	{
		std::string Tag;
		
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent& operator=(const TagComponent&) = default;
		TagComponent(std::string_view tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Position; // For 2D, only X and Y are used.
		glm::vec3 Rotation; // For 2D, the Z axis is used as the rotation.
		glm::vec3 Scale;    // For 2D, only X and Y are used.

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent& operator=(const TransformComponent&) = default;

		// 3D constructor
		TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
			: Position(position), Rotation(rotation), Scale(scale) {}

		// 2D constructor
		TransformComponent(const glm::vec2& position, float rotation, const glm::vec2& size)
			: Position{position.x, position.y, 0.0f}, Rotation{0.0f, 0.0f, rotation}, Scale{size.x, size.y, 0.0f} {}
	};

	template <typename... Components>
	struct ComponentCluster
	{
	};
	using AllComponents = ComponentCluster
	<
		IDComponent, TagComponent, TransformComponent
	>;

	inline static void GenerateComponentIDs()
	{
		// Never ever alternate the orders of the function calls! You can insert new ones AT THE END ONLY though.
		// If a component gets removed, replace it with a call to GetNextComponentTypeID().
		// This must be done to always keep component IDs backwards compatible with older compilations,
		// since ID generation depends on function call order as specializations of the templated functions get called
		// and they get their static-storage IDs generated. This is the reason that this function is the first ever called
		// function in EntryPoint.h's EngineMain() function. Also there reason why we don't just use AllComponents
		// with some fancy fold expressions is that if we removed a component, the order would change and the compatability
		// would be gone. Doing it manually has to be the case in this scenario.
		// ...................................................
		/* CECSID 00 */ GetTypeComponentID<IDComponent>();
		/* CECSID 01 */ GetTypeComponentID<TagComponent>();
		/* CECSID 02 */ GetTypeComponentID<TransformComponent>();
	}
}
