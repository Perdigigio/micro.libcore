#ifndef MICRO_LIBCORE_LIB_GRAPHIC_IBUFFER_HH__GUARD
#define MICRO_LIBCORE_LIB_GRAPHIC_IBUFFER_HH__GUARD

#include <libcore/int.hh>
#include <libcore/lib.hh>

namespace micro::core::lib::graphic
{
	class IBuffer
	{
	public:
		enum class Offset : u32 {};
		enum class Length : u32 {};
		enum class Format : u32
		{
			UINT16 = sizeof(char[2]),
			UINT32 = sizeof(char[4])
		};

	public:
		constexpr IBuffer(Format format, Length length) noexcept :
			m_format{format},
			m_length{length}
		{}

		constexpr IBuffer() noexcept = default;

		//! --------------------------------------------------------------------------- !//

		constexpr Format get_format() const noexcept { return m_format; }
		constexpr Length get_length() const noexcept { return m_length; }

	private:
		Format m_format;
		Length m_length;
	};

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto get_format(IBuffer const &b) noexcept { return b.get_format(); }
	constexpr auto get_length(IBuffer const &b) noexcept { return b.get_length(); }

	///
	///

	constexpr auto size(IBuffer const &i) noexcept
	{
		return static_cast<size_t>(get_length(i)) *
		       static_cast<size_t>(get_format(i));
	}

} // namespace micro::core::lib


#endif