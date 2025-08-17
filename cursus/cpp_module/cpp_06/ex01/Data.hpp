#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class	Data
{
	public:
		Data();
		Data(const std::string &msg);
		Data(const Data &other);
		~Data();

		Data& operator=(const Data &other);

		const std::string& getMsg();

	private:
		const std::string msg;
};

#endif

