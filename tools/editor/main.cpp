#include "editor.hpp"

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cerr<<"Absence d'argument."<<std::endl;
		return 1;
	}
	boost::filesystem::path path(argv[1]);
	std::string id(argv[2]);

	try
	{
		Editor edit;
		edit.load(path, id);

		edit.loop();
		edit.free();
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

