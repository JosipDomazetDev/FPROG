#include <string>
#include <functional>
#include <iostream>
#include <experimental/optional>

std::experimental::optional<std::string> create(bool b) {
    if (b) {
        return "Godzilla";
    } else {
        return std::experimental::nullopt;
    }
}


auto create2(bool b) {
    if (b) {
        return std::experimental::optional<std::string>("Godzilla");
    } else {
        return std::experimental::optional<std::string>();
    }
}


//int main() {
//    std::cout << "create(false) returned "
//              << create(false).value_or("empty") << '\n';
//    return 0;
//}

//int main() {
//    if (auto str = create2(true)) {
//        std::cout << "create2(true) returned " << *str << '\n';
//    }
//    return 0;
//}
//
//int main() {
//    std::cout << "create(false) returned "
//              << create(false).value_or("needed") << '\n';
//    return 0;
//}
//
int main() {
    if (auto str = create2(true)) {
        std::cout << "create2(true) returned! " << *str << '\n';
    }
    return 0;
}
//
//int main() {
//    std::cout << "create(true) returned "
//              << create(true).value_or("empty") << '\n';
//    return 0;
//}
