#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iomanip>


// 1. URL Encoder (Fixes the space issue in cookies)
std::string url_encode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        std::string::value_type c = (*i);

        // Keep alphanumeric and safe characters
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Encode spaces and special chars to %XX
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}

// 2. URL Decoder (For reading input)
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

// 3. Simple JSON Parser
std::string get_json_value(const std::string& body, const std::string& key) {
    std::string search = "\"" + key + "\":";
    size_t start = body.find(search);
    if (start == std::string::npos) return "";
    
    start += search.length();
    while (start < body.length() && (body[start] == ' ' || body[start] == '"')) {
        start++;
    }
    size_t end = start;
    while (end < body.length() && body[end] != '"' && body[end] != ',' && body[end] != '}') {
        end++;
    }
    return body.substr(start, end - start);
}

// 4. Form Data Parser
std::string get_form_value(const std::string& body, const std::string& key) {
    std::stringstream ss(body);
    std::string pair;
    while (std::getline(ss, pair, '&')) {
        size_t eq = pair.find('=');
        if (eq != std::string::npos) {
            std::string k = pair.substr(0, eq);
            if (k == key) {
                return url_decode(pair.substr(eq + 1));
            }
        }
    }
    return "";
}

// --- MAIN ---

int main() {
    // 1. Read Input
    const char* len_str = getenv("CONTENT_LENGTH");
    int len = 0;
    if (len_str) len = std::atoi(len_str);

    std::string body;
    if (len > 0) {
        body.resize(len);
        std::cin.read(&body[0], len);
    }

    // 2. Parse Data
    const char* type_str = getenv("CONTENT_TYPE");
    std::string content_type = type_str ? type_str : "";
    std::string name, message;
    
    if (content_type.find("application/json") != std::string::npos) {
        name = get_json_value(body, "name");
        message = get_json_value(body, "message");
    } else {
        name = get_form_value(body, "name");
        message = get_form_value(body, "message");
    }

    // 3. Output Headers
    // APPLY url_encode() HERE
    std::cout << "Set-Cookie: username=" << url_encode(name) << "; Path=/;\r\n";
    std::cout << "Set-Cookie: message=" << url_encode(message) << "; Path=/;\r\n";
    std::cout << "Content-Type: text/plain\r\n\r\n";

    // 4. Output Body
    std::cout << "Cookies set for: " << name;

    return 0;
}