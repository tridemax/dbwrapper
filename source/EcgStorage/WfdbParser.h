#pragma once

//#include "Miscellaneous.h"


namespace dbwrapper
{
	//-------------------------------------------------------------------------------------------------
	/// WfdbParser
	//-------------------------------------------------------------------------------------------------
	class WfdbParser : public boost::noncopyable
	{
	private:
//		std::string					m_lastError;

	public:
		WfdbParser();
		~WfdbParser();

		bool LoadFile(const char* filePath);
	};
}
