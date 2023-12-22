#ifndef MICRO_LIBCORE_LIB_LOGGER_HH__GUARD
#define MICRO_LIBCORE_LIB_LOGGER_HH__GUARD

#include "string.hh"

#define LIBCORE_LOGINFO(info) (::micro::core::lib::GlobalLogger::log_info((info), __func__))
#define LIBCORE_LOGWARN(info) (::micro::core::lib::GlobalLogger::log_warn((info), __func__))
#define LIBCORE_LOGFAIL(info) (::micro::core::lib::GlobalLogger::log_fail((info), __func__))

namespace micro::core::lib
{
	struct Logger
	{
		void (* log_info)(RString info, RString func) noexcept;
		void (* log_warn)(RString info, RString func) noexcept;
		void (* log_fail)(RString info, RString func) noexcept;
	};

	struct ANSILogger : public Logger
	{
		constexpr ANSILogger() noexcept : Logger{ANSILogger::info,
							 ANSILogger::warn,
							 ANSILogger::fail}
		{}

		///
		///

		static void info(RString info, RString func) noexcept;
		static void warn(RString info, RString func) noexcept;
		static void fail(RString info, RString func) noexcept;
	};

	struct TEXTLogger : public Logger
	{
		constexpr TEXTLogger() noexcept : Logger{TEXTLogger::info,
							 TEXTLogger::warn,
							 TEXTLogger::fail}
		{}

		///
		///

		static void info(RString info, RString func) noexcept;
		static void warn(RString info, RString func) noexcept;
		static void fail(RString info, RString func) noexcept;
	};

	struct VOIDLogger : public Logger
	{
		constexpr VOIDLogger() noexcept : Logger{VOIDLogger::info,
							 VOIDLogger::warn,
							 VOIDLogger::fail}
		{}

		static void info(RString info, RString func) noexcept {}
		static void warn(RString info, RString func) noexcept {}
		static void fail(RString info, RString func) noexcept {}
	};

	//! ----------------------------------------------------------------------------------- !//

	struct GlobalLogger
	{
		static Logger setup(Logger const &) noexcept;

		///
		///

		static void log_info(RString info, RString func) noexcept;
		static void log_warn(RString info, RString func) noexcept;
		static void log_fail(RString info, RString func) noexcept;
	};

} // namespace micro::core::lib

#endif