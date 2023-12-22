#ifndef MICRO_LIBCORE_LIB_HANDLE_HH__GUARD
#define MICRO_LIBCORE_LIB_HANDLE_HH__GUARD

#include <libcore/int.hh>
#include <libcore/lib.hh>

#include <compare>

namespace micro::core::lib
{

	template<class Type,
		 class Name = Type, Type N = Type{}>
	struct NullableHandle
	{
	public:
		using Nptr = std::nullptr_t;

	public:
		constexpr NullableHandle() noexcept = default;

		//! --------------------------------------------------------------------------- !//

		constexpr NullableHandle(Nptr v) noexcept : m_value{N} {}
		constexpr NullableHandle(Type v) noexcept : m_value{v} {}

		//! --------------------------------------------------------------------------- !//

		constexpr operator bool() const noexcept { return m_value != N; }
		constexpr operator Type() const noexcept { return m_value; }

		//! --------------------------------------------------------------------------- !//

		constexpr bool operator ==(NullableHandle const &) const noexcept = default;
		constexpr bool operator !=(NullableHandle const &) const noexcept = default;
		constexpr bool operator ==(Nptr) noexcept { return m_value == N; }
		constexpr bool operator !=(Nptr) noexcept { return m_value != N; }

		//! --------------------------------------------------------------------------- !//

		constexpr NullableHandle &operator =(Nptr _) noexcept { m_value = N; return *this; }
		constexpr NullableHandle &operator =(Type v) noexcept { m_value = v; return *this; }
	private:
		Type m_value = N;
	};



	template<size_t IndexBits,
		 size_t MagicBits>
	struct Handle : public Comparable< Handle<IndexBits, MagicBits> >
	{
		constexpr static auto INDEX_BITS = IndexBits;
		constexpr static auto MAGIC_BITS = MagicBits;
		constexpr static auto INDEX_LAST = (1 << IndexBits) - 1;
		constexpr static auto MAGIC_LAST = (1 << MagicBits) - 1;

		const u32 index : INDEX_BITS;
		const u32 magic : MAGIC_BITS;

		//!
		//!

		constexpr Handle(u32 _index = 0, u32 _magic = 0) noexcept :
			index{_index},
			magic{_magic}
		{}

		constexpr u32 get_index() const noexcept { return index; }
		constexpr u32 get_magic() const noexcept { return magic; }
		constexpr u32 get_value() const noexcept { return index | static_cast<u32>(INDEX_LAST + magic); }

		//! --------------------------------------------------------------------------- !//

		constexpr auto compare(Handle const &rhs) const noexcept;
	};

	//!
	//!

	template<size_t IndexBits,
		 size_t MagicBits>
	constexpr u32 get_index(Handle<IndexBits, MagicBits> const &h) noexcept { return h.get_index(); }

	template<size_t IndexBits,
		 size_t MagicBits>
	constexpr u32 get_magic(Handle<IndexBits, MagicBits> const &h) noexcept { return h.get_magic(); }

	template<size_t IndexBits,
		 size_t MagicBits>
	constexpr u32 get_value(Handle<IndexBits, MagicBits> const &h) noexcept { return h.get_value(); }

	//!
	//!

	template<size_t IndexBits,
		 size_t MagicBits>
	constexpr auto Handle<IndexBits, MagicBits>::compare(Handle const &rhs) const noexcept
	{
		auto const cmp = get_value() <=> rhs.get_value();

		return std::is_lt(cmp) ? comparison_r::lt :
		       std::is_gt(cmp) ? comparison_r::gt : comparison_r::eq;
	}
}

#endif