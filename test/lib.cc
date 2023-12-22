#include <iostream>
#include <iomanip>

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

#include <libcore/lib.hh>

using namespace micro::core;

struct TestEqForSuccess : Eq<TestEqForSuccess> { constexpr bool eq(TestEqForSuccess const &b) const noexcept; };
struct TestNeForSuccess : Ne<TestNeForSuccess> { constexpr bool ne(TestNeForSuccess const &b) const noexcept; };
struct TestLtForSuccess : Lt<TestLtForSuccess> { constexpr bool lt(TestLtForSuccess const &b) const noexcept; };
struct TestGtForSuccess : Gt<TestGtForSuccess> { constexpr bool gt(TestGtForSuccess const &b) const noexcept; };
struct TestLeForSuccess : Le<TestLeForSuccess> { constexpr bool le(TestLeForSuccess const &b) const noexcept; };
struct TestGeForSuccess : Ge<TestGeForSuccess> { constexpr bool ge(TestGeForSuccess const &b) const noexcept; };

constexpr bool TestEqForSuccess::eq(TestEqForSuccess const &b) const noexcept { return true; }
constexpr bool TestNeForSuccess::ne(TestNeForSuccess const &b) const noexcept { return true; }
constexpr bool TestLtForSuccess::lt(TestLtForSuccess const &b) const noexcept { return true; }
constexpr bool TestGtForSuccess::gt(TestGtForSuccess const &b) const noexcept { return true; }
constexpr bool TestLeForSuccess::le(TestLeForSuccess const &b) const noexcept { return true; }
constexpr bool TestGeForSuccess::ge(TestGeForSuccess const &b) const noexcept { return true; }

struct TestEqForFailure : Eq<TestEqForFailure> { constexpr bool eq(TestEqForFailure const &b) const noexcept; };
struct TestNeForFailure : Ne<TestNeForFailure> { constexpr bool ne(TestNeForFailure const &b) const noexcept; };
struct TestLtForFailure : Lt<TestLtForFailure> { constexpr bool lt(TestLtForFailure const &b) const noexcept; };
struct TestGtForFailure : Gt<TestGtForFailure> { constexpr bool gt(TestGtForFailure const &b) const noexcept; };
struct TestLeForFailure : Le<TestLeForFailure> { constexpr bool le(TestLeForFailure const &b) const noexcept; };
struct TestGeForFailure : Ge<TestGeForFailure> { constexpr bool ge(TestGeForFailure const &b) const noexcept; };

constexpr bool TestEqForFailure::eq(TestEqForFailure const &b) const noexcept { return false; }
constexpr bool TestNeForFailure::ne(TestNeForFailure const &b) const noexcept { return false; }
constexpr bool TestLtForFailure::lt(TestLtForFailure const &b) const noexcept { return false; }
constexpr bool TestGtForFailure::gt(TestGtForFailure const &b) const noexcept { return false; }
constexpr bool TestLeForFailure::le(TestLeForFailure const &b) const noexcept { return false; }
constexpr bool TestGeForFailure::ge(TestGeForFailure const &b) const noexcept { return false; }

struct TestComparable : Comparable<TestComparable>
{
	constexpr auto compare(TestComparable const &b) const noexcept
	{
		auto const cmp = val <=> b.val;

		return cmp < 0 ? comparison_r::lt :
		       cmp > 0 ? comparison_r::gt : comparison_r::eq;
	}

public:
	constexpr TestComparable(int val) noexcept : val(val)
	{
	}

private:
	int val;
};

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	try
	{
		if (!(TestEqForSuccess{} == TestEqForSuccess{})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestNeForSuccess{} != TestNeForSuccess{})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestLtForSuccess{} <  TestLtForSuccess{})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestGtForSuccess{} >  TestGtForSuccess{})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestLeForSuccess{} <= TestLeForSuccess{})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestGeForSuccess{} >= TestGeForSuccess{})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (!(TestComparable{1} == TestComparable{1})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestComparable{1} != TestComparable{0})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestComparable{0} <  TestComparable{1})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestComparable{1} >  TestComparable{0})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestComparable{0} <= TestComparable{1})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (!(TestComparable{1} >= TestComparable{0})) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));

		if (compare(TestComparable{1}, TestComparable{1}) != comparison_r::eq) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (compare(TestComparable{0}, TestComparable{1}) != comparison_r::lt) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		if (compare(TestComparable{1}, TestComparable{0}) != comparison_r::gt) throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
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