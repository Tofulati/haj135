#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    std::cout << "Content-Type: text/html\n\n";

    const char* ip = getenv("REMOTE_ADDR");
    time_t now = time(nullptr);
    char buf[100];
    strftime(buf, sizeof(buf), "%m-%d-%Y %H:%M:%S", localtime(&now));

    std::cout << "<!DOCTYPE html><html><head><title>Hello C++</title></head></html><body>";
    std::cout << "<h1>Hello from HAJ135</h1>";
    std::cout << "<p>Welcome to the HTML C++ page - Albert, Hajin, Joey</p>";
    std::cout << "<p>Language: C++ CGI</p>";
    std::cout << "<p>Generated at: " << buf << "</p>";
    std::cout << "<p>Your IP address: " << (ip ? ip : "unknown") << "</p>";
    std::cout << "</body></html>";

    return 0;
}