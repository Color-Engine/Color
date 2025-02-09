#pragma once

#include "Core/Window.h"

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Color
{
	class DesktopWindow : public Window
	{
	public:
		DesktopWindow(const WindowSpec& spec = {});
		virtual ~DesktopWindow() override;

		virtual bool Create() override;
		virtual void Update() override;
		virtual bool Destroy() override;

		virtual void RequestAttention() override;
		virtual void Maximize() override;
		virtual void Focus() override;

		virtual void SetTitle(std::string_view title) override;
		virtual void SetSize(int width, int height) override;
		virtual void SetWidth(int width) override;
		virtual void SetHeight(int height) override;
		virtual void SetVSync(bool vSync) override;
		virtual void SetEventCallback(const EventCallbackFn& callback) override;

		virtual bool HasFocus() const override;
		virtual bool IsIconified() const override;
		virtual bool IsMaximized() const override;

		virtual const std::string& GetTitle() const override { return m_Data.Title; }
		virtual int GetWidth() const override { return m_Data.Width; }
		virtual int GetHeight() const override { return m_Data.Height; }
		virtual bool IsFullscreen() const override { return m_Data.Fullscreen; }
		virtual bool IsResizable() const override { return m_Data.Resizable; }
		virtual bool IsVSync() const override { return m_Data.VSync; }
		virtual void* GetNativeWindow() const override { return m_Handle; }
	private:
		GLFWwindow* m_Handle = nullptr;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			int Width, Height;
			bool Fullscreen, Resizable, VSync;
			EventCallbackFn EventCallback;

			void Callback(Event& e)
			{
				if (EventCallback)
				{
					EventCallback(e);
				}
			}

			Signal<>& SigClose;
			Signal<int, int>& SigResize;
			Signal<>& SigFocus;
			Signal<>& SigLoseFocus;
			Signal<int, int>& SigMove;
			Signal<KeyCode, bool>& SigKeyPress;
			Signal<KeyCode>& SigKeyType;
			Signal<KeyCode>& SigKeyRelease;
			Signal<float, float>& SigMouseMove;
			Signal<float, float>& SigMouseScroll;
			Signal<MouseCode>& SigMouseButtonPress;
			Signal<MouseCode>& SigMouseButtonRelease;
		} m_Data;
	};
}
