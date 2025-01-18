#pragma once

#include "Core/Base.h"

#include <string_view>
#include <string>

namespace Color
{
	enum class DialogControls : long
	{
		None              = 0x00000000L,
		AbortRetryIgnore  = 0x00000002L,
		CancelTryContinue = 0x00000006L,
		Help              = 0x00004000L,
		Ok                = 0x00000000L,
		OkCancel          = 0x00000001L,
		RetryCancel       = 0x00000005L,
		YesNo             = 0x00000004L,
		YesNoCancel       = 0x00000003L
	};

	enum class DialogIcon : long
	{
		None        = 0x00000000L,
		Question    = 0x00000020L,
		Information = 0x00000040L,
		Warning     = 0x00000030L,
		Error       = 0x00000010L
	};

	enum DialogResult : int
	{
		CreationFailure = -1,

		None     =  0,
		Ok       = 1,
		Cancel   = 2,
		Abort    = 3,
		Retry    = 4,
		Ignore   = 5,
		Yes      = 6,
		No       = 7,
		TryAgain = 10,
		Continue = 11
	};

	class MessageDialog
	{
	public:
		virtual ~MessageDialog() = default;

		virtual DialogResult CreateAndWait() const = 0;

		virtual void SetCaption(std::string_view caption) = 0;
		virtual void SetContent(std::string_view content) = 0;
		virtual void SetControls(DialogControls controls) = 0;
		virtual void SetIcon(DialogIcon icon) = 0;

		virtual const std::string& GetCaption() const = 0;
		virtual const std::string& GetContent() const = 0;
		virtual DialogControls GetControls() const = 0;
		virtual DialogIcon GetIcon() const = 0;

		static Scope<MessageDialog> New(std::string_view caption, std::string_view content, DialogControls controls = DialogControls::Ok, DialogIcon icon = DialogIcon::None);
	};
}
