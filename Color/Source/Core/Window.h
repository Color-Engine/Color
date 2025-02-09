#pragma once

#include "Event/Signal.h"
#include "Event/Event.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCode.h"

namespace Color
{
	struct WindowSpec
	{
		std::string Title;
		int Width, Height;
		bool Fullscreen, Resizable, VSync;

		WindowSpec
		(
			std::string_view title = "Color Engine",
			int width = 1600,
			int height = 900,
			bool fullscreen = false,
			bool resizable = true,
			bool vSync = true
		)
			: Title(title), Width(width), Height(height), Fullscreen(fullscreen), Resizable(resizable), VSync(vSync) {}
	};

	class Window
	{
	public:
		Signal<> SigClose;
		Signal<int, int> SigResize;
		Signal<> SigFocus;
		Signal<> SigLoseFocus;
		Signal<int, int> SigMove;
		Signal<KeyCode, bool> SigKeyPress;
		Signal<KeyCode> SigKeyType;
		Signal<KeyCode> SigKeyRelease;
		Signal<float, float> SigMouseMove;
		Signal<float, float> SigMouseScroll;
		Signal<MouseCode> SigMouseButtonPress;
		Signal<MouseCode> SigMouseButtonRelease;
		typedef std::function<void(Event&)> EventCallbackFn;
	public:
		virtual ~Window() = default;

		virtual bool Create() = 0;
		virtual void Update() = 0;
		virtual bool Destroy() = 0;

		virtual void RequestAttention() = 0;
		virtual void Maximize() = 0;
		virtual void Focus() = 0;

		virtual void SetTitle(std::string_view title) = 0;
		virtual void SetSize(int width, int height) = 0;
		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual void SetVSync(bool vSync) = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual bool HasFocus() const = 0;
		virtual bool IsIconified() const = 0;
		virtual bool IsMaximized() const = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual bool IsFullscreen() const = 0;
		virtual bool IsResizable() const = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Ref<Window> New(const WindowSpec& spec = {});
	};
}
