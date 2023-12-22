#ifndef MICRO_LIBCORE_LIB_IO_FILE_HH__GUARD
#define MICRO_LIBCORE_LIB_IO_FILE_HH__GUARD

#include <libcore/lib.hh>
#include <libcore/int.hh>
#include <libcore/lib/memory.hh>
#include <libcore/lib/result.hh>
#include <libcore/lib/future.hh>

#include <filesystem>

namespace micro::core::lib::io
{
	using Path = std::filesystem::path;

	using lib::MBufferView;
	using lib::CBufferView;

	struct File
	{
	public:
		using Result = Option<CBufferView>;
		using Offset = u64;
		using Length = u64;
		using Unique = std::unique_ptr<File>;
		using Shared = std::shared_ptr<File>;

	public:
		static Unique open_r(Path const &) noexcept;
		static Unique open_w(Path const &) noexcept;

		//! --------------------------------------------------------------------------- !//

		static Result get(Unique const &h, MBufferView b, Offset o) noexcept;
		static Result put(Unique const &h, CBufferView b, Offset o) noexcept;
		static Result get(Shared const &h, MBufferView b, Offset o) noexcept;
		static Result put(Shared const &h, CBufferView b, Offset o) noexcept;

		[[nodiscard]] static Future<Result> get_async(Shared const &h, MBufferView b, Offset o) noexcept;
		[[nodiscard]] static Future<Result> put_async(Shared const &h, CBufferView b, Offset o) noexcept;

		//! --------------------------------------------------------------------------- !//

		static void sync(File::Unique const &) noexcept;
		static void sync(File::Shared const &) noexcept;

		//! --------------------------------------------------------------------------- !//

		virtual ~File() noexcept = default;
	};

} // namespace micro::core::lib::io


#endif