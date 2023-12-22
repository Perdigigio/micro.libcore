#ifndef MICRO_LIBCORE_LIB_IO_MMAP_HH__GUARD
#define MICRO_LIBCORE_LIB_IO_MMAP_HH__GUARD

#include "file.hh"

namespace micro::core::lib::io
{

	class Mmap
	{
	public:
		using MView = MBufferView;
		using CView = CBufferView;

		using Offset = size_t;
		using Length = size_t;
		using Shared = std::shared_ptr<Mmap>;
		using Unique = std::unique_ptr<Mmap>;

	public:
		static Unique open_r(File::Unique const &f, Mmap::Length l, File::Offset o) noexcept;
		static Unique open_w(File::Unique const &f, Mmap::Length l, File::Offset o) noexcept;
		static Unique open_r(File::Shared const &f, Mmap::Length l, File::Offset o) noexcept;
		static Unique open_w(File::Shared const &f, Mmap::Length l, File::Offset o) noexcept;

		//! --------------------------------------------------------------------------- !//

		static MView view(Unique const &) noexcept;
		static MView view(Shared const &) noexcept;

		//! --------------------------------------------------------------------------- !//

		static void sync(Unique const &) noexcept;
		static void sync(Shared const &) noexcept;
		static void sync(Unique const &, Offset, Length = std::dynamic_extent) noexcept;
		static void sync(Shared const &, Offset, Length = std::dynamic_extent) noexcept;

		//! --------------------------------------------------------------------------- !//

		virtual ~Mmap() noexcept = default;
	};

	//! ----------------------------------------------------------------------------------- !//

	inline Mmap::MView mview(Mmap::Unique const &m) noexcept { return Mmap::view(m); }
	inline Mmap::CView cview(Mmap::Unique const &m) noexcept { return Mmap::view(m); }
	inline Mmap::MView mview(Mmap::Shared const &m) noexcept { return Mmap::view(m); }
	inline Mmap::CView cview(Mmap::Shared const &m) noexcept { return Mmap::view(m); }

	inline auto mview(Mmap::Unique const &m, Mmap::Offset o, Mmap::Length l = std::dynamic_extent) noexcept { return mview(m).subspan(o, l); }
	inline auto cview(Mmap::Unique const &m, Mmap::Offset o, Mmap::Length l = std::dynamic_extent) noexcept { return cview(m).subspan(o, l); }
	inline auto mview(Mmap::Shared const &m, Mmap::Offset o, Mmap::Length l = std::dynamic_extent) noexcept { return mview(m).subspan(o, l); }
	inline auto cview(Mmap::Shared const &m, Mmap::Offset o, Mmap::Length l = std::dynamic_extent) noexcept { return cview(m).subspan(o, l); }

	//! ----------------------------------------------------------------------------------- !//

	inline auto data(Mmap::Unique const &m) noexcept { return std::data(Mmap::view(m)); }
	inline auto data(Mmap::Shared const &m) noexcept { return std::data(Mmap::view(m)); }
	inline auto size(Mmap::Unique const &m) noexcept { return std::size(Mmap::view(m)); }
	inline auto size(Mmap::Shared const &m) noexcept { return std::size(Mmap::view(m)); }

} // namespace micro::core::lib::io


#endif