#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <unistd.h>
#include <netdb.h>
#include <format>

std::map<std::string,std::string> parse_query(const std::string& query) {
    std::map<std::string,std::string> result;
    std::istringstream ss(query);
    std::string pair;
    while (std::getline(ss, pair, '&')) {
        size_t eq = pair.find('=');
        if (eq != std::string::npos) {
            result[pair.substr(0, eq)] = pair.substr(eq+1);
        } else {
            result[pair] = "";
        }
    }
    return result;
}

std::string map_to_json(const std::map<std::string,std::string>& m) {
    std::string s = "{";
    for(auto it=m.begin(); it!=m.end(); ++it) {
        if(it!=m.begin()) s += ", ";
        s += "\"" + it->first + "\": \"" + it->second + "\"";
    }
    s += "}";
    return s;
}

int main() {
    std::cout << "Content-Type: text/plain\n\n";

    const char* query_c = getenv("QUERY_STRING");
    std::string query = query_c ? query_c : "";
    std::map<std::string,std::string> parsed_query = parse_query(query);
        
    if (parsed_query.count("name") && parsed_query.count("message")) {
        std::cout << "Set-Cookie: username=" << parsed_query["name"] << "; Path=/;\r\n";
        std::cout << "Set-Cookie: message=" << parsed_query["message"] << "; Path=/;\r\n";
    }

    return 0;
}
