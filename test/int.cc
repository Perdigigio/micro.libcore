#include <exception>
#include <iostream>

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

//!
//!

#include <libcore/int.hh>

using namespace micro::core;

void test_le_encode();
void test_be_encode();
void test_le_decode();
void test_be_decode();

//! ------------------------------------------------------------------------------------------- !//

constexpr auto _u16 = static_cast<u16>(0x8877);
constexpr auto _i16 = static_cast<i16>(0x8877);
constexpr auto _u32 = static_cast<u32>(0x8877CCDD);
constexpr auto _i32 = static_cast<i32>(0x8877CCDD);
constexpr auto _u64 = static_cast<u64>(0x8877CCDD11223344);
constexpr auto _i64 = static_cast<i64>(0x8877CCDD11223344);

constexpr auto _x16_buffer_be = x16_buffer{std::byte(0x77), std::byte(0x88)};
constexpr auto _x16_buffer_le = x16_buffer{std::byte(0x88), std::byte(0x77)};
constexpr auto _x32_buffer_be = x32_buffer{std::byte(0xDD), std::byte(0xCC), std::byte(0x77), std::byte(0x88)};
constexpr auto _x32_buffer_le = x32_buffer{std::byte(0x88), std::byte(0x77), std::byte(0xCC), std::byte(0xDD)};
constexpr auto _x64_buffer_be = x64_buffer{std::byte(0x44), std::byte(0x33), std::byte(0x22), std::byte(0x11), std::byte(0xDD), std::byte(0xCC), std::byte(0x77), std::byte(0x88)};
constexpr auto _x64_buffer_le = x64_buffer{std::byte(0x88), std::byte(0x77), std::byte(0xCC), std::byte(0xDD), std::byte(0x11), std::byte(0x22), std::byte(0x33), std::byte(0x44)};

//! ------------------------------------------------------------------------------------------- !//

static bool operator !=(x16_buffer const &l, x16_buffer const &r) noexcept
{
	return l[0] != r[0] &&
	       l[1] != r[1];
}

static bool operator !=(x32_buffer const &l, x32_buffer const &r) noexcept
{
	return l[0] != r[0] &&
	       l[1] != r[1] &&
	       l[2] != r[2] &&
	       l[3] != r[3];
}

static bool operator !=(x64_buffer const &l, x64_buffer const &r) noexcept
{
	return l[0] != r[0] &&
	       l[1] != r[1] &&
	       l[2] != r[2] &&
	       l[3] != r[3] &&
	       l[4] != r[4] &&
	       l[5] != r[5] &&
	       l[6] != r[6] &&
	       l[7] != r[7];
}

//! ------------------------------------------------------------------------------------------- !//

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	try
	{
		test_le_encode();
		test_be_encode();
		test_le_decode();
		test_be_decode();
	}
	catch(std::exception const& e)
	{
		std::cerr << "=============================== CAUGHT EXCEPTION ===============================" << std::endl;
		std::cerr << e.what() << std::endl;
		std::cerr << "================================================================================" << std::endl;

		return 1;
	}

	return 0;
}

void test_le_encode()
{
	auto _1 = le_encode(_u16);
	auto _2 = le_encode(_i16);
	auto _3 = le_encode(_u32);
	auto _4 = le_encode(_i32);
	auto _5 = le_encode(_u64);
	auto _6 = le_encode(_i64);

	if (_1 != _x16_buffer_le) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_2 != _x16_buffer_le) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_3 != _x32_buffer_le) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_4 != _x32_buffer_le) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_5 != _x64_buffer_le) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_6 != _x64_buffer_le) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
}

void test_be_encode()
{
	auto _1 = be_encode(_u16);
	auto _2 = be_encode(_i16);
	auto _3 = be_encode(_u32);
	auto _4 = be_encode(_i32);
	auto _5 = be_encode(_u64);
	auto _6 = be_encode(_i64);

	if (_1 != _x16_buffer_be) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_2 != _x16_buffer_be) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_3 != _x32_buffer_be) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_4 != _x32_buffer_be) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_5 != _x64_buffer_be) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_6 != _x64_buffer_be) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
}

void test_le_decode()
{
	auto _1 = le_udecode(_x16_buffer_le);
	auto _2 = le_idecode(_x16_buffer_le);
	auto _3 = le_udecode(_x32_buffer_le);
	auto _4 = le_idecode(_x32_buffer_le);
	auto _5 = le_udecode(_x64_buffer_le);
	auto _6 = le_idecode(_x64_buffer_le);

	if (_1 != _u16) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_2 != _i16) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_3 != _u32) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_4 != _i32) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_5 != _u64) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_6 != _i64) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));	
}

void test_be_decode()
{
	auto _1 = be_udecode(_x16_buffer_be);
	auto _2 = be_idecode(_x16_buffer_be);
	auto _3 = be_udecode(_x32_buffer_be);
	auto _4 = be_idecode(_x32_buffer_be);
	auto _5 = be_udecode(_x64_buffer_be);
	auto _6 = be_idecode(_x64_buffer_be);

	if (_1 != _u16) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_2 != _i16) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_3 != _u32) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_4 != _i32) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_5 != _u64) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	if (_6 != _i64) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
}