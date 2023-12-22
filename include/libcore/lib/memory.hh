#ifndef MICRO_LIBCORE_LIB_MEMORY_HH__GUARD
#define MICRO_LIBCORE_LIB_MEMORY_HH__GUARD

#include <cstddef>    //! byte, size_t
#include <span>
#include <memory>

namespace micro::core::lib
{
	using Memory = std::unique_ptr<std::byte, void (*)(std::byte *) noexcept>;

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
	concept c_allocator = requires(T const all)
	{
		{ all.zero_alloc(size_t{}) } -> std::convertible_to<Memory>;
		{ all.dirt_alloc(size_t{}) } -> std::convertible_to<Memory>;
	};

	template<c_allocator T> auto zero_alloc(T const &a, size_t s) noexcept -> Memory { return a.zero_alloc(s); }
	template<c_allocator T> auto dirt_alloc(T const &a, size_t s) noexcept -> Memory { return a.dirt_alloc(s); }

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
	concept m_allocator = requires(T all)
	{
		{ all.zero_alloc(size_t{}) } -> std::convertible_to<Memory>;
		{ all.dirt_alloc(size_t{}) } -> std::convertible_to<Memory>;
	};

	template<m_allocator T> auto zero_alloc(T &a, size_t s) noexcept -> Memory { return a.zero_alloc(s); }
	template<m_allocator T> auto dirt_alloc(T &a, size_t s) noexcept -> Memory { return a.dirt_alloc(s); }

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		using Span = std::span<T>;

	using MBufferView = Span<std::byte>;
	using CBufferView = Span<std::byte const>;

	inline MBufferView mview(MBufferView const &b) noexcept { return b; }
	inline CBufferView cview(MBufferView const &b) noexcept { return b; }
	inline CBufferView cview(CBufferView const &b) noexcept { return b; }

	inline MBufferView mview(MBufferView const &b, size_t o, size_t l = std::dynamic_extent) noexcept { return b.subspan(o, l); }
	inline CBufferView cview(MBufferView const &b, size_t o, size_t l = std::dynamic_extent) noexcept { return b.subspan(o, l); }
	inline CBufferView cview(CBufferView const &b, size_t o, size_t l = std::dynamic_extent) noexcept { return b.subspan(o, l); }

	inline auto head(MBufferView const &b) noexcept { return data(b); }
	inline auto head(CBufferView const &b) noexcept { return data(b); }
	inline auto tail(MBufferView const &b) noexcept { return data(b) + size(b); }
	inline auto tail(CBufferView const &b) noexcept { return data(b) + size(b); }

	//! ----------------------------------------------------------------------------------- !//

	struct GlobalAllocator
	{
		Memory zero_alloc(size_t size) const noexcept;
		Memory dirt_alloc(size_t size) const noexcept;
		Memory zero_alloc(size_t size) noexcept;
		Memory dirt_alloc(size_t size) noexcept;
	};

}

#endif //! MICRO_LIBCORE_LIB_RESULT_HH__GUARD