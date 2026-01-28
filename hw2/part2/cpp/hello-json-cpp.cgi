#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    std::cout << "Content-Type: application/json\n\n";

    const char* ip = getenv("REMOTE_ADDR");
    time_t now = time(nullptr);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));

    std::cout << "{\n";
    std::cout << "  \"greeting\": \"Hello from HAJ135\",\n";
    std::cout << "  \"message\": \"Hello from HAJ135\",\n";
    std::cout << "  \"language\": \"C++ CGI\",\n";
    std::cout << "  \"datetime\": \"" << buf << "\",\n";
    std::cout << "  \"ip\": \"" << (ip ? ip : "unknown") << "\"\n";
    std::cout << "}\n";

    return 0;
}
