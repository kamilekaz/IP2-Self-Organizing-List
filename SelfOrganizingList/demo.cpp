#include <iostream>
#include "SelfOrganizingList.h"

int main() {
    std::cout << "--- SelfOrganizingList Demo ---" << std::endl << std::endl;

    sol::SelfOrganizingList<std::string> list;

    std::cout << "[1] Adding songs" << std::endl;
    list += "Smells Like Teen Spirit";
    list += "Gangnam Style";
    list += "Blinding Lights";
    std::cout << "Current list: " << list.toString() << std::endl;

    std::cout << "\n[2] Searching song and applying Move-to-Front" << std::endl;
    std::cout << "Searching for 'Smells Like Teen Spirit'..." << std::endl;
    int pos = list["Smells Like Teen Spirit"];
    std::cout << "Found at position: " << pos << std::endl;
    std::cout << "List after search: " << list.toString() << std::endl;

    std::cout << "\n[3] Updating song" << std::endl;
    list *= {"Gangnam Style", "Gangnam Style (Remix)"};
    std::cout << "After update: " << list.toString() << std::endl;

    std::cout << "\n[4] Removing song" << std::endl;
    list -= "Blinding Lights";
    std::cout << "After remove: " << list.toString() << std::endl;

    std::cout << "\n[5] Copy constructor" << std::endl;
    sol::SelfOrganizingList<std::string> list2 = list;
    std::cout << "Original: " << list.toString() << std::endl;
    std::cout << "Copy:     " << list2.toString() << std::endl;

    std::cout << "\n[6] Comparison operators" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "list == list2: " << (list == list2) << std::endl;
    std::cout << "list != list2: " << (list != list2) << std::endl;
    std::cout << "list <  list2: " << (list < list2) << std::endl;
    std::cout << "list <= list2: " << (list <= list2) << std::endl;
    std::cout << "list >  list2: " << (list > list2) << std::endl;
    std::cout << "list >= list2: " << (list >= list2) << std::endl;

    std::cout << "\n[7] Duplicate element exception" << std::endl;
    try {
        list += "Smells Like Teen Spirit";
    } catch (const sol::DuplicateElementException& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    std::cout << "\n[8] Clearing the list" << std::endl;
    !list;
    std::cout << "After clear: " << list.toString() << std::endl;

    std::cout << "\n--- Demo finished ---" << std::endl;
    return 0;
}