#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

std::string get_post_data() {
    const char* contentLengthStr = getenv("CONTENT_LENGTH");
    if (!contentLengthStr) return "";
    int contentLength = atoi(contentLengthStr);
    if (contentLength <= 0) return "";

    std::string data;
    data.resize(contentLength);
    std::cin.read(&data[0], contentLength);
    return data;
}

int main() {
    std::cout << "Content-Type: text/plain\n\n";

    const char* method = getenv("REQUEST_METHOD");
    const char* query = getenv("QUERY_STRING");
    const char* ip = getenv("REMOTE_ADDR");
    const char* ua = getenv("HTTP_USER_AGENT");
    time_t now = time(nullptr);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));

    std::cout << "Request Method: " << (method ? method : "unknown") << "\n";
    std::cout << "Client IP: " << (ip ? ip : "unknown") << "\n";
    std::cout << "User-Agent: " << (ua ? ua : "unknown") << "\n";
    std::cout << "Timestamp: " << buf << "\n";

    std::string body;
    if (method && (std::string(method) == "POST" || std::string(method) == "PUT")) {
        body = get_post_data();
        std::cout << "Data (body): " << body << "\n";
    } else {
        std::cout << "Data (query string): " << (query ? query : "") << "\n";
    }

    return 0;
}
