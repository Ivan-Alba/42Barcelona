#include "BitcoinExchange.hpp"
#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>

BitcoinExchange::BitcoinExchange()
{
	initDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		db = other.db;
	}
	return (*this);
}

void	BitcoinExchange::initDatabase()
{

	std::ifstream file("data.csv");
	if (!file.is_open())
	{
		throw std::runtime_error("Error: could not open file \"data.csv\".");
	}
	
	std::string	line;
	if (std::getline(file, line) != "date,exchange_rate")
	{
		throw std::runtime_error(
			"Error: data file header not correct. Must be \"date,exchange_rate\"");
	}

	while (std::getline(file, line))
	{
		loadData(line);
	}


	db["2011-01-03"] = 1.2f;
	db["2011-01-09"] = 0.2f;
	db["2011-01-11"] = 3;
	db["2011-02-23"] = 0.8f;
	db["2012-01-01"] = 500;
	db["2020-08-02"] = 2.2f;
	db["2024-07-16"] = 3.1f;
	db["2020-01-01"] = 0.25f;
	db["2001-12-31"] = 1.1f;
}

void	BitcoinExchange::loadData(const std::string &line)
{
	size_t		pos;
	std::string	date;
	std::string	value;
	float		exchangeRate;

	pos = line.find(",");
	if (pos != std::string::npos && pos + 2 <= line.size())
	{
		date = line.substr(0, pos);
		if (isDateValid(date))
		{
			value = line.substr(pos + 1);
			if (strToFloat(value, exchangeRate))
			{
				std::pair<std::map<std::string,float>::iterator, bool> res;
				
				res = db.insert(std::make_pair(date, exchangeRate));
				if (!res.second)

			}
		}
	}
}

bool	BitcoinExchange::strToInt(const std::string &s, int &out) const
{
	std::stringstream ss(s);
	ss >> out;

	return (!ss.fail() && ss.eof());
}

bool	BitcoinExchange::strToFloat(const std::string &value, float &out) const
{
	std::stringstream ss(value);
	ss >> out;

	return (!ss.fail() && ss.eof());
}

bool	BitcoinExchange::isDateValid(const std::string &date) const
{
	int	year;
	int	month;
	int	day;

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	for (size_t i = 0; i < date.size(); i++)
	{
		if (i != 4 && i != 7)
		{
			if (!std::isdigit(date[i]))
				return (false);
		}
	}

	strToInt(date.substr(0, 4), year);
	strToInt(date.substr(5, 2), month);
	strToInt(date.substr(8, 2), day);

	if (year < 0 || month < 1 || month > 12 || day < 1)
		return (false);

	bool leapYear = false;
	if  ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		leapYear = true;

	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day > 31)
				return (false);
			break;
		case 2:
			if (day > 29)
				return (false);
			else if (day > 28 && !leapYear)
				return (false);
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (day > 30)
				return (false);
			break;
	}

	return (true);
}

float	BitcoinExchange::isValueValid(const std::string &value_str,
			const std::string &line, float &out) const
{
	float	value;

	if (!strToFloat(value_str, value))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}

	if (value < 0.0f)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	else if (value > 1000.0f)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}

	out = value;
	
	return (true);
}

void	BitcoinExchange::getValue(const std::string &line) const
{
	size_t		pos;
	std::string	date;
	std::string	value;
	float 		val;

	pos = line.find("|");
	if (pos == std::string::npos || line[pos - 1] != ' '
		|| line[pos + 1] != ' ' || pos + 2 > line.size())
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	
	date = line.substr(0, pos - 1);
	if (!isDateValid(date))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	
	value = line.substr(pos + 2);
	if (!isValueValid(value, line, val))
		return ;

	std::map<std::string, float>::const_iterator it = db.find(date);
	if (it == db.end())
	{
		it = db.lower_bound(date);
		if (it == db.begin())
		{
			std::cerr << "Error: date not found" << std::endl;
			return ;
		}
		else
			--it;
	}

	std::cout << date << " => " << value << " = " << val * it->second
		<< std::endl;
}

bool	BitcoinExchange::isInputHeaderCorrect(std::string &line) const
{
	if (line != "date | value")
		return (false);

	return (true);
}
