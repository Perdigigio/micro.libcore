#ifndef MICRO_LIBCORE_LIB_GRAPHIC_CUBEMAP_HH__GUARD
#define MICRO_LIBCORE_LIB_GRAPHIC_CUBEMAP_HH__GUARD

#include "texture.hh"

namespace micro::core::lib::graphic
{
	class Cubemap : public Texture
	{
	public:
		using Format = Texture::Format;
		using Extent = Texture::Extent;
		using Levels = Texture::Levels;
		using Layers = Texture::Layers;

		enum class Slices : u32
		{
			POSITIVE_X = 0,
			POSITIVE_Y = 1,
			POSITIVE_Z = 2,
			NEGATIVE_X = 3,
			NEGATIVE_Y = 4,
			NEGATIVE_Z = 5
		};

		using Index = std::tuple<Levels /** levels **/,
					 Layers /** layers **/,
					 Slices /** slices **/>;

		using Image = std::tuple<Index, Surface>;

	public:
		using Texture::Texture; 
	};

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto index(Cubemap::Image const &i) noexcept { return std::get<0>(i); }
	constexpr auto image(Cubemap::Image const &i) noexcept { return std::get<1>(i); }
	constexpr auto level(Cubemap::Index const &i) noexcept { return std::get<0>(i); }
	constexpr auto layer(Cubemap::Index const &i) noexcept { return std::get<1>(i); }
	constexpr auto slice(Cubemap::Index const &i) noexcept { return std::get<2>(i); }

	constexpr auto check_index(Cubemap const &t, Cubemap::Index const &i) noexcept
	{
		return level(i) < get_levels(t) &&
		       layer(i) < get_layers(t);
	}

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto cols(Cubemap::Extent e, Cubemap::Index i) noexcept { return cols(e, { level(i), layer(i) }); }
	constexpr auto rows(Cubemap::Extent e, Cubemap::Index i) noexcept { return rows(e, { level(i), layer(i) }); }

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto check_image(Cubemap const &t, Cubemap::Image const &i) noexcept
	{
		return cols(get_extent(t), index(i)) == cols(get_extent(image(i))) &&
		       rows(get_extent(t), index(i)) == rows(get_extent(image(i))) && check_index(t, index(i));
	}



} // namespace micro::core::lib


#endif