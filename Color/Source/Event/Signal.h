#pragma once

#include "Core/Assert.h"

#include <functional>
#include <vector>

namespace Color
{
	template <typename Ret, typename... Params>
	size_t GetStdFunctionAddress(std::function<Ret(Params...)> function)
	{
		typedef Ret(FunctionType)(Params...);
		FunctionType** functionPtr = function.template target<FunctionType*>();
		return (size_t) *functionPtr;
	}

	template <typename... Params>
	class Signal
	{
	public:
		using BindingType = std::function<void(Params...)>;
	public:
		Signal() = default;
		Signal(const Signal&) = default;
		Signal& operator=(const Signal&) = default;
		Signal(std::initializer_list<BindingType> bindings)
			: m_Bindings(bindings) {}

		size_t Bind(const BindingType& binding)
		{
			m_Bindings.push_back(binding);
			return m_Bindings.size() - 1;
		}

		bool Unbind(const BindingType& binding)
		{
			for (size_t i = 0; i < m_Bindings.size(); i++)
			{
				if (GetStdFunctionAddress(m_Bindings[i]) == GetStdFunctionAddress(binding))
				{
					m_Bindings.erase(m_Bindings.begin() + i);
					return true;
				}
			}

			return false;
		}

		void Broadcast(Params... params) const
		{
			for (const BindingType& binding : m_Bindings)
			{
				binding(params...);
			}
		}

		void operator()(Params... params) const
		{
			Broadcast(params...);
		}

		const std::vector<BindingType>& GetBindings() const { return m_Bindings; }
	private:
		std::vector<BindingType> m_Bindings;
	};
}
