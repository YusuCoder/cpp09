#include <string>
#include <cstring>
#include <sstream>

bool checkDAteFormat(std::string date) {
    std::string temp_lengthh = date;
    char *p;
    p = strtok((char *)temp_lengthh.c_str(), "-");
    int i = 0;
    while (p != NULL) {
        if (i == 0 && strlen(p) != 4) {
            return false;
        }
        else if (i > 0 && strlen(p) != 2) {
            return false;
        }
        p = strtok(NULL, "-");
        i++;
    }

    if (i != 3) {
        return false;
    }
    struct tm result;
    if (strptime(date.c_str(), "%Y-%m-%d", &result) == NULL) {
        return false;
    }

    return true;
}

bool checkValue(std::string value) {
    std::stringstream ss(value);
    float f;

    if (!(ss >> f) || !ss.eof()) {
        return false;
    }
    if (f < 0) {
        return false;
    }
    
    return true;
}

float stringToFloat(std::string str) {
    std::stringstream ss(str);
    float f;

    if (!(ss >> f) || !ss.eof()) {
        return -1;
    }

    return f;
}

    