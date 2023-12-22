#ifndef MICRO_LIBCORE_LIB_MEMORY_HH__GUARD
#define MICRO_LIBCORE_LIB_MEMORY_HH__GUARD

#include <libcore/lib.hh>

#include <cstddef>    //! byte, size_t
#include <functional> //! function
#include <memory>     //! unique_ptr
#include <new>        //! align_val_t
#include <tuple>      //! tuple
#include <span>

namespace micro::core::lib
{
	using Memory = std::unique_ptr<std::byte[], std::function<void(std::byte [])>>;

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		struct Allocator {};

	//!
	//!

	template<class T>
		auto zero_alloc(Allocator<T> &a, size_t s) noexcept -> Memory { return upcast(a).zero_alloc(s); }
	template<class T>
		auto dirt_alloc(Allocator<T> &a, size_t s) noexcept -> Memory { return upcast(a).dirt_alloc(s); }
	template<class T>
		auto zero_alloc(Allocator<T> const &a, size_t s) noexcept -> Memory { return upcast(a).zero_alloc(s); }
	template<class T>
		auto dirt_alloc(Allocator<T> const &a, size_t s) noexcept -> Memory { return upcast(a).dirt_alloc(s); }

	//! ----------------------------------------------------------------------------------- !//

	using Buffer = std::tuple<Memory, size_t>;

	//!
	//!

	template<class T>
		inline auto make_zero_buffer(Allocator<T> &a, size_t s) noexcept { return Buffer(zero_alloc(upcast(a), s), s); }
	template<class T>
		inline auto make_dirt_buffer(Allocator<T> &a, size_t s) noexcept { return Buffer(dirt_alloc(upcast(a), s), s); }
	template<class T>
		inline auto make_zero_buffer(Allocator<T> const &a, size_t s) noexcept { return Buffer(zero_alloc(upcast(a), s), s); }
	template<class T>
		inline auto make_dirt_buffer(Allocator<T> const &a, size_t s) noexcept { return Buffer(dirt_alloc(upcast(a), s), s); }

	//!
	//!

	inline auto const &data(Buffer const &b) noexcept { return std::get<0>(b); }
	inline auto const &size(Buffer const &b) noexcept { return std::get<1>(b); }

	inline auto head(Buffer const &b) noexcept { return data(b).get(); }
	inline auto tail(Buffer const &b) noexcept { return data(b).get() + size(b); }

	//! ----------------------------------------------------------------------------------- !//

	using MBufferView = std::span<std::byte, std::dynamic_extent>;
	using CBufferView = std::span<std::byte const, std::dynamic_extent>;

	inline MBufferView mview(Buffer const &b) noexcept { return MBufferView{head(b), size(b)}; }
	inline CBufferView cview(Buffer const &b) noexcept { return CBufferView{head(b), size(b)}; }
	inline MBufferView mview(MBufferView const &b) noexcept { return b; }
	inline CBufferView cview(MBufferView const &b) noexcept { return b; }
	inline CBufferView cview(CBufferView const &b) noexcept { return b; }

	inline MBufferView mview(Buffer const &b, size_t o, size_t l) noexcept { return mview(b).subspan(o, l); }
	inline CBufferView cview(Buffer const &b, size_t o, size_t l) noexcept { return cview(b).subspan(o, l); }
	inline MBufferView mview(MBufferView const &b, size_t o, size_t l) noexcept { return b.subspan(o, l); }
	inline CBufferView cview(MBufferView const &b, size_t o, size_t l) noexcept { return b.subspan(o, l); }
	inline CBufferView cview(CBufferView const &b, size_t o, size_t l) noexcept { return b.subspan(o, l); }

	inline MBufferView mview(Buffer const &b, size_t o) noexcept { return mview(b, o, std::dynamic_extent); }
	inline CBufferView cview(Buffer const &b, size_t o) noexcept { return cview(b, o, std::dynamic_extent); }
	inline MBufferView mview(MBufferView const &b, size_t o) noexcept { return mview(b, o, std::dynamic_extent); }
	inline CBufferView cview(MBufferView const &b, size_t o) noexcept { return cview(b, o, std::dynamic_extent); }
	inline CBufferView cview(CBufferView const &b, size_t o) noexcept { return cview(b, o, std::dynamic_extent); }

	inline auto head(MBufferView const &b) noexcept { return data(b); }
	inline auto head(CBufferView const &b) noexcept { return data(b); }
	inline auto tail(MBufferView const &b) noexcept { return data(b) + size(b); }
	inline auto tail(CBufferView const &b) noexcept { return data(b) + size(b); }

	//! ----------------------------------------------------------------------------------- !//

	struct GlobalAllocator : public Allocator<GlobalAllocator>
	{
		static constexpr std::align_val_t ALIGNOF { alignof(std::max_align_t) };

		//!
		//!

		Memory zero_alloc(size_t size) const noexcept;
		Memory dirt_alloc(size_t size) const noexcept;
	};
}

#endif //! MICRO_LIBCORE_LIB_RESULT_HH__GUARD