#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

// URL decoder
std::string url_decode(std::string str) {
    std::string ret;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            if (i + 2 < str.length()) {
                int value;
                sscanf(str.substr(i + 1, 2).c_str(), "%x", &value);
                ret += static_cast<char>(value);
                i += 2;
            }
        } else if (str[i] == '+') {
            ret += ' ';
        } else {
            ret += str[i];
        }
    }
    return ret;
}

// Extract value by key from a string
std::string get_value(const std::string& body, const std::string& key, bool is_json) {
    if (is_json) {
        // Simple JSON search: "key":"value"
        std::string search = "\"" + key + "\":";
        size_t start = body.find(search);
        if (start == std::string::npos) return "";
        
        start += search.length();
        // Skip whitespace and opening quote
        while (start < body.length() && (body[start] == ' ' || body[start] == '\"')) start++;
        
        size_t end = start;
        while (end < body.length() && body[end] != '\"' && body[end] != ',' && body[end] != '}') end++;
        
        return body.substr(start, end - start);
    } else {
        // Simple URL-encoded search: key=value
        std::string search = key + "=";
        size_t start = body.find(search);
        // Handle case where key is at start or preceded by &
        if (start != 0 && (start == std::string::npos || body[start-1] != '&')) {
            // Try finding &key=
            search = "&" + key + "=";
            start = body.find(search);
            if (start != std::string::npos) start += 1; // skip &
        }
        
        if (start == std::string::npos) return "";
        
        start += (key.length() + 1); // skip key=
        size_t end = body.find('&', start);
        if (end == std::string::npos) end = body.length();
        
        return url_decode(body.substr(start, end - start));
    }
}

int main() {
    const char* len_str = getenv("CONTENT_LENGTH");
    int len = len_str ? std::stoi(len_str) : 0;

    std::string body;
    if (len > 0) {
        body.resize(len);
        std::cin.read(&body[0], len);
    }

    const char* type_str = getenv("CONTENT_TYPE");
    std::string content_type = type_str ? type_str : "";
    bool is_json = (content_type.find("application/json") != std::string::npos);

    std::string name = get_value(body, "name", is_json);
    std::string message = get_value(body, "message", is_json);

    std::cout << "Set-Cookie: username=" << name << "; Path=/;\r\n";
    std::cout << "Set-Cookie: message=" << message << "; Path=/;\r\n";
    std::cout << "Content-Type: text/plain\r\n\r\n";

    return 0;
}