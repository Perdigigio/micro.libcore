#include <libcore/lib/panics.hh>
#include <libcore/lib/logger.hh>

#include <stdexcept>

namespace micro::core::lib
{
	namespace details
	{
		using __panic = std::runtime_error;
		using __reach = std::logic_error;

		inline LString format(LString kind, RString info, RString file, int line)
		{
			return cat("[   ", kind ,"  ][", file, ":", line, "] ", info);
		}

		[[noreturn]] inline void panic(RString info, RString file, int line) { throw __panic{format("PANIC", info, file, line)}; }
		[[noreturn]] inline void reach(RString info, RString file, int line) { throw __reach{format("REACH", info, file, line)}; }
	}

	void dopanic(RString info, RString file, int line) noexcept { details::panic(info, file, line); }
	void noreach(RString info, RString file, int line) noexcept { details::reach(info, file, line); }

} // namespace micro::core::lib