#include <fstream>
#include <iostream>
#include <string>

int	replaceFile(const std::string& filename, const std::string& s1,
	const std::string& s2)
{
	if (s1.empty() || filename.empty()) {
        std::cerr << "Error: filename and s1 cannot be empty." << std::endl;
        return (1);
    }

	std::ifstream inFile(filename.c_str());
	if (!inFile)
	{
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return (1);
	}

	std::string	outFilename = filename + ".replace";
	std::ofstream outFile(outFilename.c_str());
	if (!outFile)
	{
		std::cerr << "Error: Could not create output file." << std::endl;
		return (1);
	}

	std::string line;
	while (std::getline(inFile, line))
	{
		size_t pos = 0;
		while ((pos = line.find(s1, pos)) != std::string::npos)
		{
    		line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
    		pos += s2.length();
		}
		outFile << line << std::endl;
	}

	std::cout << "File processed successfully. Output: "
		<< filename << ".replace" << std::endl;
	
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Error: <filename> <s1> <s2> is required." << std::endl;
		return (1);
	}
	
	std::string	filename = argv[1];
	std::string	s1 = argv[2];
	std::string	s2 = argv[3];

	return (replaceFile(filename, s1, s2));
}
