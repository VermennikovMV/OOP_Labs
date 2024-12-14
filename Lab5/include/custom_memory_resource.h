#pragma once
#include <memory_resource>
#include <list>
#include <cstddef>
#include <stdexcept>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    explicit CustomMemoryResource(std::size_t total_size);
    ~CustomMemoryResource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    struct BlockInfo {
        void* ptr;
        std::size_t size;
        std::size_t alignment;
    };

    void* m_buffer = nullptr;
    std::size_t m_capacity = 0;
    std::size_t m_used = 0;
    std::list<BlockInfo> m_allocated_blocks;
    std::list<BlockInfo> m_free_blocks;
};
