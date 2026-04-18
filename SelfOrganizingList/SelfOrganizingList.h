#ifndef SELFORGANIZINGLIST_H
#define SELFORGANIZINGLIST_H

#include <string>
#include <utility>
#include <stdexcept>

namespace Sol {

    // custom exception for duplicate insert attempts
    class DuplicateElementException : public std::invalid_argument {
    public:
        explicit DuplicateElementException(const std::string& msg);
    };

    template <typename T>
    class SelfOrganizingList {
    private:
        struct Impl;
        Impl* pImpl;

    public:
        // creates an empty list
        SelfOrganizingList();

        // frees all allocated memory
        ~SelfOrganizingList();

        // copy constructor
        SelfOrganizingList(const SelfOrganizingList& other);

        // assignment operator
        SelfOrganizingList& operator=(const SelfOrganizingList& other);

        // adds element to the front
        // throws if element already exists
        SelfOrganizingList& operator+=(const T& value);

        // removes element from the list
        SelfOrganizingList& operator-=(const T& value);

        // finds element and moves it to the front
        // returns its previous position
        int operator[](const T& value);

        // clears the whole list
        SelfOrganizingList& operator!();

        // replaces one element with another
        // pair.first = old value, pair.second = new value
        SelfOrganizingList& operator*=(const std::pair<T,T>& values);

        // returns number of elements
        int size() const;

        // returns element at given position
        const T& at(int index) const;

        // comparison operators
        bool operator==(const SelfOrganizingList& other) const;
        bool operator!=(const SelfOrganizingList& other) const;
        bool operator<(const SelfOrganizingList& other) const;
        bool operator<=(const SelfOrganizingList& other) const;
        bool operator>(const SelfOrganizingList& other) const;
        bool operator>=(const SelfOrganizingList& other) const;

        // returns list as string (with size and elements)
        std::string toString() const;
    };

}

#endif
