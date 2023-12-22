#ifndef MICRO_LIBCORE_LIB_PANICS_HH__GUARD
#define MICRO_LIBCORE_LIB_PANICS_HH__GUARD

#include "string.hh"

#define LIBCORE_DOPANIC(info) (::micro::core::lib::dopanic((info), __FILE__, __LINE__))
#define LIBCORE_NOREACH(info) (::micro::core::lib::noreach((info), __FILE__, __LINE__))

#define LIBCORE_EXPECTS(cond) (!!(cond) ? (void)(0) : LIBCORE_DOPANIC("EXPECTS evaluated (" #cond ") not true"))
#define LIBCORE_ASSURES(cond) (!!(cond) ? (void)(0) : LIBCORE_DOPANIC("ASSURES evaluated (" #cond ") not true"))

namespace micro::core::lib
{

	[[noreturn]] void dopanic(RString msg, RString file, int line) noexcept;
	[[noreturn]] void noreach(RString msg, RString file, int line) noexcept;

} // namespace micro::core::lib

#endif