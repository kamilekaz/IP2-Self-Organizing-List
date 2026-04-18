#include <iostream>
#include "SelfOrganizingList.h"

int main() {
    std::cout << "--- SelfOrganizingList Demo ---" << std::endl << std::endl;

    Sol::SelfOrganizingList<std::string> list;

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
    Sol::SelfOrganizingList<std::string> list2 = list;
    std::cout << "Original: " << list.toString() << std::endl;
    std::cout << "Copy:     " << list2.toString() << std::endl;

    std::cout << "\n[6] Read operations" << std::endl;
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "Element at index 0: " << list.at(0) << std::endl;
    std::cout << "All elements one by one:" << std::endl;
    for (int i = 0; i < list.size(); i++) {
        std::cout << "Element " << i << ": " << list.at(i) << std::endl;
    }

    std::cout << "\n[7] Comparison operators" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "list == list2: " << (list == list2) << std::endl;
    std::cout << "list != list2: " << (list != list2) << std::endl;
    std::cout << "list <  list2: " << (list < list2) << std::endl;
    std::cout << "list <= list2: " << (list <= list2) << std::endl;
    std::cout << "list >  list2: " << (list > list2) << std::endl;
    std::cout << "list >= list2: " << (list >= list2) << std::endl;

    std::cout << "\n[8] Duplicate element exception" << std::endl;
    try {
        list += "Smells Like Teen Spirit";
    } catch (const Sol::DuplicateElementException& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    std::cout << "\n[9] Clearing the list" << std::endl;
    !list;
    std::cout << "After clear: " << list.toString() << std::endl;

    std::cout << "\n--- Demo finished ---" << std::endl;
    return 0;
}
