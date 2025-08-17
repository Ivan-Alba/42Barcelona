#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int	main()
{
	Data *newData;
	Data *returnedData;
	uintptr_t raw;

	newData = new Data("This is a secret message");


	raw = Serializer::serialize(newData);

	returnedData = Serializer::deserialize(raw);

	std::cout << "Original Data msg: " << newData->getMsg() << "\n"
		<< "Deserialized Data msg: " << returnedData->getMsg() << std::endl;

	delete (newData);

	return (0);
}
