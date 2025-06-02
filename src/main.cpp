/* Chernyackov Eugeny chernyackov.eugeny@yandex.ru
stl_circular_list
*/

#include <iostream>
#include "circular_list.hpp"

int main() {
    CircularList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    std::cout << "List elements (forward): ";
    for (const auto& val : list) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    std::cout << "List elements (reverse): ";
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Front: " << list.front() << std::endl;
    std::cout << "Back: " << list.back() << std::endl;

    CircularList<int> copy = list;
    std::cout << "Copy equal to original? " << (copy == list ? "yes" : "no") << std::endl;

    list.clear();
    std::cout << "List empty after clear? " << (list.empty() ? "yes" : "no") << std::endl;

    return 0;
}
