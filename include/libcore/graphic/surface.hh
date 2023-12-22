#ifndef MICRO_LIBCORE_LIB_GRAPHIC_SURFACE_HH__GUARD
#define MICRO_LIBCORE_LIB_GRAPHIC_SURFACE_HH__GUARD

#include <libcore/int.hh>
#include <libcore/lib.hh>

#include <tuple>

namespace micro::core::lib::graphic
{
	class Surface : public Eq<Surface>,
			public Ne<Surface>
	{
	public:
		enum class Format : u32
		{
			COLOR16x3,             /// UINT16 NORM B:5 G:6 R:5
			COLOR16x4,             /// UINT16 NORM B:5 G:5 R:5 A:1
			COLOR32x4,             /// UINT32 NORM B:8 G:8 R:8 A:8

			COMPRESSED_DXT1,       /// 4x4 3-channel
			COMPRESSED_DXT3,       /// 4x4 4-channel 4-bit alpha
			COMPRESSED_DXT5,       /// 4x4 4-channel 8-bit alpha
			COMPRESSED_ATI1,       /// 4x4 1-channel
			COMPRESSED_ATI2,       /// 4x4 2-channel
			COMPRESSED_BPTC_UNORM, /// 4x4 4-channel
			COMPRESSED_BPTC_FLOAT, /// 4x4 3-channel

			NORMAL32x2,            /// UINT32 NORM X:16 Y:16
			NORMAL32x3,            /// UINT32 NORM X:10 Y:10 Z:10 W:2

			HDR_FLOAT16,           /// FLOAT16[4]
			HDR_FLOAT32,           /// FLOAT32[4]

			DEPTH24_STENCIL8,      /// UINT32 D:24 S:8
			DEPTH32_STENCIL8,      /// UINT64 D:32 S:8
			DEPTH32,               /// UINT32 D:32

			DEPTH_STENCIL_MASK_R24_X8 = 0x8000'0001, /// MASK
			DEPTH_STENCIL_MASK_R32_X8 = 0x8000'0002, /// MASK
			DEPTH_STENCIL_MASK_X24_G8 = 0x8000'0003, /// MASK
			DEPTH_STENCIL_MASK_X32_G8 = 0x8000'0004, /// MASK
		};

		using Extent = std::tuple<u32 /** cols **/,
					  u32 /** rows **/>;
		using Stride = size_t;
		using Length = size_t;

	public:

		constexpr Surface(Format format, Extent extent, Length length, Stride stride) noexcept :
			m_format{format},
			m_extent{extent},
			m_length{length},
			m_stride{stride}
		{}

		constexpr Surface() noexcept = default;

		// ----------------------------------------------------------------------------- //

		constexpr auto get_format() const noexcept { return m_format; }
		constexpr auto get_extent() const noexcept { return m_extent; }
		constexpr auto get_length() const noexcept { return m_length; }
		constexpr auto get_stride() const noexcept { return m_stride; }

		// ----------------------------------------------------------------------------- //

		constexpr bool eq(Surface const &) const noexcept;
		constexpr bool ne(Surface const &) const noexcept;

	private:
		Format m_format = {};
		Extent m_extent = {};
		Length m_length = {};
		Stride m_stride = {};
	};

	//! ----------------------------------------------------------------------------------- !//

	constexpr bool Surface::eq(Surface const &s) const noexcept
	{
		return m_format == s.m_format &&
		       m_extent == s.m_extent &&
		       m_length == s.m_length &&
		       m_stride == s.m_stride;
	}

	constexpr bool Surface::ne(Surface const &s) const noexcept
	{
		return !Surface::eq(s);
	}

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto get_format(Surface const &s) noexcept { return s.get_format(); }
	constexpr auto get_extent(Surface const &s) noexcept { return s.get_extent(); }
	constexpr auto get_length(Surface const &s) noexcept { return s.get_length(); }
	constexpr auto get_stride(Surface const &s) noexcept { return s.get_stride(); }

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto rows(Surface::Extent const &e) noexcept { return std::get<0>(e); }
	constexpr auto cols(Surface::Extent const &e) noexcept { return std::get<1>(e); }
	constexpr auto area(Surface::Extent const &e) noexcept { return std::get<0>(e) * std::get<1>(e); }

	//! ----------------------------------------------------------------------------------- !//

	///
	///

	size_t size(Surface const &) noexcept;



} // namespace micro::core::lib


#endif