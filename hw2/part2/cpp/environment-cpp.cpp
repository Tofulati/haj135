#include <iostream>
#include <cstdlib>

extern char **environ;

int main() {
    std::cout << "Content-Type: text/plain\n\n";

    for (char **env = environ; *env != nullptr; ++env) {
        std::cout << *env << "\n";
    }

    return 0;
}
