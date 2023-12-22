#include <libcore/io/file.hh>

namespace micro::core::lib::io
{
	class NixFile : public File
	{
	public:
		using Handle = int;

	public:
		inline NixFile(int handle) noexcept : m_handle{handle}
		{}

		//! --------------------------------------------------------------------------- !//

		static Handle get_handle(File::Unique const &) noexcept;
		static Handle get_handle(File::Shared const &) noexcept;

		//! --------------------------------------------------------------------------- !//

		inline Result get(MBufferView b, Offset o) const noexcept;
		inline Result put(CBufferView b, Offset o) const noexcept;

		//! --------------------------------------------------------------------------- !//

		inline void sync() const noexcept;

		//! --------------------------------------------------------------------------- !//

		virtual ~NixFile() noexcept;
	private:
		Handle m_handle;
	};

} // namespace micro::core::lib::io
