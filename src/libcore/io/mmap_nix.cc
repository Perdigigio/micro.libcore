#include "mmap_nix.hh"
#include "file_nix.hh"

#include <sys/mman.h>

namespace micro::core::lib::io
{

	static constexpr auto const MAP_R = PROT_READ;
	static constexpr auto const MAP_W = PROT_READ | PROT_WRITE;

	//! ----------------------------------------------------------------------------------- !//

	auto NixMmap::get_view() const noexcept
	{
		return MView{m_data, m_size};
	}

	auto NixMmap::sync(Offset o, Length l) const noexcept
	{
		if (auto view = get_view().subspan(o, l); !std::empty(view))
		{
			msync(std::data(view),
			      std::size(view), MS_ASYNC | MS_INVALIDATE);
		}
	}


	NixMmap::~NixMmap() noexcept
	{
		munmap(m_data, m_size);
	}

	inline auto mmap(Mmap::Unique const &p) noexcept { return static_cast<NixMmap const *>(p.get()); }
	inline auto mmap(Mmap::Shared const &p) noexcept { return static_cast<NixMmap const *>(p.get()); }
	inline auto mmap(File::Unique const &f, int p, size_t l, off_t o) noexcept { return static_cast<NixMmap::Memory>(::mmap(NULL, l, p, MAP_SHARED, NixFile::get_handle(f), o)); }
	inline auto mmap(File::Shared const &f, int p, size_t l, off_t o) noexcept { return static_cast<NixMmap::Memory>(::mmap(NULL, l, p, MAP_SHARED, NixFile::get_handle(f), o)); }

	//! ----------------------------------------------------------------------------------- !//

	inline Mmap::Unique wrap_mmap(NixMmap::Memory m, NixMmap::Length l) noexcept
	{
		return  m != MAP_FAILED ? std::make_unique<NixMmap>(m, l) : nullptr;
	}

	//! ----------------------------------------------------------------------------------- !//

	Mmap::Unique Mmap::open_r(File::Unique const &f, Length l, File::Offset o) noexcept { return wrap_mmap(mmap(f, MAP_R, l, o), l); }
	Mmap::Unique Mmap::open_w(File::Unique const &f, Length l, File::Offset o) noexcept { return wrap_mmap(mmap(f, MAP_W, l, o), l); }
	Mmap::Unique Mmap::open_r(File::Shared const &f, Length l, File::Offset o) noexcept { return wrap_mmap(mmap(f, MAP_R, l, o), l); }
	Mmap::Unique Mmap::open_w(File::Shared const &f, Length l, File::Offset o) noexcept { return wrap_mmap(mmap(f, MAP_W, l, o), l); }

	//! ----------------------------------------------------------------------------------- !//

	Mmap::MView Mmap::view(Unique const &p) noexcept { return mmap(p)->get_view(); }
	Mmap::MView Mmap::view(Shared const &p) noexcept { return mmap(p)->get_view(); }

	//! ----------------------------------------------------------------------------------- !//

	void Mmap::sync(Unique const &m) noexcept { mmap(m)->sync(); }
	void Mmap::sync(Shared const &m) noexcept { mmap(m)->sync(); }
	void Mmap::sync(Unique const &m, Offset o, Length l) noexcept { mmap(m)->sync(o, l); }
	void Mmap::sync(Shared const &m, Offset o, Length l) noexcept { mmap(m)->sync(o, l); }

} // namespace micro::core::lib::io