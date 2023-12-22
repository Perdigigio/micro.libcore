#ifndef MICRO_LIBCORE_LIB_FUTURE_HH__GUARD
#define MICRO_LIBCORE_LIB_FUTURE_HH__GUARD

#include <functional>
#include <future>

namespace micro::core::lib
{
	using std::async;

	template<class T>
		using Future = std::future<T>;

}

#endif //! MICRO_LIBCORE_LIB_FUTURE_HH__GUARD