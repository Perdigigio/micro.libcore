#include <libcore/lib/string.hh>
#include <libcore/lib/panics.hh>

namespace micro::core::lib
{

	template<class T>
		inline LString as_dec(T v) noexcept { return std::to_string(v); }

	//! ----------------------------------------------------------------------------------- !//

	inline LString as_hex(u16 i) noexcept
	{
		static constexpr char const _lookup[] = "0123456789ABCDEF";

		return {_lookup[(i >> 0xC) & 0xF], 
			_lookup[(i >> 0x8) & 0xF], 
			_lookup[(i >> 0x4) & 0xF], 
			_lookup[(i >> 0x0) & 0xF]};
	}

	inline LString as_hex(u32 i) noexcept
	{
		return as_hex(static_cast<u16>((i >> 0x10) & 0xFFFF)) +
		       as_hex(static_cast<u16>((i >> 0x00) & 0xFFFF));
	}

	inline LString as_hex(u64 i) noexcept
	{
		return as_hex(static_cast<u16>((i >> 0x30) & 0xFFFF)) +
		       as_hex(static_cast<u16>((i >> 0x20) & 0xFFFF)) + 
		       as_hex(static_cast<u16>((i >> 0x10) & 0xFFFF)) + 
		       as_hex(static_cast<u16>((i >> 0x00) & 0xFFFF));
	}

	inline LString as_hex(i16 i) noexcept { return as_hex(static_cast<u16>(i)); }
	inline LString as_hex(i32 i) noexcept { return as_hex(static_cast<u32>(i)); }
	inline LString as_hex(i64 i) noexcept { return as_hex(static_cast<u64>(i)); }

	//! ----------------------------------------------------------------------------------- !//

	inline LString as_oct(u16 i) noexcept
	{
		static constexpr char const _lookup[] = "01234567";

		return {_lookup[(i >> 017) & 07],
			_lookup[(i >> 014) & 07],
			_lookup[(i >> 011) & 07],  /// 0:3
			_lookup[(i >> 006) & 07],  /// 4:7
			_lookup[(i >> 003) & 07],  /// 8:B
			_lookup[(i >> 000) & 07]}; /// C:F
	}

	inline LString as_oct(u32 i) noexcept
	{
		static constexpr char const _lookup[] = "01234567";

		return {_lookup[(i >> 036) & 07],
			_lookup[(i >> 033) & 07],  /// 0:3
			_lookup[(i >> 030) & 07],  /// 4:7
			_lookup[(i >> 025) & 07],  /// 8:B
			_lookup[(i >> 022) & 07],
			_lookup[(i >> 017) & 07],
			_lookup[(i >> 014) & 07],
			_lookup[(i >> 011) & 07],  /// 0:3
			_lookup[(i >> 006) & 07],  /// 4:7
			_lookup[(i >> 003) & 07],  /// 8:B
			_lookup[(i >> 000) & 07]}; /// C:F
	}

	inline LString as_oct(u64 i) noexcept
	{
		static constexpr char const _lookup[] = "01234567";

		return {_lookup[(i >> 077) & 07],
			_lookup[(i >> 074) & 07],
			_lookup[(i >> 071) & 07],
			_lookup[(i >> 066) & 07],
			_lookup[(i >> 063) & 07],
			_lookup[(i >> 060) & 07],
			_lookup[(i >> 055) & 07],
			_lookup[(i >> 052) & 07],
			_lookup[(i >> 047) & 07],
			_lookup[(i >> 044) & 07],
			_lookup[(i >> 041) & 07],
			_lookup[(i >> 036) & 07],
			_lookup[(i >> 033) & 07],
			_lookup[(i >> 030) & 07],
			_lookup[(i >> 025) & 07],
			_lookup[(i >> 022) & 07],
			_lookup[(i >> 017) & 07],
			_lookup[(i >> 014) & 07],
			_lookup[(i >> 011) & 07], 
			_lookup[(i >> 006) & 07], 
			_lookup[(i >> 003) & 07], 
			_lookup[(i >> 000) & 07]};
	}

	inline LString as_oct(i16 i) noexcept { return as_oct(static_cast<u16>(i)); }
	inline LString as_oct(i32 i) noexcept { return as_oct(static_cast<u32>(i)); }
	inline LString as_oct(i64 i) noexcept { return as_oct(static_cast<u64>(i)); }

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		inline LString select_as_string(T v, nbase b) noexcept
		{
			switch (b)
			{
				case nbase::dec: return as_dec(v);
				case nbase::hex: return as_hex(v);
				case nbase::oct: return as_oct(v);
			}

			///
			/// SHOULD NEVER BE REACHED
			///

			LIBCORE_NOREACH("invalid nbase: ![nbase::dec, nbase::hex, nbase::oct]");
		}

	//! ----------------------------------------------------------------------------------- !//

	LString as_string(i16 i, nbase base) noexcept { return select_as_string(i, base); }
	LString as_string(i32 i, nbase base) noexcept { return select_as_string(i, base); }
	LString as_string(i64 i, nbase base) noexcept { return select_as_string(i, base); }
	LString as_string(u16 i, nbase base) noexcept { return select_as_string(i, base); }
	LString as_string(u32 i, nbase base) noexcept { return select_as_string(i, base); }
	LString as_string(u64 i, nbase base) noexcept { return select_as_string(i, base); }
}