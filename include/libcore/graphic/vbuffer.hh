#ifndef MICRO_LIBCORE_LIB_GRAPHIC_VBUFFER_HH__GUARD
#define MICRO_LIBCORE_LIB_GRAPHIC_VBUFFER_HH__GUARD

#include <libcore/int.hh>
#include <libcore/lib.hh>

namespace micro::core::lib::graphic
{
	class VBuffer
	{
	public:
		enum class Format : u32
		{
			FLOAT16x2, //! FLOAT16[2]
			FLOAT16x4, //! FLOAT16[4]
			FLOAT32x1, //! FLOAT32[1]
			FLOAT32x2, //! FLOAT32[2]
			FLOAT32x3, //! FLOAT32[3]
			FLOAT32x4, //! FLOAT32[4]
			COLOR32_UNORM, //! [+0, 1] BYTE[4]
			COLOR32_SNORM, //! [-1, 1] BYTE[4]
			UINT16x2, //! UINT16[2]
			UINT16x4, //! UINT16[4]
			SINT16x2, //! SINT16[2]
			SINT16x4, //! SINT16[4]
			UINT16x2_UNORM, //! [+0, 1] UINT16[2]
			UINT16x4_UNORM, //! [+0, 1] UINT16[4]
			SINT16x2_SNORM, //! [-1, 1] UINT16[2]
			SINT16x4_SNORM, //! [-1, 1] UINT16[4]
			UINT32x1, //! UINT32[1]
			UINT32x2, //! UINT32[2]
			UINT32x3, //! UINT32[3]
			UINT32x4, //! UINT32[4]
			SINT32x1, //! UINT32[1]
			SINT32x2, //! SINT32[2]
			SINT32x3, //! SINT32[3]
			SINT32x4, //! SINT32[4]
		};

		enum class Attrib : u32
		{
			POSITION_1,
			POSITION_2,
			POSITION_3,

			PER_VERTEX_NORMAL_1,
			PER_VERTEX_NORMAL_2,
			PER_VERTEX_NORMAL_3,

			TEXCOORD_1,
			TEXCOORD_2,
			TEXCOORD_3,
			TEXCOORD_4,
			TEXCOORD_5,
			TEXCOORD_6,
			TEXCOORD_7,
			TEXCOORD_8,

			PER_VERTEX_COLOR_1,
			PER_VERTEX_COLOR_2,
			PER_VERTEX_COLOR_3,

			BLEND_WEIGHTS,
			BLEND_INDICES,

			GENERIC_ATTRIB_1,
			GENERIC_ATTRIB_2,
			GENERIC_ATTRIB_3,
			GENERIC_ATTRIB_4
		};

		using Length = size_t;
		using Offset = size_t;

	public:
		constexpr VBuffer(Attrib attrib, Format format, Length length, Offset offset) noexcept :
			m_attrib{attrib},
			m_format{format},
			m_length{length},
			m_offset{offset}
		{}

		constexpr VBuffer() noexcept = default;

		//! --------------------------------------------------------------------------- !//

		constexpr auto get_attrib() const noexcept { return m_attrib; }
		constexpr auto get_format() const noexcept { return m_format; }
		constexpr auto get_length() const noexcept { return m_length; }
		constexpr auto get_offset() const noexcept { return m_offset; }

	private:
		Attrib m_attrib = {};
		Format m_format = {};
		Length m_length = {};
		Offset m_offset = {};
	};

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto get_attrib(VBuffer const &b) noexcept { return b.get_attrib(); }
	constexpr auto get_format(VBuffer const &b) noexcept { return b.get_format(); }
	constexpr auto get_length(VBuffer const &b) noexcept { return b.get_length(); }
	constexpr auto get_offset(VBuffer const &b) noexcept { return b.get_offset(); }

} // namespace micro::core::lib


#endif