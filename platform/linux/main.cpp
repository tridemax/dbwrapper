#include "platform.h"
#include "../../source/SpeechStorage/SpeechStorageDialog.h"


//-------------------------------------------------------------------------------------------------
/// main
//-------------------------------------------------------------------------------------------------
int main(int argc, const char** argv)
{
	// Build path to configuration file
	boost::filesystem::path configPath;

	for (int32_t argumentIndex = 1; argumentIndex < argc; ++argumentIndex)
	{
		if (boost::starts_with(argv[argumentIndex], "--config"))
		{
			if (argumentIndex + 1 != argc)
			{
				configPath = argv[++argumentIndex];
			}
		}
	}

	if (configPath.empty())
	{
		configPath = argv[0];
		configPath.remove_filename();
		configPath /= "dbwrapper.conf";
	}

	// Run the autobuild
	/*
	DbWrapper::SpeechStorage speechStorage;

	int32_t exitCode = 0;

	if (!autoBuilder.Run(configPath.c_str()))
	{
		std::cerr << autoBuilder.LastError() << std::endl;
		exitCode = 1;
	}
*/
	return 0;
}
