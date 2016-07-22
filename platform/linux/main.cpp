#include "platform.h"
#include "../../source/EcgStorage/EcgCommandHandler.h"


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

	// Run terminal dialog
	std::unique_ptr<dbwrapper::EcgCommandHandler> ecgCommandHandler(new dbwrapper::EcgCommandHandler());

	while (true)
	{
		std::string command;
		std::cin >> command;

		boost::trim(command);

		if (ecgCommandHandler && ecgCommandHandler->HandleCommand(command))
		{
			continue;
		}

		if (boost::istarts_with(command, "exit") || boost::istarts_with(command, "q"))
		{
			break;
		}
	}

	return 0;
}
