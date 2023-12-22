#include "file_nix.hh"

#include <fcntl.h>
#include <unistd.h>

namespace micro::core::lib::io
{
	static constexpr auto const R_MODE = O_RDONLY;
	static constexpr auto const W_MODE = O_RDWR | O_CREAT;

	static constexpr auto const C_MODE = S_IRUSR | S_IWUSR |
					     S_IRGRP | S_IWGRP |
					     S_IROTH | S_IWOTH;

	//! ----------------------------------------------------------------------------------- !//

	inline auto result(ssize_t r, CBufferView b) noexcept -> File::Result { return r > 0 ? File::Result{b.subspan(0, static_cast<size_t>(r))} : Nullopt; }

	inline auto file(File::Unique const &f) noexcept { return static_cast<NixFile const *>(f.get()); }
	inline auto file(File::Shared const &f) noexcept { return static_cast<NixFile const *>(f.get()); }

	inline auto get_buffer(File::Shared f, MBufferView b, File::Offset o) noexcept { return file(f)->get(b, o); }
	inline auto put_buffer(File::Shared f, CBufferView b, File::Offset o) noexcept { return file(f)->put(b, o); }

	//! ----------------------------------------------------------------------------------- !//

	NixFile::Handle NixFile::get_handle(File::Unique const &f) noexcept { return file(f)->m_handle; }
	NixFile::Handle NixFile::get_handle(File::Shared const &f) noexcept { return file(f)->m_handle; }

	//!
	//!

	File::Result NixFile::get(MBufferView b, Offset o) const noexcept
	{
		using std::data;
		using std::size;

		return result(pread(m_handle, data(b), size(b), o), b);
	}

	File::Result NixFile::put(CBufferView b, Offset o) const noexcept
	{
		using std::data;
		using std::size;

		return result(pwrite(m_handle, data(b), size(b), o), b);
	}

	void NixFile::sync() const noexcept
	{
		fsync(m_handle);
	}

	NixFile::~NixFile() noexcept
	{
		close(m_handle);
	}

	//! ----------------------------------------------------------------------------------- !//

	inline File::Unique wrap_file(int file) noexcept
	{
		return file != NixFile::Handle{-1} ? std::make_unique<NixFile>(file) : nullptr;
	}

	//! ----------------------------------------------------------------------------------- !//

	File::Unique File::open_r(Path const &p) noexcept { return wrap_file(open(p.c_str(), R_MODE)); }
	File::Unique File::open_w(Path const &p) noexcept { return wrap_file(open(p.c_str(), W_MODE,
											     C_MODE)); }

	//! ----------------------------------------------------------------------------------- !//

	File::Result File::get(Unique const &h, MBufferView b, Offset o) noexcept { return file(h)->get(b, o); }
	File::Result File::put(Unique const &h, CBufferView b, Offset o) noexcept { return file(h)->put(b, o); }
	File::Result File::get(Shared const &h, MBufferView b, Offset o) noexcept { return file(h)->get(b, o); }
	File::Result File::put(Shared const &h, CBufferView b, Offset o) noexcept { return file(h)->put(b, o); }

	Future<File::Result> File::get_async(Shared const &h, MBufferView b, Offset o) noexcept { return async(get_buffer, h, b, o); }
	Future<File::Result> File::put_async(Shared const &h, CBufferView b, Offset o) noexcept { return async(put_buffer, h, b, o); }

	//! ----------------------------------------------------------------------------------- !//

	void File::sync(File::Unique const &f) noexcept { file(f)->sync(); }
	void File::sync(File::Shared const &f) noexcept { file(f)->sync(); }

	//! ----------------------------------------------------------------------------------- !//



} // namespace micro::core::lib::io
