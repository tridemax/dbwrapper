#include "platform.h"
#include "SpeechStorage.h"
#include "TemplatesForUtterances.h"


namespace dbwrapper
{
//	const char SpeechStorage::m_dbConnectionParams[] = "hostaddr=192.168.76.200 port=5432 dbname=trainingdb user=postgres password=111 connect_timeout=30 keepalives=1";

	//-------------------------------------------------------------------------------------------------
	SpeechStorage::SpeechStorage(const char* connectionString, bool explainQueries) : m_connectionString(connectionString), m_explainQueries(explainQueries)
	{
	}

	//-------------------------------------------------------------------------------------------------
	SpeechStorage::~SpeechStorage()
	{
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::LoadUtterances(const IdVector& idVector, std::list<Utterance>& utteranceList)
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Explain query plan
		if (m_explainQueries)
		{
			const LoadUtterancesTemplate<ExplainSelectionOfUtterancesColumns> explainQueryPlanTemplate(idVector);

			if (!ExplainQueryPlan(connection, explainQueryPlanTemplate))
			{
				assert(false);
				return false;
			}
		}

		// Compose statement
		const LoadUtterancesTemplate<SelectUtterancesColumns> loadUtterancesTemplate(idVector);

		auto postgresqlStatement = connection.StatementFromTemplate(loadUtterancesTemplate);

		if (!postgresqlStatement)
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Execute statement
		if (!postgresqlStatement.Execute(loadUtterancesTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Results extracting loop
		std::string utteranceAudioFormat, utteranceLanguage;

		const uint32_t resultsCount = postgresqlStatement.GetResultTuplesCount();

		for (uint32_t resultIndex = 0u; resultIndex != resultsCount; ++resultIndex)
		{
			utteranceList.emplace_back(Utterance());

			Utterance& loadedUtterance = utteranceList.back();

			utteranceAudioFormat.clear();
			utteranceLanguage.clear();

			postgresqlStatement.GetResultTuple(resultIndex,
				loadedUtterance.m_utteranceId,
				loadedUtterance.m_content,
				utteranceAudioFormat,
				loadedUtterance.m_timeStart,
				loadedUtterance.m_timeDuration,
				utteranceLanguage,
				loadedUtterance.m_transcribe);

			loadedUtterance.m_audioFormat = AudioFormatStringifier::FromString(utteranceAudioFormat);
			loadedUtterance.m_language = LanguageStringifier::FromString(utteranceLanguage);
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::SelectUtterances(const UtteranceFilter& utteranceFilter, int64_t skip, int64_t limit, std::list<Utterance>& utteranceList)
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Explain query plan
		if (m_explainQueries)
		{
			const SelectUtterancesTemplate<ExplainSelectionOfUtterancesColumns> explainQueryPlanTemplate(utteranceFilter, skip, limit);

			if (!ExplainQueryPlan(connection, explainQueryPlanTemplate))
			{
				assert(false);
				return false;
			}
		}

		// Compose statement
		const SelectUtterancesTemplate<SelectUtterancesColumns> selectUtterancesTemplate(utteranceFilter, skip, limit);

		auto postgresqlStatement = connection.StatementFromTemplate(selectUtterancesTemplate);

		if (!postgresqlStatement)
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Execute statement
		if (!postgresqlStatement.Execute(selectUtterancesTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Results extracting loop
		std::string utteranceAudioFormat, utteranceLanguage;

		const uint32_t resultsCount = postgresqlStatement.GetResultTuplesCount();

		for (uint32_t resultIndex = 0u; resultIndex != resultsCount; ++resultIndex)
		{
			utteranceList.emplace_back(Utterance());

			Utterance& loadedUtterance = utteranceList.back();

			utteranceAudioFormat.clear();
			utteranceLanguage.clear();

			postgresqlStatement.GetResultTuple(resultIndex,
				loadedUtterance.m_utteranceId,
				loadedUtterance.m_content,
				utteranceAudioFormat,
				loadedUtterance.m_timeStart,
				loadedUtterance.m_timeDuration,
				utteranceLanguage,
				loadedUtterance.m_transcribe);

			loadedUtterance.m_audioFormat = AudioFormatStringifier::FromString(utteranceAudioFormat);
			loadedUtterance.m_language = LanguageStringifier::FromString(utteranceLanguage);
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::SelectUtterancesStatistics(const UtteranceFilter& utteranceFilter, uint64_t& filteredUtterancesQuantity, uint64_t& lastUtteranceId)
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Explain query plan
		if (m_explainQueries)
		{
			const SelectUtterancesTemplate<ExplainSelectionOfUtterancesStatistics> explainQueryPlanTemplate(utteranceFilter);

			if (!ExplainQueryPlan(connection, explainQueryPlanTemplate))
			{
				assert(false);
				return false;
			}
		}

		// Compose statement
		const SelectUtterancesTemplate<class SelectUtterancesStatistics> selectUtterancesTemplate(utteranceFilter);

		auto postgresqlStatement = connection.StatementFromTemplate(selectUtterancesTemplate);

		if (!postgresqlStatement)
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Execute statement
		if (!postgresqlStatement.Execute(selectUtterancesTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Extract results
		if (postgresqlStatement.HasResults())
		{
			postgresqlStatement.GetResultTuple(0, filteredUtterancesQuantity, lastUtteranceId);
		}
		else
		{
			filteredUtterancesQuantity = 0u;
			lastUtteranceId = 0u;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::VacuumUtterances()
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate vacuumUtterancesTemplate("vacuum (verbose) utterances; ");

		if (!connection.ExecuteTemplate(vacuumUtterancesTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::VacuumAndAnalyzeUtterances()
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate vacuumUtterancesTemplate("vacuum (verbose, analyze) utterances; ");

		if (!connection.ExecuteTemplate(vacuumUtterancesTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::CreateIndicesForUtterances()
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate timeDurationIndexTemplate("create index if not exists utterances_time_duration_index on utterances (time_duration); ");

		if (!connection.ExecuteTemplate(timeDurationIndexTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate languageIndexTemplate("create index if not exists utterances_language_index on utterances (language); ");

		if (!connection.ExecuteTemplate(languageIndexTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::DeleteIndicesForUtterances()
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate timeDurationIndexTemplate("drop index if exists utterances_time_duration_index; ");

		if (!connection.ExecuteTemplate(timeDurationIndexTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate languageIndexTemplate("drop index if exists utterances_language_index; ");

		if (!connection.ExecuteTemplate(languageIndexTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool SpeechStorage::ReindexIndicesForUtterances()
	{
		// Try to open connection
		auto& connection = Postgres::PostgresClient::Instance().GetConnection(m_connectionString);

		if (!connection.IsOpen())
		{
			m_lastError.assign(connection.LastError());
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate timeDurationIndexTemplate("reindex (verbose) index utterances_time_duration_index; ");

		if (!connection.ExecuteTemplate(timeDurationIndexTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Compose and execute statement
		const Postgres::PostgresTemplate languageIndexTemplate("reindex (verbose) index utterances_language_index; ");

		if (!connection.ExecuteTemplate(languageIndexTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	const std::string& SpeechStorage::LastError() const
	{
		return m_lastError;
	}

	//-------------------------------------------------------------------------------------------------
	template <class TemplateType>
	bool SpeechStorage::ExplainQueryPlan(Postgres::PostgresConnection& connection, const TemplateType& explainingTemplate)
	{
		// Compose statement
		auto postgresqlStatement = connection.StatementFromTemplate(explainingTemplate);

		if (!postgresqlStatement)
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Execute statement
		if (!postgresqlStatement.Execute(explainingTemplate))
		{
			m_lastError.assign(connection.LastError());
			assert(false);
			return false;
		}

		// Results extracting loop
		std::string outputMessage;

		const uint32_t resultsCount = postgresqlStatement.GetResultTuplesCount();

		for (uint32_t resultIndex = 0u; resultIndex != resultsCount; ++resultIndex)
		{
			outputMessage.clear();

			postgresqlStatement.GetResultTuple(resultIndex, outputMessage);

			std::cout << outputMessage << std::endl;
		}

		return true;
	}
}
