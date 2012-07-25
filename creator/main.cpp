#include "creator.hpp"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Absence d'argument."<<std::endl;
		return 1;
	}
	boost::filesystem::path path(argv[1]);

	try
	{
		Creator creat;
		creat.load(path);

		creat.loop();
		creat.free();
	}
	catch(gcn::Exception e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	catch(std::string str)
	{
		std::cout << "Erreur interne : " << str << std::endl;
	}
	catch(std::exception e)
	{
		std::cout << "Erreur de la bibliothèque standart ou de boost : " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Erreur inconnue." << std::endl;
	}

	return 0;
}

