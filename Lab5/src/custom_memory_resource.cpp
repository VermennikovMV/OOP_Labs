#include "custom_memory_resource.h"
#include <new>
#include <utility>

CustomMemoryResource::CustomMemoryResource(std::size_t total_size) {
    m_buffer = ::operator new(total_size);
    m_capacity = total_size;
    m_used = 0;
}

CustomMemoryResource::~CustomMemoryResource() {
    ::operator delete(m_buffer);
}

void* CustomMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    for (auto it = m_free_blocks.begin(); it != m_free_blocks.end(); ++it) {
        if (it->size >= bytes && it->alignment == alignment) {
            void* ptr = it->ptr;
            m_allocated_blocks.push_back({ptr, bytes, alignment});
            m_free_blocks.erase(it);
            return ptr;
        }
    }

    std::size_t space = m_capacity - m_used;
    void* current_ptr = static_cast<char*>(m_buffer) + m_used;
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(current_ptr);
    std::size_t adjustment = 0;
    if (alignment > 0 && (addr % alignment) != 0) {
        adjustment = alignment - (addr % alignment);
    }
    if (bytes + adjustment <= space) {
        m_used += (bytes + adjustment);
        void* aligned_ptr = static_cast<char*>(current_ptr) + adjustment;
        m_allocated_blocks.push_back({aligned_ptr, bytes, alignment});
        return aligned_ptr;
    }
    throw std::bad_alloc();
}

void CustomMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    for (auto it = m_allocated_blocks.begin(); it != m_allocated_blocks.end(); ++it) {
        if (it->ptr == p && it->size == bytes && it->alignment == alignment) {
            m_free_blocks.push_back(*it);
            m_allocated_blocks.erase(it);
            return;
        }
    }
    throw std::runtime_error("Invalid deallocate");
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
