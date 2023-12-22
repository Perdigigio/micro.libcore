#include <libcore/lib/memory.hh>

namespace micro::core::lib
{
	struct alignas(32) base_block { std::byte __storage[32]; };

	//! ----------------------------------------------------------------------------------- !//

	struct dirt_block : base_block {};
	struct zero_block : base_block
	{
		inline zero_block() noexcept { std::ranges::uninitialized_value_construct(__storage); }
	};

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto size(size_t sz) noexcept
	{
		return (sz + alignof(base_block) - 1U) / sizeof(base_block);
	}

	//! ----------------------------------------------------------------------------------- !//

	inline auto zero_acquire(size_t sz) noexcept { return reinterpret_cast<std::byte *>(new (std::nothrow) zero_block[size(sz)]); }
	inline auto dirt_acquire(size_t sz) noexcept { return reinterpret_cast<std::byte *>(new (std::nothrow) dirt_block[size(sz)]); }

	inline auto zero_dispose(std::byte *ptr) noexcept { return delete[] reinterpret_cast<zero_block *>(ptr); }
	inline auto dirt_dispose(std::byte *ptr) noexcept { return delete[] reinterpret_cast<dirt_block *>(ptr); }

	//! ----------------------------------------------------------------------------------- !//

	Memory GlobalAllocator::dirt_alloc(size_t size) const noexcept { return Memory{dirt_acquire(size), dirt_dispose}; }
	Memory GlobalAllocator::zero_alloc(size_t size) const noexcept { return Memory{zero_acquire(size), zero_dispose}; }
	Memory GlobalAllocator::zero_alloc(size_t size) noexcept { return const_cast<GlobalAllocator const *>(this)->zero_alloc(size); }
	Memory GlobalAllocator::dirt_alloc(size_t size) noexcept { return const_cast<GlobalAllocator const *>(this)->dirt_alloc(size); }
}