#include <libcore/graphic/surface.hh>

namespace micro::core::lib::graphic
{
	static size_t calc_bm16(Surface const &s) noexcept;
	static size_t calc_bm32(Surface const &s) noexcept;
	static size_t calc_bptc(Surface const &s) noexcept;
	static size_t calc_rgtc(Surface const &s) noexcept;
	static size_t calc_fp16(Surface const &s) noexcept;
	static size_t calc_fp32(Surface const &s) noexcept;

	//! ----------------------------------------------------------------------------------- !//

	size_t size(Surface const &s) noexcept
	{
		switch (get_format(s))
		{
		case Surface::Format::COLOR16x3: return calc_bm16(s);
		case Surface::Format::COLOR16x4: return calc_bm16(s);
		case Surface::Format::COLOR32x4: return calc_bm32(s);
		case Surface::Format::COMPRESSED_DXT1: return calc_bptc(s);
		case Surface::Format::COMPRESSED_DXT3: return calc_bptc(s);
		case Surface::Format::COMPRESSED_DXT5: return calc_bptc(s);
		case Surface::Format::COMPRESSED_ATI1: return calc_rgtc(s);
		case Surface::Format::COMPRESSED_ATI2: return calc_rgtc(s);
		case Surface::Format::COMPRESSED_BPTC_UNORM: return calc_bptc(s);
		case Surface::Format::COMPRESSED_BPTC_FLOAT: return calc_bptc(s);
		case Surface::Format::NORMAL32x2:  return calc_bm32(s);
		case Surface::Format::NORMAL32x3:  return calc_bm32(s);
		case Surface::Format::HDR_FLOAT16: return calc_fp16(s);
		case Surface::Format::HDR_FLOAT32: return calc_fp32(s);
		}

		return 0;
	}

	static size_t calc_bm16(Surface const &s) noexcept { return area(get_extent(s)) * sizeof(char[2]); }
	static size_t calc_bm32(Surface const &s) noexcept { return area(get_extent(s)) * sizeof(char[4]); }
	static size_t calc_fp16(Surface const &s) noexcept { return 4U * calc_bm16(s); }
	static size_t calc_fp32(Surface const &s) noexcept { return 4U * calc_bm32(s); }

	static size_t calc_bptc(Surface const &s) noexcept
	{
		auto u = max(1U, (cols(get_extent(s)) + 3U) / 4U);
		auto v = max(1U, (rows(get_extent(s)) + 3U) / 4U);

		return get_format(s) == Surface::Format::COMPRESSED_DXT1 ? u * v * u32{010} :
									   u * v * u32{020};
	}

	static size_t calc_rgtc(Surface const &s) noexcept
	{
		auto u = max(1U, (cols(get_extent(s)) + 3U) / 4U);
		auto v = max(1U, (rows(get_extent(s)) + 3U) / 4U);

		return get_format(s) == Surface::Format::COMPRESSED_ATI1 ? u * v * u32{010} :
									   u * v * u32{020};
	}


}