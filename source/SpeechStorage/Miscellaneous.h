#pragma once


namespace DbWrapper
{
	//-------------------------------------------------------------------------------------------------
	/// IdVector
	//-------------------------------------------------------------------------------------------------
	typedef std::vector<uint64_t> IdVector;

	//-------------------------------------------------------------------------------------------------
	/// AudioFormatStringifier
	//-------------------------------------------------------------------------------------------------
	class AudioFormatStringifier
	{
	public:
		static const char			AudioWave[];
		static const char			AudioFlac[];
		static const char			AudioOpus[];
		static const char			AudioVorbis[];
		static const char			AudioMp3[];
		static const char			AudioAac[];

	public:
		static inline AudioFormat FromString(const std::string& audioFormat);
		static inline const char* ToString(AudioFormat audioFormat);
	};

	//-------------------------------------------------------------------------------------------------
	selectany const char AudioFormatStringifier::AudioWave[] = "wave";
	selectany const char AudioFormatStringifier::AudioFlac[] = "flac";
	selectany const char AudioFormatStringifier::AudioOpus[] = "opus";
	selectany const char AudioFormatStringifier::AudioVorbis[] = "vorbis";
	selectany const char AudioFormatStringifier::AudioMp3[] = "mp3";
	selectany const char AudioFormatStringifier::AudioAac[] = "aac";

	//-------------------------------------------------------------------------------------------------
	inline AudioFormat AudioFormatStringifier::FromString(const std::string& audioFormat)
	{
		if (EnumCompare(audioFormat, AudioWave))
		{
			return AudioFormat::AudioWave;
		}
		if (EnumCompare(audioFormat, AudioFlac))
		{
			return AudioFormat::AudioFlac;
		}
		if (EnumCompare(audioFormat, AudioOpus))
		{
			return AudioFormat::AudioOpus;
		}
		if (EnumCompare(audioFormat, AudioVorbis))
		{
			return AudioFormat::AudioVorbis;
		}
		if (EnumCompare(audioFormat, AudioMp3))
		{
			return AudioFormat::AudioMp3;
		}
		if (EnumCompare(audioFormat, AudioAac))
		{
			return AudioFormat::AudioAac;
		}
		return AudioFormat::AudioUnknown;
	}

	//-------------------------------------------------------------------------------------------------
	inline const char* AudioFormatStringifier::ToString(AudioFormat audioFormat)
	{
		switch (audioFormat)
		{
		case AudioFormat::AudioWave:
			return AudioWave;

		case AudioFormat::AudioFlac:
			return AudioFlac;

		case AudioFormat::AudioOpus:
			return AudioOpus;

		case AudioFormat::AudioVorbis:
			return AudioVorbis;

		case AudioFormat::AudioMp3:
			return AudioMp3;

		case AudioFormat::AudioAac:
			return AudioAac;
		}
		return "";
	}

	//-------------------------------------------------------------------------------------------------
	/// Language
	//-------------------------------------------------------------------------------------------------
	enum class Language : uint32_t
	{
		Unknown = 0u,
		enUS,
		deDE,
		frFR,
		esES,
		itIT,
		arSA,
		heIL,
		plPL,
		ruRU,
		ukUA,
		trTR
	};

	//-------------------------------------------------------------------------------------------------
	/// LanguageStringifier
	//-------------------------------------------------------------------------------------------------
	class LanguageStringifier
	{
	public:
		static const char			enUS[];
		static const char			deDE[];
		static const char			frFR[];
		static const char			esES[];
		static const char			itIT[];
		static const char			arSA[];
		static const char			heIL[];
		static const char			plPL[];
		static const char			ruRU[];
		static const char			ukUA[];
		static const char			trTR[];

	public:
		static inline Language FromString(const std::string& language);
		static inline const char* ToString(Language language);
	};

	//-------------------------------------------------------------------------------------------------
	selectany const char LanguageStringifier::enUS[] = "en-US";
	selectany const char LanguageStringifier::deDE[] = "de-DE";
	selectany const char LanguageStringifier::frFR[] = "fr-FR";
	selectany const char LanguageStringifier::esES[] = "es-ES";
	selectany const char LanguageStringifier::itIT[] = "it-IT";
	selectany const char LanguageStringifier::arSA[] = "ar-SA";
	selectany const char LanguageStringifier::heIL[] = "he-IL";
	selectany const char LanguageStringifier::plPL[] = "pl-PL";
	selectany const char LanguageStringifier::ruRU[] = "ru-RU";
	selectany const char LanguageStringifier::ukUA[] = "uk-UA";
	selectany const char LanguageStringifier::trTR[] = "tr-TR";

	//-------------------------------------------------------------------------------------------------
	inline Language LanguageStringifier::FromString(const std::string& language)
	{
		if (EnumCompare(language, enUS))
		{
			return Language::enUS;
		}
		if (EnumCompare(language, deDE))
		{
			return Language::deDE;
		}
		return Language::Unknown;
	}

	//-------------------------------------------------------------------------------------------------
	inline const char* LanguageStringifier::ToString(Language language)
	{
		switch (language)
		{
		case Language::enUS:
			return enUS;

		case Language::deDE:
			return deDE;

		case Language::frFR:
			return frFR;

		case Language::esES:
			return esES;

		case Language::itIT:
			return itIT;

		case Language::arSA:
			return arSA;

		case Language::heIL:
			return heIL;

		case Language::plPL:
			return plPL;

		case Language::ruRU:
			return ruRU;

		case Language::ukUA:
			return ukUA;

		case Language::trTR:
			return trTR;
		}
		return "";
	}

	//-------------------------------------------------------------------------------------------------
	/// UtteranceFilter
	//-------------------------------------------------------------------------------------------------
	class UtteranceFilter
	{
	public:
		uint32_t					m_durationMin;
		uint32_t					m_durationMax;
		std::vector<Language>		m_languageList;
		bool						m_mustHaveTranscribes;

	public:
		inline UtteranceFilter() : m_durationMin(0u), m_durationMax(0u), m_mustHaveTranscribes(false)
		{
		}
	};

	//-------------------------------------------------------------------------------------------------
	/// Utterance
	//-------------------------------------------------------------------------------------------------
	class Utterance
	{
	public:
		uint64_t					m_utteranceId;
		std::vector<byte>			m_content;
		AudioFormat					m_audioFormat;
		uint32_t					m_timeStart;
		uint32_t					m_timeDuration;
		Language					m_language;
		std::string					m_transcribe;
	};
}
