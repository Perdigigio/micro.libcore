#ifndef MICRO_LIBCORE_LIB_GRAPHIC_TEXTURE_HH__GUARD
#define MICRO_LIBCORE_LIB_GRAPHIC_TEXTURE_HH__GUARD

#include "surface.hh"

namespace micro::core::lib::graphic
{

	class Texture
	{
	public:
		using Format = Surface::Format;
		using Extent = Surface::Extent;
		using Levels = u32;
		using Layers = u32;

		using Index = std::tuple<Levels /** level **/,
					 Layers /** layer **/>;

		using Image = std::tuple<Index, Surface>;
	public:
		constexpr Texture(Format format, Extent extent, Levels levels, Layers layers) noexcept :
			m_format{format},
			m_extent{extent},
			m_levels{levels},
			m_layers{layers}
		{}

		constexpr Texture() noexcept = default;

		//! --------------------------------------------------------------------------- !//

		constexpr auto get_format() const noexcept { return m_format; }
		constexpr auto get_extent() const noexcept { return m_extent; }
		constexpr auto get_levels() const noexcept { return m_levels; }
		constexpr auto get_layers() const noexcept { return m_layers; }

	private:
		Format m_format;
		Extent m_extent;
		Levels m_levels;
		Layers m_layers;
	};

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto get_format(Texture const &t) noexcept { return t.get_format(); }
	constexpr auto get_extent(Texture const &t) noexcept { return t.get_extent(); }
	constexpr auto get_levels(Texture const &t) noexcept { return t.get_levels(); }
	constexpr auto get_layers(Texture const &t) noexcept { return t.get_layers(); }

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto index(Texture::Image const &i) noexcept { return std::get<0>(i); }
	constexpr auto image(Texture::Image const &i) noexcept { return std::get<1>(i); }
	constexpr auto level(Texture::Index const &i) noexcept { return std::get<0>(i); }
	constexpr auto layer(Texture::Index const &i) noexcept { return std::get<1>(i); }

	constexpr auto check_index(Texture const &t, Texture::Index const &i) noexcept
	{
		return level(i) < get_levels(t) &&
		       layer(i) < get_layers(t);
	}

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto cols(Texture::Extent e, Texture::Index i) noexcept { return max(1U, cols(e) >> level(i)); }
	constexpr auto rows(Texture::Extent e, Texture::Index i) noexcept { return max(1U, rows(e) >> level(i)); }

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto check_image(Texture const &t, Texture::Image const &i) noexcept
	{
		return cols(get_extent(t), index(i)) == cols(get_extent(image(i))) &&
		       rows(get_extent(t), index(i)) == rows(get_extent(image(i))) && check_index(t, index(i));
	}

} // namespace micro::core::lib


#endif