#ifndef MICRO_LIBCORE_LIB_STRING_HH__GUARD
#define MICRO_LIBCORE_LIB_STRING_HH__GUARD

#include <libcore/int.hh>

#include <string>
#include <string_view>

namespace micro::core::lib
{
	using LString = std::string;
	using RString = std::string_view;

	//! ----------------------------------------------------------------------------------- !//

	inline LString as_string(RString s) noexcept { return LString{static_cast<RString &&>(s)}; }
	inline LString as_string(LString s) noexcept { return LString{static_cast<LString &&>(s)}; }

	//! ----------------------------------------------------------------------------------- !//

	enum class nbase
	{
		dec,
		hex,
		oct
	};

	LString as_string(i16 i, nbase base = nbase::dec) noexcept;
	LString as_string(i32 i, nbase base = nbase::dec) noexcept;
	LString as_string(i64 i, nbase base = nbase::dec) noexcept;
	LString as_string(u16 i, nbase base = nbase::dec) noexcept;
	LString as_string(u32 i, nbase base = nbase::dec) noexcept;
	LString as_string(u64 i, nbase base = nbase::dec) noexcept;

	///

	template<class T,
		 nbase B>
	struct integer_with_base { T _value; };

	template<class T>
		constexpr integer_with_base<T, nbase::dec> fmt_dec(T _value) noexcept { return{_value}; }
	template<class T>
		constexpr integer_with_base<T, nbase::hex> fmt_hex(T _value) noexcept { return{_value}; }
	template<class T>
		constexpr integer_with_base<T, nbase::oct> fmt_oct(T _value) noexcept { return{_value}; }

	template<class T,
		 nbase B>
	inline LString as_string(integer_with_base<T, B> i) noexcept { return as_string(i._value, B); }

	//! ----------------------------------------------------------------------------------- !//

	template<size_t N>
		inline LString as_string(char const (&s)[N]) noexcept { return LString{s, 0, N}; };

	//! ----------------------------------------------------------------------------------- !//

	inline LString as_string(void const *p) noexcept
	{
		return "[ptr: 0x" + as_string(reinterpret_cast<std::uintptr_t>(p), nbase::hex) + "]";
	}

	//! ----------------------------------------------------------------------------------- !//

	inline LString as_string(std::byte b) noexcept
	{
		return {"0123456789abcdef"[(static_cast<u32>(b) >> 4) & 0xF],
			"0123456789abcdef"[(static_cast<u32>(b) >> 0) & 0xF]};
	}

	inline LString as_string(uuid const &_uuid) noexcept
	{
		LString _ret;

		for (auto _a : uuid_a(_uuid)) _ret += as_string(_a); _ret += '-';
		for (auto _b : uuid_b(_uuid)) _ret += as_string(_b); _ret += '-';
		for (auto _c : uuid_c(_uuid)) _ret += as_string(_c); _ret += '-';
		for (auto _d : uuid_d(_uuid)) _ret += as_string(_d); _ret += '-';
		for (auto _e : uuid_e(_uuid)) _ret += as_string(_e);

		return _ret;
	}

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
	concept is_catenable = requires(T _stringable)
	{
		{ as_string(_stringable) } -> std::convertible_to<LString>;
	};

	template<is_catenable ... Args>
		inline LString cat(Args && ...args) noexcept { return (as_string(std::forward<Args>(args)) += ...); }
}

#endif //! MICRO_LIBCORE_LIB_RESULT_HH__GUARD