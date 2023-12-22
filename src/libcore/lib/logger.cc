#include <libcore/lib/logger.hh>
#include <libcore/lib/panics.hh>

#include <chrono>   /// system_clock
#include <iomanip>  /// setw, setfill
#include <iostream> /// clog
#include <tuple>    /// tuple

namespace micro::core::lib
{
	namespace details
	{
		using namespace std::chrono;

		inline auto now(std::ostream &o) -> std::ostream &
		{
			auto _time = system_clock::now().time_since_epoch();

			auto _h = duration_cast<hours>(_time) % 24;
			auto _m = duration_cast<minutes>(_time) % 60;
			auto _s = duration_cast<seconds>(_time) % 60;
			auto _f = duration_cast<microseconds>(_time) % 1'000'000;

			o << std::setw(2) << std::setfill('0') << _h.count() << ':'
			  << std::setw(2) << std::setfill('0') << _m.count() << ':'
			  << std::setw(2) << std::setfill('0') << _s.count() << '.'
			  << std::setw(6) << std::setfill('0') << _f.count();

			return o;
		}
	}

	//! ----------------------------------------------------------------------------------- !//

	thread_local static Logger _logger = {.log_info = TEXTLogger::info,
					      .log_warn = TEXTLogger::warn,
					      .log_fail = TEXTLogger::fail};


	///
	///

	void ANSILogger::info(RString info, RString func) noexcept { std::clog << "\033[1;46m[   INFO   ]\033[0m\033[1;36m[" << details::now << "][" << func << "] " << info << "\033[0m" << std::endl;  }
	void ANSILogger::warn(RString info, RString func) noexcept { std::clog << "\033[1;43m[   WARN   ]\033[0m\033[1;33m[" << details::now << "][" << func << "] " << info << "\033[0m" << std::endl;  }
	void ANSILogger::fail(RString info, RString func) noexcept { std::clog << "\033[1;41m[   FAIL   ]\033[0m\033[1;31m[" << details::now << "][" << func << "] " << info << "\033[0m" << std::endl;  }

	void TEXTLogger::info(RString info, RString func) noexcept { std::clog << "[   INFO   ][" << details::now << "][" << func << "] " << info << std::endl;  }
	void TEXTLogger::warn(RString info, RString func) noexcept { std::clog << "[   WARN   ][" << details::now << "][" << func << "] " << info << std::endl;  }
	void TEXTLogger::fail(RString info, RString func) noexcept { std::clog << "[   FAIL   ][" << details::now << "][" << func << "] " << info << std::endl;  }

	///
	///

	Logger GlobalLogger::setup(Logger const &logger) noexcept
	{
		LIBCORE_ASSURES(logger.log_info != nullptr);
		LIBCORE_ASSURES(logger.log_warn != nullptr);
		LIBCORE_ASSURES(logger.log_fail != nullptr);

		Logger _old {.log_info = std::exchange(_logger.log_info, logger.log_info),
			     .log_warn = std::exchange(_logger.log_warn, logger.log_warn),
			     .log_fail = std::exchange(_logger.log_fail, logger.log_fail)};

		return _old;
	}


	//! ----------------------------------------------------------------------------------- !//

	void GlobalLogger::log_info(RString info, RString func) noexcept { _logger.log_info(info, func); }
	void GlobalLogger::log_warn(RString info, RString func) noexcept { _logger.log_warn(info, func); }
	void GlobalLogger::log_fail(RString info, RString func) noexcept { _logger.log_fail(info, func); }

} // namespace micro::core::lib