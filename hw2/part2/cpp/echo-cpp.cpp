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

std::string get_body() {
    const char* len_str = getenv("CONTENT_LENGTH");
    if (!len_str) return "";
    int len = atoi(len_str);
    if (len <= 0) return "";
    std::string body(len, ' ');
    std::cin.read(&body[0], len);
    return body;
}

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

std::string current_time() {
    time_t t = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return std::string(buf);
}

std::string hostname() {
    char name[256];
    gethostname(name, sizeof(name));
    return std::string(name);
}

int main() {
    std::cout << "Content-Type: text/plain\n\n";

    const char* method_c = getenv("REQUEST_METHOD");
    const char* protocol_c = getenv("SERVER_PROTOCOL");
    const char* query_c = getenv("QUERY_STRING");
    const char* content_type_c = getenv("CONTENT_TYPE");
    const char* ip_c = getenv("REMOTE_ADDR");
    const char* ua_c = getenv("HTTP_USER_AGENT");

    std::string method = method_c ? method_c : "unknown";
    std::string protocol = protocol_c ? protocol_c : "unknown";
    std::string query = query_c ? query_c : "";
    std::string content_type = content_type_c ? content_type_c : "";
    std::string ip = ip_c ? ip_c : "Unknown";
    std::string ua = ua_c ? ua_c : "Unknown";

    std::cout << "Server Protocol: " << protocol << "\n";
    std::cout << "HTTP Method: " << method << "\n";
    std::cout << "Raw Query: " << query << "\n";

    std::map<std::string,std::string> parsed_query = parse_query(query);
    std::cout << "Parsed Query: " << map_to_json(parsed_query) << "\n";

    std::string raw_body;
    if(method=="POST" || method=="PUT" || method=="DELETE") {
        raw_body = get_body();
    }
    std::cout << "Raw Message Body: " << raw_body << "\n";

    std::map<std::string,std::string> parsed_body = parse_query(raw_body);
    std::cout << "Parsed Message Body: " << map_to_json(parsed_body) << "\n";

    std::cout << "Hostname: " << hostname() << "\n";
    std::cout << "Timestamp: " << current_time() << "\n";
    std::cout << "IP Address: " << ip << "\n";
    std::cout << "User-Agent: " << ua << "\n";

    return 0;
}
