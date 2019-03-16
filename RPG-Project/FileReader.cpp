#include "pch.h"
#include "FileReader.h"


FileReader::FileReader(std::string filename)
{
	file.open(filename);
}

FileReader::~FileReader()
{
	if (file.is_open())
		file.close();
}

void FileReader::close()
{
	file.close();
}

bool FileReader::isOpen() const
{
	return file.is_open();
}

std::string FileReader::readAll()
{
	std::stringstream str;

	std::string line;
	while (std::getline(file, line))
		str << line << std::endl;
	file.close();
	return str.str();
}