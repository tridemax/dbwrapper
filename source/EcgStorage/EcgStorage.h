#pragma once

//#include "Miscellaneous.h"


namespace dbwrapper
{
	//-------------------------------------------------------------------------------------------------
	/// EcgStorage
	//-------------------------------------------------------------------------------------------------
	class EcgStorage : public boost::noncopyable
	{
	private:
		const char*					m_connectionString;
		const bool					m_explainQueries;
		std::string					m_lastError;

	public:
		EcgStorage(const char* connectionString, bool explainQueries);
		~EcgStorage();

		const std::string& LastError() const;
	};
}
