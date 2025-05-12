#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
#include <utility>

class BitcoinExchange {
    private:
        std::string _db_path;
        std::map<std::string, float> _db;
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string& db_path);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void constructDB();
        std::string dbPath() const;
        float getRate(const std::string date);

        class CantReadFile : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

#endif