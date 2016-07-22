#include "platform.h"
#include "EcgCommandHandler.h"


namespace dbwrapper
{
	//-------------------------------------------------------------------------------------------------
	bool EcgCommandHandler::LoadConfiguration(const boost::filesystem::path& configPath)
	{
		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool EcgCommandHandler::HandleCommand(const std::string& command)
	{
		// Handle 'scanecg' command
		if (boost::istarts_with(command, "scanecg"))
		{
			boost::filesystem::recursive_directory_iterator currentItem("./", boost::filesystem::symlink_option::none), endItem;

			while (currentItem != endItem)
			{
				if (currentItem->status().type() == boost::filesystem::file_type::regular_file) // skip all except regular files
				{
					if (boost::iequals(currentItem->path().extension().string(), ".rf")) // skip all except '.rf' files
					{
						std::cout << "found ECG file: " << currentItem->path() <<  std::endl;

						boost::filesystem::path imagePath = currentItem->path();

						imagePath.replace_extension(".jpeg");

//						SaveWaveform(currentItem->path(), imagePath);
					}
				}
				++currentItem;
			}

			return true;
		}

		return false;
	}

	//-------------------------------------------------------------------------------------------------
	bool EcgCommandHandler::SaveWaveform(const boost::filesystem::path& filePath, const boost::filesystem::path& imagePath)
	{
		////
		QImage image(2048, 1536, QImage::Format_ARGB32);

		image.fill(0xFFFFFFFF);

		////
		struct stat st;
		lstat(filePath.c_str(), &st);
		const size_t inputSize = st.st_size;

		const size_t samplesCount = inputSize / 4;
		const size_t samplesPerPixel = 2048 / samplesCount;

		std::unique_ptr<uint8_t[]> samplesBuffer(new uint8_t[samplesPerPixel]);
		size_t samplesBufferFillness = 0u;
		size_t currentPixel = 0u;

		////
		FILE* inputFile = fopen(filePath.c_str(), "r");

		if (inputFile)
		{
			uint8_t buffer[4096];

			while (true)
			{
				auto readBytes = fread(buffer, 4096, 1, inputFile);

				if (readBytes == 0)
				{
					break;
				}

				auto readSamples = readBytes / 4;


			}

			fclose(inputFile);
		}

		////
		image.save(imagePath.c_str(), "jpeg");

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool EcgCommandHandler::ParseMit(const boost::filesystem::path& filePath)
	{
		WFDB_Anninfo an[1];
		an[0].name = "mit";
		an[0].stat = WFDB_AHA_READ;

		char path[1024] = "AAMYTDK69A";
		const auto annopenResult = annopen(path, an, 1);

		WFDB_Annotation annot;

		int yyy = 0;

		while (getann(0, &annot) == 0)
		{
			yyy++;
		}

		wfdbquit();

		return true;
	}
}
