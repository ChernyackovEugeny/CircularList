/* Chernyackov Eugeny chernyackov.eugeny@yandex.ru
stl_circular_list
*/

#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <iterator>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <typename T>
class CircularList {
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;
            Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        };
        Node* sentinel;
        std::size_t size_;

        // initialization of a dummy node (sentinel)
        void init_sentinel() {
            sentinel = new Node(T{}); // sentinel stores a default value T
            sentinel->next = sentinel;
            sentinel->prev = sentinel;
            size_ = 0;
        }

    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = T&;
        using const_reference = const T&;

        // declaring iterators
        class iterator;
        class const_iterator;

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // constructors and destructor
        CircularList() { init_sentinel(); }

        CircularList(std::initializer_list<T> init) {
            init_sentinel();
            for (const T& value : init) {
                push_back(value);
            }
        }

        CircularList(const CircularList& other) {
            init_sentinel();
            for (const auto& value : other) {
                push_back(value);
            }
        }

        CircularList(CircularList&& other) noexcept
            : sentinel(other.sentinel), size_(other.size_) {
            // clearing another list, leaving it empty
            other.sentinel = new Node(T{});
            other.sentinel->next = other.sentinel;
            other.sentinel->prev = other.sentinel;
            other.size_ = 0;
        }

        ~CircularList() {
            clear();
            delete sentinel;
        }

        // assignment operation (copy/move) via the copy-and-swap idiom
        CircularList& operator=(CircularList other) {
            swap(*this, other);
            return *this;
        }

        // exchanging contents
        friend void swap(CircularList& a, CircularList& b) noexcept {
            using std::swap;
            swap(a.sentinel, b.sentinel);
            swap(a.size_, b.size_);
        }

        // access methods
        size_type size() const {
            return size_;
        }
        bool empty() const {
            return size_ == 0;
        }

        reference front() {
            if (empty()) throw std::out_of_range("front() вызван для пустого списка");
            return sentinel->next->data;
        }
        const_reference front() const {
            if (empty()) throw std::out_of_range("front() вызван для пустого списка");
            return sentinel->next->data;
        }

        reference back() {
            if (empty()) throw std::out_of_range("back() вызван для пустого списка");
            return sentinel->prev->data;
        }
        const_reference back() const {
            if (empty()) throw std::out_of_range("back() вызван для пустого списка");
            return sentinel->prev->data;
        }

        // modifiers
        void push_front(const T& value) {
            Node* node = new Node(value);
            node->next = sentinel->next;
            node->prev = sentinel;
            sentinel->next->prev = node;
            sentinel->next = node;
            ++size_;
        }

        void push_back(const T& value) {
            Node* node = new Node(value);
            node->prev = sentinel->prev;
            node->next = sentinel;
            sentinel->prev->next = node;
            sentinel->prev = node;
            ++size_;
        }

        void pop_front() {
            if (empty()) throw std::out_of_range("pop_front() вызван для пустого списка");
            Node* node = sentinel->next;
            sentinel->next = node->next;
            node->next->prev = sentinel;
            delete node;
            --size_;
        }

        void pop_back() {
            if (empty()) throw std::out_of_range("pop_back() вызван для пустого списка");
            Node* node = sentinel->prev;
            sentinel->prev = node->prev;
            node->prev->next = sentinel;
            delete node;
            --size_;
        }
        void clear() {
            Node* curr = sentinel->next;
            while (curr != sentinel) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
            sentinel->next = sentinel;
            sentinel->prev = sentinel;
            size_ = 0;
        }

        // iterators
        iterator begin() {
            return iterator(sentinel->next);
        }
        const_iterator begin() const {
            return const_iterator(sentinel->next);
        }
        iterator end() {
            return iterator(sentinel);
        }
        const_iterator end() const {
            return const_iterator(sentinel);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend() {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        const_iterator cbegin() const {
            return begin();
        }
        const_iterator cend() const {
            return end();
        }
        const_reverse_iterator crbegin() const {
            return rbegin();
        }
        const_reverse_iterator crend() const {
            return rend();
        }

        // comparison operators
        bool operator==(const CircularList& other) const {
            if (size_ != other.size_) return false;
            auto it1 = begin();
            auto it2 = other.begin();
            while (it1 != end() && it2 != other.end()) {
                if (!(*it1 == *it2)) {
                    return false;
                }
                ++it1;
                ++it2;
            }
            return true;
        }
        bool operator!=(const CircularList& other) const {
            return !(*this == other);
        }

        // forward (non-const) iterator class
        class iterator {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;
            private:
                Node* node;
            public:
                iterator(Node* n) : node(n) {}
                T& operator*() const {
                    return node->data;
                }
                T* operator->() const {
                    return &(node->data);
                }

                iterator& operator++() {
                    node = node->next;
                    return *this;
                }
                iterator operator++(int) {
                    iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                iterator& operator--() {
                    node = node->prev;
                    return *this;
                }
                iterator operator--(int) {
                    iterator tmp = *this;
                    --(*this);
                    return tmp;
                }
                bool operator==(const iterator& other) const {
                    return node == other.node;
                }
                bool operator!=(const iterator& other) const {
                    return node != other.node;
                }
        };

        // const iterator class
        class const_iterator {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = const T*;
                using reference         = const T&;
            private:
                const Node* node;
            public:
                const_iterator(const Node* n) : node(n) {}
                const_iterator(const iterator& it) : node(it.node) {}
                const T& operator*() const {
                    return node->data;
                }
                const T* operator->() const {
                    return &(node->data);
                }

                const_iterator& operator++() {
                    node = node->next;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                const_iterator& operator--() {
                    node = node->prev;
                    return *this;
                }
                const_iterator operator--(int) {
                    const_iterator tmp = *this;
                    --(*this);
                    return tmp;
                }
                bool operator==(const const_iterator& other) const {
                    return node == other.node;
                }
                bool operator!=(const const_iterator& other) const {
                    return node != other.node;
                }
        };
};

// static checking of iterators for C++20 concepts
template <typename T>
void check_iterator_concepts() {
    static_assert(std::bidirectional_iterator<typename CircularList<T>::iterator>);
    static_assert(std::bidirectional_iterator<typename CircularList<T>::const_iterator>);
}

static_assert(true);

#endif
