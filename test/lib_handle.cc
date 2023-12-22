#include <iostream>
#include <iomanip>

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

#include <libcore/lib/handle.hh>

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

	try
	{
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