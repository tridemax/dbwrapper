#pragma once

#include "Miscellaneous.h"


namespace DbWrapper
{
	//-------------------------------------------------------------------------------------------------
	/// SpeechStorage
	//-------------------------------------------------------------------------------------------------
	class SpeechStorage : public boost::noncopyable
	{
	private:
		const char*					m_connectionString;
		const bool					m_explainQueries;
		std::string					m_lastError;

	public:
		SpeechStorage(const char* connectionString, bool explainQueries);
		~SpeechStorage();

		bool LoadUtterances(const IdVector& idVector, std::list<Utterance>& utteranceList);
		bool SelectUtterances(const UtteranceFilter& utteranceFilter, int64_t skip, int64_t limit, std::list<Utterance>& utteranceList);
		bool SelectUtterancesStatistics(const UtteranceFilter& utteranceFilter, uint64_t& filteredUtterancesQuantity, uint64_t& greatestUtteranceId);
		bool VacuumUtterances();
		bool VacuumAndAnalyzeUtterances();
		bool CreateIndicesForUtterances();
		bool DeleteIndicesForUtterances();
		bool ReindexIndicesForUtterances();
		const std::string& LastError() const;

	private:
		template <class TemplateType>
		bool ExplainQueryPlan(Postgres::PostgresConnection& connection, const TemplateType& explainQueryPlanTemplate);
	};
}
