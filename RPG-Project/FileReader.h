#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

class FileReader
{
public:
	FileReader(std::string filename);
	virtual ~FileReader();
	std::string readAll();
	void close();
	bool isOpen() const;

private:
	std::ifstream file;
};

#endif // !FILEREADER_H

