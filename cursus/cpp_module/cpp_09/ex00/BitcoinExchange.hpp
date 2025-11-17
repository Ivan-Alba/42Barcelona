#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, float> db;
		
		bool	strToInt(const std::string &s, int &out) const;
		bool	strToFloat(const std::string &value, float &out) const;
		
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		BitcoinExchange& operator=(const BitcoinExchange &other);

		void	initDatabase();
		bool	isInputHeaderCorrect(std::string &line) const;
		void	getValue(const std::string &line) const;
		bool	isDateValid(const std::string &date) const;
		float	isValueValid(const std::string &value_str,
					const std::string &line, float &out) const;
};

#endif
