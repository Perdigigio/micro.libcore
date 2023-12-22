#include <libcore/io/mmap.hh>

namespace micro::core::lib::io
{
	class NixMmap : public Mmap
	{
	public:
		using Memory = MView::pointer;

	public:
		inline NixMmap(Memory data, Length size) noexcept :
			m_data{data},
			m_size{size}
		{}

		inline auto get_data() const noexcept { return m_data; }
		inline auto get_size() const noexcept { return m_size; }
		inline auto get_view() const noexcept;

		inline auto sync(Offset o = {}, Length l = std::dynamic_extent) const noexcept;

		virtual ~NixMmap() noexcept;
	private:
		Memory m_data;
		Length m_size;
	};

} // namespace micro::core::lib::io