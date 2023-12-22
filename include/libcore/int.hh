#ifndef MICRO_LIBCORE_INT_HH__GUARD
#define MICRO_LIBCORE_INT_HH__GUARD

#include <array>
#include <cstdint>
#include <span>

namespace micro::core
{
	using u16 = uint_least16_t;
	using u32 = uint_least32_t;
	using u64 = uint_least64_t;

	//! ----------------------------------------------------------------------------------- !//

	enum class wword : u16 {};
	enum class dword : u32 {};
	enum class qword : u64 {};

	constexpr wword as_wword(u16 v) noexcept { return static_cast<wword>(v); }
	constexpr dword as_dword(u32 v) noexcept { return static_cast<dword>(v); }
	constexpr qword as_qword(u64 v) noexcept { return static_cast<qword>(v); }

	constexpr u16 to_integer(wword v) noexcept { return static_cast<u16>(v); }
	constexpr u32 to_integer(dword v) noexcept { return static_cast<u32>(v); }
	constexpr u64 to_integer(qword v) noexcept { return static_cast<u64>(v); }

	constexpr wword operator &(wword l, wword r) noexcept { return as_wword(to_integer(l) & to_integer(r)); }
	constexpr dword operator &(dword l, dword r) noexcept { return as_dword(to_integer(l) & to_integer(r)); }
	constexpr qword operator &(qword l, qword r) noexcept { return as_qword(to_integer(l) & to_integer(r)); }

	constexpr wword operator |(wword l, wword r) noexcept { return as_wword(to_integer(l) | to_integer(r)); }
	constexpr dword operator |(dword l, dword r) noexcept { return as_dword(to_integer(l) | to_integer(r)); }
	constexpr qword operator |(qword l, qword r) noexcept { return as_qword(to_integer(l) | to_integer(r)); }

	constexpr wword operator ^(wword l, wword r) noexcept { return as_wword(to_integer(l) ^ to_integer(r)); }
	constexpr dword operator ^(dword l, dword r) noexcept { return as_dword(to_integer(l) ^ to_integer(r)); }
	constexpr qword operator ^(qword l, qword r) noexcept { return as_qword(to_integer(l) ^ to_integer(r)); }

	constexpr wword operator ~(wword l) noexcept { return as_wword(~to_integer(l)); }
	constexpr dword operator ~(dword l) noexcept { return as_dword(~to_integer(l)); }
	constexpr qword operator ~(qword l) noexcept { return as_qword(~to_integer(l)); }

	constexpr wword operator >>(wword l, u16 r) noexcept { return as_wword(to_integer(l) >> r); }
	constexpr dword operator >>(dword l, u32 r) noexcept { return as_dword(to_integer(l) >> r); }
	constexpr qword operator >>(qword l, u64 r) noexcept { return as_qword(to_integer(l) >> r); }

	constexpr wword operator <<(wword l, u16 r) noexcept { return as_wword(to_integer(l) << r); }
	constexpr dword operator <<(dword l, u32 r) noexcept { return as_dword(to_integer(l) << r); }
	constexpr qword operator <<(qword l, u64 r) noexcept { return as_qword(to_integer(l) << r); }

	//! ----------------------------------------------------------------------------------- !//

	using i16 = int_least16_t;
	using i32 = int_least32_t;
	using i64 = int_least64_t;

	//! ----------------------------------------------------------------------------------- !//

	using x16_buffer = std::array<std::byte, 2>;
	using x32_buffer = std::array<std::byte, 4>;
	using x64_buffer = std::array<std::byte, 8>;

	//! ----------------------------------------------------------------------------------- !//

	constexpr x16_buffer be_encode(u16 i) noexcept
	{
		return { static_cast<std::byte>((i >> 000) & 0xFF),
			 static_cast<std::byte>((i >> 010) & 0xFF) };
	}

	constexpr x16_buffer le_encode(u16 i) noexcept
	{
		return { static_cast<std::byte>((i >> 010) & 0xFF),
			 static_cast<std::byte>((i >> 000) & 0xFF) };
	}

	constexpr x32_buffer be_encode(u32 i) noexcept
	{
		return { static_cast<std::byte>((i >> 000) & 0xFF),
			 static_cast<std::byte>((i >> 010) & 0xFF),
			 static_cast<std::byte>((i >> 020) & 0xFF),
			 static_cast<std::byte>((i >> 030) & 0xFF) };
	}

