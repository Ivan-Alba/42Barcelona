#include "Data.hpp"

Data::Data() : msg("Default Message") {}

Data::Data(const std::string &msg) : msg(msg) {}

Data::Data(const Data &other)
{
	*this = other;
}

Data::~Data() {}

Data& Data::operator=(const Data &other)
{
	if (this != &other)
	{
	}
	return (*this);
}

const std::string& Data::getMsg()
{
	return (msg);
}
