#include <libcore/lib/memory.hh>

namespace micro::core::lib
{
	static auto _zero_acquire(size_t size) -> std::byte *
	{
		return new (GlobalAllocator::ALIGNOF, std::nothrow) std::byte[size]{};
	}

	static auto _dirt_acquire(size_t size) -> std::byte *
	{
		return new (GlobalAllocator::ALIGNOF, std::nothrow) std::byte[size];
	}

	static auto _dispose(std::byte addr []) -> void
	{
		operator delete[](addr, GlobalAllocator::ALIGNOF, std::nothrow);
	}

	//!
	//!

	Memory GlobalAllocator::dirt_alloc(size_t size) const noexcept { return Memory{_dirt_acquire(size), _dispose}; }
	Memory GlobalAllocator::zero_alloc(size_t size) const noexcept { return Memory{_zero_acquire(size), _dispose}; }
}