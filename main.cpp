#include <iostream>

int value {10};

int& get(int data) {
    return value;
}

float get(float data) {
    return 1000.f;
}

auto getValue(float param) {
    return get(param);
}

int main() {

    auto destination = getValue(100.f);
    destination += 5;
    std::cout << value << std::endl;

    return EXIT_SUCCESS;
}