	constexpr x32_buffer le_encode(u32 i) noexcept
	{
		return { static_cast<std::byte>((i >> 030) & 0xFF),
			 static_cast<std::byte>((i >> 020) & 0xFF),
			 static_cast<std::byte>((i >> 010) & 0xFF),
			 static_cast<std::byte>((i >> 000) & 0xFF) };
	}

	constexpr x64_buffer be_encode(u64 i) noexcept
	{
		return { static_cast<std::byte>((i >> 000) & 0xFF),
			 static_cast<std::byte>((i >> 010) & 0xFF),
			 static_cast<std::byte>((i >> 020) & 0xFF),
			 static_cast<std::byte>((i >> 030) & 0xFF),
			 static_cast<std::byte>((i >> 040) & 0xFF),
			 static_cast<std::byte>((i >> 050) & 0xFF),
			 static_cast<std::byte>((i >> 060) & 0xFF),
			 static_cast<std::byte>((i >> 070) & 0xFF) };
	}

	constexpr x64_buffer le_encode(u64 i) noexcept
	{
		return { static_cast<std::byte>((i >> 070) & 0xFF),
			 static_cast<std::byte>((i >> 060) & 0xFF),
			 static_cast<std::byte>((i >> 050) & 0xFF),
			 static_cast<std::byte>((i >> 040) & 0xFF),
			 static_cast<std::byte>((i >> 030) & 0xFF),
			 static_cast<std::byte>((i >> 020) & 0xFF),
			 static_cast<std::byte>((i >> 010) & 0xFF),
			 static_cast<std::byte>((i >> 000) & 0xFF) };
	}

	constexpr x16_buffer be_encode(i16 i) noexcept { return be_encode(static_cast<u16>(i)); }
	constexpr x16_buffer le_encode(i16 i) noexcept { return le_encode(static_cast<u16>(i)); }
	constexpr x32_buffer be_encode(i32 i) noexcept { return be_encode(static_cast<u32>(i)); }
	constexpr x32_buffer le_encode(i32 i) noexcept { return le_encode(static_cast<u32>(i)); }
	constexpr x64_buffer be_encode(i64 i) noexcept { return be_encode(static_cast<u64>(i)); }
	constexpr x64_buffer le_encode(i64 i) noexcept { return le_encode(static_cast<u64>(i)); }

	constexpr x16_buffer be_encode(wword i) noexcept { return be_encode(to_integer(i)); }
	constexpr x16_buffer le_encode(wword i) noexcept { return le_encode(to_integer(i)); }
	constexpr x32_buffer be_encode(dword i) noexcept { return be_encode(to_integer(i)); }
	constexpr x32_buffer le_encode(dword i) noexcept { return le_encode(to_integer(i)); }
	constexpr x64_buffer be_encode(qword i) noexcept { return be_encode(to_integer(i)); }
	constexpr x64_buffer le_encode(qword i) noexcept { return le_encode(to_integer(i)); }

	//! ----------------------------------------------------------------------------------- !//

	constexpr u16 be_udecode(x16_buffer const &b) noexcept
	{
		return static_cast<u16>(b[0]) << 000 |
		       static_cast<u16>(b[1]) << 010;
	}

	constexpr u16 le_udecode(x16_buffer const &b) noexcept
	{
		return static_cast<u16>(b[0]) << 010 |
		       static_cast<u16>(b[1]) << 000;
	}

	constexpr u32 be_udecode(x32_buffer const &b) noexcept
	{
		return static_cast<u32>(b[0]) << 000 |
		       static_cast<u32>(b[1]) << 010 |
		       static_cast<u32>(b[2]) << 020 |
		       static_cast<u32>(b[3]) << 030;
	}

	constexpr u32 le_udecode(x32_buffer const &b) noexcept
	{
		return static_cast<u32>(b[0]) << 030 |
		       static_cast<u32>(b[1]) << 020 |
		       static_cast<u32>(b[2]) << 010 |
		       static_cast<u32>(b[3]) << 000;
	}

