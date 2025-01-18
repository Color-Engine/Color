#include "EnginePCH.h"
#include "LinuxMessageDialog.h"

namespace Color
{
	LinuxMessageDialog::LinuxMessageDialog(std::string_view caption, std::string_view content, DialogControls controls, DialogIcon icon)
		: m_Caption(caption), m_Content(content), m_Controls(controls), m_Icon(icon)
	{
	}

	DialogResult LinuxMessageDialog::CreateAndWait() const
	{
		return DialogResult::CreationFailure;
	}

	void LinuxMessageDialog::SetCaption(std::string_view caption)
	{
		m_Caption = caption;
	}

	void LinuxMessageDialog::SetContent(std::string_view content)
	{
		m_Content = content;
	}

	void LinuxMessageDialog::SetControls(DialogControls controls)
	{
		m_Controls = controls;
	}

	void LinuxMessageDialog::SetIcon(DialogIcon icon)
	{
		m_Icon = icon;
	}
}
