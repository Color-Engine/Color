#pragma once

#include "Core/Window.h"

namespace Color
{
	enum class InputState
	{
		None = -1,

		Released = 0,
		Pressed  = 1,
		Repeated = 2,
	};

	class NativeInput
	{
	public:
		virtual ~NativeInput() = default;

		virtual InputState GetKeyState(KeyCode keycode) const = 0;
		virtual InputState GetMouseButtonState(MouseCode button) const = 0;
		virtual glm::vec2 GetMousePosition() const = 0;

		virtual bool IsKeyPressed(KeyCode keycode) const { return GetKeyState(keycode) == InputState::Pressed; }
		virtual bool IsKeyRepeated(KeyCode keycode) const { return GetKeyState(keycode) == InputState::Repeated; }
		virtual bool IsKeyDown(KeyCode keycode) const
		{
			InputState state = GetKeyState(keycode);
			return state == InputState::Pressed || state == InputState::Repeated;
		}
		virtual bool IsKeyUp(KeyCode keycode) const { return GetKeyState(keycode) == InputState::Released; }

		virtual bool IsMouseButtonDown(MouseCode button) const { return GetKeyState(button) == InputState::Pressed; }
		virtual bool IsMouseButtonUp(MouseCode button) const { return GetKeyState(button) == InputState::Released; }

		virtual float GetMouseX() const { return GetMousePosition().x; }
		virtual float GetMouseY() const { return GetMousePosition().y; }

		static Scope<NativeInput> New(const Ref<Window>& window);
	};

	/** Static Input class for Application's main window instance. */
	class Input
	{
	public:
		static InputState GetKeyState(KeyCode keycode)
		{
			return s_Instance->GetKeyState(keycode);
		}

		static InputState GetMouseButtonState(MouseCode button)
		{
			return s_Instance->GetMouseButtonState(button);
		}
		
		static glm::vec2 GetMousePosition()
		{
			return s_Instance->GetMousePosition();
		}

		static bool IsKeyPressed(KeyCode keycode)
		{
			return s_Instance->IsKeyPressed(keycode);
		}

		static bool IsKeyRepeated(KeyCode keycode)
		{
			return s_Instance->IsKeyRepeated(keycode);
		}

		static bool IsKeyDown(KeyCode keycode)
		{
			return s_Instance->IsKeyDown(keycode);
		}

		static bool IsKeyUp(KeyCode keycode)
		{
			return s_Instance->IsKeyUp(keycode);
		}

		static bool IsMouseButtonDown(MouseCode button)
		{
			return s_Instance->IsMouseButtonDown(button);
		}

		static bool IsMouseButtonUp(MouseCode button)
		{
			return s_Instance->IsMouseButtonUp(button);
		}

		static float GetMouseX()
		{
			return s_Instance->GetMouseX();
		}

		static float GetMouseY()
		{
			return s_Instance->GetMouseY();
		}
	private:
		static void Init(const Ref<Window>& window);
	private:
		static Scope<NativeInput> s_Instance;
		friend class Application;
	};
}
