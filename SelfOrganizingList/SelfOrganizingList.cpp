#include "SelfOrganizingList.h"
#include <stdexcept>
#include <sstream>

namespace sol {

    template <typename T>
    struct SelfOrganizingList<T>::Impl {

        struct Node {
            T data;
            Node* next;
            Node(const T& data) : data(data), next(nullptr) {}
        };

        Node* head = nullptr;
        int size = 0;

        // removes all nodes from the list
        void clear() {
            Node* curr = head;
            while (curr != nullptr) {
                Node* nxt = curr->next;
                delete curr;
                curr = nxt;
            }
            head = nullptr;
            size = 0;
        }

        // deep copy from another list
        void copyFrom(const Impl& other) {
            Node* curr = other.head;
            Node* tail = nullptr;

            while (curr != nullptr) {
                Node* newNode = new Node(curr->data);

                if (tail == nullptr) {
                    head = newNode;
                } else {
                    tail->next = newNode;
                }

                tail = newNode;
                curr = curr->next;
            }

            size = other.size;
        }
    };

    template <typename T>
    SelfOrganizingList<T>::SelfOrganizingList() {
        pImpl = new Impl();
    }

    template <typename T>
    SelfOrganizingList<T>::~SelfOrganizingList() {
        pImpl->clear();
        delete pImpl;
    }

    template <typename T>
    SelfOrganizingList<T>::SelfOrganizingList(const SelfOrganizingList& other) {
        pImpl = new Impl();
        pImpl->copyFrom(*other.pImpl);
    }

    template <typename T>
    SelfOrganizingList<T>& SelfOrganizingList<T>::operator=(const SelfOrganizingList& other) {
        if (this != &other) {
            pImpl->clear();
            pImpl->copyFrom(*other.pImpl);
        }
        return *this;
    }

    template <typename T>
    SelfOrganizingList<T>& SelfOrganizingList<T>::operator+=(const T& value) {
        typename Impl::Node* curr = pImpl->head;

        while (curr != nullptr) {
            if (curr->data == value) {
                throw DuplicateElementException("Element already exists");
            }
            curr = curr->next;
        }

        typename Impl::Node* newNode = new typename Impl::Node(value);
        newNode->next = pImpl->head;
        pImpl->head = newNode;
        pImpl->size++;
        return *this;
    }

    template <typename T>
    SelfOrganizingList<T>& SelfOrganizingList<T>::operator-=(const T& value) {
        typename Impl::Node* prv = nullptr;
        typename Impl::Node* curr = pImpl->head;

        while (curr != nullptr) {
            if (curr->data == value) {
                if (prv == nullptr) {
                    pImpl->head = curr->next;
                } else {
                    prv->next = curr->next;
                }

                delete curr;
                pImpl->size--;
                return *this;
            }

            prv = curr;
            curr = curr->next;
        }

        throw std::invalid_argument("Element not found");
    }

    template <typename T>
    int SelfOrganizingList<T>::operator[](const T& value) {
        typename Impl::Node* prv = nullptr;
        typename Impl::Node* curr = pImpl->head;
        int pos = 0;

        while (curr != nullptr) {
            if (curr->data == value) {
                if (prv != nullptr) {
                    prv->next = curr->next;
                    curr->next = pImpl->head;
                    pImpl->head = curr;
                }
                return pos;
            }

            prv = curr;
            curr = curr->next;
            pos++;
        }

        throw std::invalid_argument("Element not found");
    }

    template <typename T>
    SelfOrganizingList<T>& SelfOrganizingList<T>::operator!() {
        pImpl->clear();
        return *this;
    }

    template <typename T>
    SelfOrganizingList<T>& SelfOrganizingList<T>::operator*=(const std::pair<T,T>& values) {
        typename Impl::Node* curr = pImpl->head;

        while (curr != nullptr) {
            if (curr->data == values.first) {
                curr->data = values.second;
                return *this;
            }
            curr = curr->next;
        }

        throw std::invalid_argument("Element not found");
    }

    // comparison operators (based on list size)
    template <typename T>
    bool SelfOrganizingList<T>::operator==(const SelfOrganizingList& other) const {
        return pImpl->size == other.pImpl->size;
    }

    template <typename T>
    bool SelfOrganizingList<T>::operator<(const SelfOrganizingList& other) const {
        return pImpl->size < other.pImpl->size;
    }

    template <typename T>
    bool SelfOrganizingList<T>::operator!=(const SelfOrganizingList& other) const {
        return *this < other || other < *this;
    }

    template <typename T>
    bool SelfOrganizingList<T>::operator<=(const SelfOrganizingList& other) const {
        return *this < other || *this == other;
    }

    template <typename T>
    bool SelfOrganizingList<T>::operator>(const SelfOrganizingList& other) const {
        return other < *this;
    }

    template <typename T>
    bool SelfOrganizingList<T>::operator>=(const SelfOrganizingList& other) const {
        return other < *this || *this == other;
    }

    template <typename T>
    std::string SelfOrganizingList<T>::toString() const {
        std::stringstream ss;
        ss << "SelfOrganizingList [size=" << pImpl->size << "]: ";

        typename Impl::Node* curr = pImpl->head;
        while (curr != nullptr) {
            ss << curr->data;
            if (curr->next != nullptr) ss << " -> ";
            curr = curr->next;
        }

        return ss.str();
    }

    template class SelfOrganizingList<std::string>;
    template class SelfOrganizingList<int>;
    template class SelfOrganizingList<double>;
    template class SelfOrganizingList<char>;

}