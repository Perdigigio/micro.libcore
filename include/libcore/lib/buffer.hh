#ifndef MICRO_LIBCORE_LIB_BUFFER_HH__GUARD
#define MICRO_LIBCORE_LIB_BUFFER_HH__GUARD

#include "memory.hh"

namespace micro::core::lib
{

	class Buffer
	{
	public:
		using Length = size_t;
	
	public:
		/// @brief Initialize an empty buffer object
		///
		inline Buffer() noexcept = default;

		/// @brief Initialize a new buffer object
		///
		/// @param memory 
		/// @param length
		///
		inline Buffer(Memory memory, Length length) noexcept :
			m_data{std::move(memory)},
			m_size{std::move(length)}
		{}

		inline operator CBufferView () const noexcept { return std::span{m_data.get(), m_size}; }
		inline operator MBufferView () const noexcept { return std::span{m_data.get(), m_size}; }

	private:
		Memory m_data = {nullptr, nullptr};
		Length m_size = {};
	};

	//!
	//!

	template<m_allocator T> inline auto make_zero_buffer(T &a, size_t s) noexcept { return Buffer{zero_alloc(a, s), s}; }
	template<m_allocator T> inline auto make_dirt_buffer(T &a, size_t s) noexcept { return Buffer{dirt_alloc(a, s), s}; }
	template<c_allocator T> inline auto make_zero_buffer(T const &a, size_t s) noexcept { return Buffer{zero_alloc(a, s), s}; }
	template<c_allocator T> inline auto make_dirt_buffer(T const &a, size_t s) noexcept { return Buffer{dirt_alloc(a, s), s}; }

	//! ----------------------------------------------------------------------------------- !//

	inline MBufferView mview(Buffer const &b) noexcept { return static_cast<MBufferView>(b); }
	inline CBufferView cview(Buffer const &b) noexcept { return static_cast<CBufferView>(b); }
	inline MBufferView mview(Buffer const &b, size_t o, size_t l = std::dynamic_extent) noexcept { return mview(b).subspan(o, l); }
	inline CBufferView cview(Buffer const &b, size_t o, size_t l = std::dynamic_extent) noexcept { return cview(b).subspan(o, l); }

} // namespace micro::core::lib


#endif