	constexpr u64 be_udecode(x64_buffer const &b) noexcept
	{
		return static_cast<u64>(b[0]) << 000 |
		       static_cast<u64>(b[1]) << 010 |
		       static_cast<u64>(b[2]) << 020 |
		       static_cast<u64>(b[3]) << 030 |
		       static_cast<u64>(b[4]) << 040 |
		       static_cast<u64>(b[5]) << 050 |
		       static_cast<u64>(b[6]) << 060 |
		       static_cast<u64>(b[7]) << 070;
	}

	constexpr u64 le_udecode(x64_buffer const &b) noexcept
	{
		return static_cast<u64>(b[0]) << 070 |
		       static_cast<u64>(b[1]) << 060 |
		       static_cast<u64>(b[2]) << 050 |
		       static_cast<u64>(b[3]) << 040 |
		       static_cast<u64>(b[4]) << 030 |
		       static_cast<u64>(b[5]) << 020 |
		       static_cast<u64>(b[6]) << 010 |
		       static_cast<u64>(b[7]) << 000;
	}

	constexpr i16 be_idecode(x16_buffer const &b) noexcept { return static_cast<i16>(be_udecode(b)); }
	constexpr i16 le_idecode(x16_buffer const &b) noexcept { return static_cast<i16>(le_udecode(b)); }
	constexpr i32 be_idecode(x32_buffer const &b) noexcept { return static_cast<i32>(be_udecode(b)); }
	constexpr i32 le_idecode(x32_buffer const &b) noexcept { return static_cast<i32>(le_udecode(b)); }
	constexpr i64 be_idecode(x64_buffer const &b) noexcept { return static_cast<i64>(be_udecode(b)); }
	constexpr i64 le_idecode(x64_buffer const &b) noexcept { return static_cast<i64>(le_udecode(b)); }

	constexpr wword be_wdecode(x16_buffer const &b) noexcept { return as_wword(be_udecode(b)); }
	constexpr wword le_wdecode(x16_buffer const &b) noexcept { return as_wword(le_udecode(b)); }
	constexpr dword be_wdecode(x32_buffer const &b) noexcept { return as_dword(be_udecode(b)); }
	constexpr dword le_wdecode(x32_buffer const &b) noexcept { return as_dword(le_udecode(b)); }
	constexpr qword be_wdecode(x64_buffer const &b) noexcept { return as_qword(be_udecode(b)); }
	constexpr qword le_wdecode(x64_buffer const &b) noexcept { return as_qword(le_udecode(b)); }

	//! ----------------------------------------------------------------------------------- !//

	constexpr dword fourcc(char f, char o, char u, char r) noexcept
	{
		return as_dword(static_cast<unsigned char>(f)) << 000 |
		       as_dword(static_cast<unsigned char>(o)) << 010 |
		       as_dword(static_cast<unsigned char>(u)) << 020 |
		       as_dword(static_cast<unsigned char>(r)) << 030;
	}

	//! ----------------------------------------------------------------------------------- !//

	//using uuid = std::array<std::byte, 16>; //! [0] AAAAAAAABBBBCCCCDDDDEEEEEEEEEEEE [16]

	struct uuid
	{
		std::byte a[4];
		std::byte b[2];
		std::byte c[2];
		std::byte d[2];
		std::byte e[6];

		friend  constexpr auto operator <=>(uuid const &a, uuid const &b) noexcept = default;
	};
	
	constexpr auto make_uuid(std::span<std::byte const, 16> data) noexcept
	{
		return uuid{data[0x0], data[0x1], data[0x2], data[0x3],
			    data[0x4], data[0x5], data[0x6], data[0x7],
			    data[0x8], data[0x9], data[0xA], data[0xB],
			    data[0xC], data[0xD], data[0xE], data[0xF]};
	}

	inline auto make_uuid(std::span<uint8_t const, 16> data) noexcept
	{
		return make_uuid(std::as_bytes(data));
	}

	constexpr auto uuid_a(uuid const &_uuid) noexcept { return std::span{_uuid.a}; }
	constexpr auto uuid_b(uuid const &_uuid) noexcept { return std::span{_uuid.b}; }
	constexpr auto uuid_c(uuid const &_uuid) noexcept { return std::span{_uuid.c}; }
	constexpr auto uuid_d(uuid const &_uuid) noexcept { return std::span{_uuid.d}; }
	constexpr auto uuid_e(uuid const &_uuid) noexcept { return std::span{_uuid.e}; }
}

#endif //! MICRO_LIBCORE_INT_HH__GUARD