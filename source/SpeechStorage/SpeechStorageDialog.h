#pragma once

//#include "Miscellaneous.h"
#include "SpeechStorage.h"


namespace dbwrapper
{
	//-------------------------------------------------------------------------------------------------
	/// SpeechStorageDialog
	//-------------------------------------------------------------------------------------------------
	class SpeechStorageDialog : public boost::noncopyable
	{
	private:
		SpeechStorage				m_speechStorage;

	public:
		SpeechStorageDialog();
		~SpeechStorageDialog();
	};
}
