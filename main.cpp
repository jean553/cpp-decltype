#include <iostream>

int value {10};

int& get() {
    return value;
}

auto& getValue() {
    return get();
}

int main() {

    auto& destination = getValue();
    destination += 5;
    std::cout << value << std::endl;

    return EXIT_SUCCESS;
}
