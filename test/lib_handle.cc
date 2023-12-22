#include <iostream>
#include <iomanip>

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

#include <libcore/lib/handle.hh>
#include <libcore/lib/memory.hh>

using namespace micro::core;

static constexpr lib::Handle<16, 16> a{1, 1};
static constexpr lib::Handle<16, 16> b{1, 1};
static constexpr lib::Handle<16, 16> c{2, 1};

enum idxa : int {};
enum idxb : int {};


int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	auto _1 = lib::zero_alloc(lib::GlobalAllocator{}, 512);
	auto _2 = lib::zero_alloc(lib::GlobalAllocator{}, 512);

	_1 = std::move(_2);

	enum class HH : u32 { VALUE = 0xFF };

	lib::NullableHandle<HH> nh1;
	lib::NullableHandle<HH> nh2;
	lib::NullableHandle<HH> vh1 = HH::VALUE;
	lib::NullableHandle<HH> vh2 = HH::VALUE;

	struct deleter
	{
		using pointer = lib::NullableHandle<HH>;

		inline void operator()(pointer p) noexcept
		{
			std::cout << "Handle: " << static_cast<u32>(static_cast<HH>(p)) << std::endl;
		}
	};

	std::unique_ptr<lib::NullableHandle<HH>, deleter> _{HH::VALUE};

	try
	{
		if (!(nh1 == nh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh1 == nh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh1 != vh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh1 != vh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (!(nh2 == nh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh2 == nh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh2 != vh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh2 != vh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (!(vh1 != nh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(vh1 != nh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(vh1 == vh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(vh1 == vh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (!(vh2 != nh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(vh2 != nh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(vh2 == vh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(vh2 == vh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (!(nullptr == nh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nullptr == nh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh1 == nullptr)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(nh2 == nullptr)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(!nh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(!nh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!( vh1)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!( vh2)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (!(a == b)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(a <= b)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(a >= b)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(a != c)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(a <  c)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if ((a != b)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if ((a <  b)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if ((a >  b)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if ((a >  c)) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
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