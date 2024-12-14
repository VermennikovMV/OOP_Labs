#pragma once
#include <memory_resource>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <new>
#include <type_traits>

// Шаблонный класс лучше полностью оставлять в заголовочном файле.
template <typename T>
class Stack {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(pointer ptr) : m_ptr(ptr) {}
        iterator(const iterator& other) : m_ptr(other.m_ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        iterator& operator++() { ++m_ptr; return *this; }
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

        iterator& operator--() { --m_ptr; return *this; }
        iterator operator--(int) { iterator tmp(*this); --(*this); return tmp; }

        iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        iterator operator+(difference_type n) const { return iterator(m_ptr + n); }

        iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
        iterator operator-(difference_type n) const { return iterator(m_ptr - n); }

        difference_type operator-(const iterator& other) const { return m_ptr - other.m_ptr; }

        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return m_ptr != other.m_ptr; }
        bool operator<(const iterator& other) const { return m_ptr < other.m_ptr; }
        bool operator>(const iterator& other) const { return m_ptr > other.m_ptr; }
        bool operator<=(const iterator& other) const { return m_ptr <= other.m_ptr; }
        bool operator>=(const iterator& other) const { return m_ptr >= other.m_ptr; }

    private:
        pointer m_ptr;
    };

    Stack(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
        : m_alloc(mr), m_data(nullptr), m_size(0), m_capacity(0) {}

    Stack(std::size_t capacity, const allocator_type& alloc)
        : m_alloc(alloc), m_data(nullptr), m_size(0), m_capacity(0) {
        reserve(capacity);
    }

    ~Stack() {
        clear();
        deallocate();
    }

    void push(const T& value) {
        ensure_capacity(m_size + 1);
        std::allocator_traits<allocator_type>::construct(m_alloc, m_data + m_size, value);
        ++m_size;
    }

    void push(T&& value) {
        ensure_capacity(m_size + 1);
        std::allocator_traits<allocator_type>::construct(m_alloc, m_data + m_size, std::move(value));
        ++m_size;
    }

    template <class... Args>
    void emplace(Args&&... args) {
        ensure_capacity(m_size + 1);
        std::allocator_traits<allocator_type>::construct(m_alloc, m_data + m_size, std::forward<Args>(args)...);
        ++m_size;
    }

    void pop() {
        if (m_size == 0) throw std::runtime_error("Empty");
        std::allocator_traits<allocator_type>::destroy(m_alloc, m_data + m_size - 1);
        --m_size;
    }

    T& top() {
        if (m_size == 0) throw std::runtime_error("Empty");
        return m_data[m_size - 1];
    }

    const T& top() const {
        if (m_size == 0) throw std::runtime_error("Empty");
        return m_data[m_size - 1];
    }

    std::size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void clear() {
        for (std::size_t i = 0; i < m_size; ++i) {
            std::allocator_traits<allocator_type>::destroy(m_alloc, m_data + i);
        }
        m_size = 0;
    }

    iterator begin() { return iterator(m_data); }
    iterator end() { return iterator(m_data + m_size); }

    std::size_t get_size() const {
        return m_size;
    }

    bool operator==(const Stack& other) const {
        if (m_size != other.m_size) return false;
        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_data[i] != other.m_data[i]) return false;
        }
        return true;
    }

private:
    void ensure_capacity(std::size_t new_size) {
        if (new_size > m_capacity) {
            std::size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
            if (new_cap < new_size) new_cap = new_size;
            reallocate(new_cap);
        }
    }

    void reallocate(std::size_t new_cap) {
        T* new_data = m_alloc.allocate(new_cap);
        for (std::size_t i = 0; i < m_size; ++i) {
            std::allocator_traits<allocator_type>::construct(m_alloc, new_data + i, std::move(m_data[i]));
            std::allocator_traits<allocator_type>::destroy(m_alloc, m_data + i);
        }
        deallocate();
        m_data = new_data;
        m_capacity = new_cap;
    }

    void deallocate() {
        if (m_data) {
            m_alloc.deallocate(m_data, m_capacity);
            m_data = nullptr;
            m_capacity = 0;
        }
    }

    void reserve(std::size_t new_cap) {
        if (new_cap <= m_capacity) return;
        reallocate(new_cap);
    }

    allocator_type m_alloc;
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
};
