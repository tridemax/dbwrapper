#pragma once

//#include "Miscellaneous.h"
//#include "SpeechStorage.h"


namespace dbwrapper
{
	//-------------------------------------------------------------------------------------------------
	/// EcgCommandHandler
	//-------------------------------------------------------------------------------------------------
	class EcgCommandHandler : public boost::noncopyable
	{
	private:
//		SpeechStorage				m_speechStorage;

	public:
		bool LoadConfiguration(const boost::filesystem::path& configPath);
		bool HandleCommand(const std::string& command);

	private:
		bool SaveWaveform(const boost::filesystem::path& filePath, const boost::filesystem::path& imagePath);
		bool ParseMit(const boost::filesystem::path& filePath);
	};
}
