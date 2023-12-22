#ifndef MICRO_LIBCORE_LIB_RESULT_HH__GUARD
#define MICRO_LIBCORE_LIB_RESULT_HH__GUARD

#include <optional>
#include <utility>
#include <variant>

namespace micro::core::lib
{

	enum class error : int
	{
		//!
		//!
	};

	constexpr const error EUNKNOWN {0};
	constexpr const error EFAILURE {1};

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		using Result = std::variant<T, error>;

	template<class T>
		constexpr bool is_valid(Result<T> const &res) noexcept { return res.index() == 0; }
	template<class T>
		constexpr bool is_error(Result<T> const &res) noexcept { return res.index() == 1; }

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		using Option = std::optional<T>;

	constexpr auto const Nullopt = std::nullopt;
}

#endif //! MICRO_LIBCORE_LIB_RESULT_HH__GUARD