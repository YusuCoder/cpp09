#include "BitcoinExchange.hpp"
#include "btc.hpp"
#include <string.h>


BitcoinExchange::BitcoinExchange() : _db_path("data.csv") {
   // Default constructor
}

BitcoinExchange::BitcoinExchange(const std::string& db_path) : _db_path(db_path) {
    // Constructor with database path
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db_path(other._db_path), _db(other._db) {
    // Copy constructor
}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange& other) {
    this->_db_path = other._db_path;

    std::map<std::string, float>::iterator it;
    for (it = this->_db.begin(); it != this->_db.end(); ++it) {
        this->_db[it->first] = it->second;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
    // Destructor
}

void BitcoinExchange::constructDB() {
    // Open the database file
    std::string line;
    std::ifstream db_file(this->_db_path.c_str());

    if (!db_file.is_open()) {
        throw BitcoinExchange::CantReadFile();
    }

    this->_db.clear();
    // Read the file line by line
    int i = -1;
    while (getline(db_file, line)) {
        i++;
        if (i == 0) {
            continue;
        }
        bool ign = false;

        //Split the line into date and value
        char *p;
        p = strtok((char *)line.c_str(), ",");
        std::string date;
        std::string value;
        while (p != NULL) {
            if (date.empty())
                date = p;
            else if (value.empty())
                value = p;
            else
                ign = true;
            p = strtok(NULL, ",");
        }

        if (!checkValue(value) && !ign) {
            std::cerr << "Error: bad input => " << date << " => " << value << std::endl;
            ign = true;
        }

        if (!checkDAteFormat(date) && !ign) {
            std::cerr << "Error: bad input => " << date << " => " << value << std::endl;
            ign = true;
        }

        if (!ign) {
            this->_db[date] = stringToFloat(value);
        }   
    }
    db_file.close();
    return;
}

float BitcoinExchange::getRate(const std::string date) {
    if (this->_db.size() == 0) {
        return 0;
    }

    if (this->_db.find(date) == this->_db.end()) {
        std::map<std::string, float>::iterator it;
        std::string close_date;

        for (it = this->_db.begin(); it != this->_db.end(); ++it) {
            int comp = date.compare(it->first);

            if (comp == -1) {
                if (it != this->_db.begin()) {
                    it--;
                } 
                close_date = it->first;
                break;
            }
        }
        if (close_date.empty()) {
            it--;
            close_date = it->first;
        }

        return this->_db[close_date];
    }
    return this->_db[date];
}

const char* BitcoinExchange::CantReadFile::what() const throw() {
    return "Error: could not open file";
}
