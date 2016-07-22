#include "platform.h"
#include "EcgStorage.h"


namespace dbwrapper
{
	//-------------------------------------------------------------------------------------------------
	EcgStorage::EcgStorage(const char* connectionString, bool explainQueries) : m_connectionString(connectionString), m_explainQueries(explainQueries)
	{
	}

	//-------------------------------------------------------------------------------------------------
	EcgStorage::~EcgStorage()
	{
	}

	//-------------------------------------------------------------------------------------------------
	const std::string& EcgStorage::LastError() const
	{
		return m_lastError;
	}
}
