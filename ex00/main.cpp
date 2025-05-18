#include "BitcoinExchange.hpp"
#include "btc.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		if (argc > 2)
			std::cerr << "Error: too many arguments." << std::endl;
		else
			std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}

	BitcoinExchange btc = BitcoinExchange("data.csv");
	try
	{
		btc.constructDB();
	}
	catch (BitcoinExchange::CantReadFile &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}


	// Opening file
	std::string line;
	std::ifstream inputfile(argv[1]);

	if (!inputfile.is_open())
	{
		std::cerr << "Error: could not open file (" << argv[1] << ")" << std::endl;
		return (1);
	}

	// Reading line by line
	int ctr = -1;
	while (getline(inputfile,line))
	{
		ctr++;
		if (ctr == 0)
			continue;

		bool ignore = false;

		// Spliting on |
		char *ptr;
		ptr = std::strtok((char *)line.c_str(), " | ");
		std::string date;
		std::string value;
		while (ptr != NULL)
		{
			if (date.empty())
				date = ptr;
			else if (value.empty())
				value = ptr;
			else
				ignore = true;
			ptr = strtok (NULL, " | ");
		}

		// Checking date format
		if (!checkDAteFormat(date) && !ignore)
		{
			std::cerr << "Error: Incorrect date format (" << date << ")" << std::endl;
			ignore = true;
		}
		// Checking value format
		if (!checkValue(value) && !ignore)
		{
			std::cerr << "Error: Incorrect value format (" << value << ")" << std::endl;
			ignore = true;
		}

		if (!ignore && stringToFloat(value) > 1000)
		{
			std::cerr << "Error: Too large a number (" << value << ")" << std::endl;
			ignore = true;
		}

		if (!ignore) {
			float result = stringToFloat(value) * btc.getRate(date);
			std::cout << date << " => " << value << " = " << result << std::endl;
		}

	}
	inputfile.close();
}