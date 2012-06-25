#include <iostream>
#include <boost/filesystem/path.hpp>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Absence d'argument."<<std::endl;
		return 1;
	}

	boost::filesystem::path path(argv[1]);
	std::cout<<path.string()<<std::endl;

	return 0;
}

