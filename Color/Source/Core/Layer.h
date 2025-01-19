#pragma once

#include "Core/Base.h"
#include "Misc/Timestep.h"

#include <string_view>
#include <string>

namespace Color
{
	class Layer
	{
	public:
		Layer(std::string_view name);
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnDetach() {}

		const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
