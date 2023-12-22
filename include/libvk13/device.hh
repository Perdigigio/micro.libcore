#include "driver.hh"

namespace micro::vk13
{
	using namespace micro::core::driver::video;

	//
	//

	class Device
	{
	public:
		Device(UniquePhysicalDevice const &) noexcept;

		HTEXTURE create_Texture(Usage u, Flags f, Texture1D const &d, Subresource1DArray a) noexcept;
		HTEXTURE create_Texture(Usage u, Flags f, Texture2D const &d, Subresource2DArray a) noexcept;
		HTEXTURE create_Texture(Usage u, Flags f, Texture3D const &d, Subresource3DArray a) noexcept;
		HTEXTURE create_Texture(Usage u, Flags f, TextureCM const &d, Subresource2DArray a) noexcept;
		HTEXTURE create_Texture(Usage u, Flags f, TextureMS const &d, Subresource2DArray a) noexcept;

		//! --------------------------------------------------------------------------- !//

		void update(HTEXTURE h, Level u, Layer v, Subresource1D d) noexcept;
		void update(HTEXTURE h, Level u, Layer v, Subresource2D d) noexcept;
		void update(HTEXTURE h, Level u, Layer v, Subresource3D d) noexcept;

		//! --------------------------------------------------------------------------- !//

		HCBUFFER create_CBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i) noexcept;
		HIBUFFER create_IBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i) noexcept;
		HSBUFFER create_SBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i) noexcept;
		HTBUFFER create_TBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i) noexcept;
		HVBUFFER create_VBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i) noexcept;

		//! --------------------------------------------------------------------------- !//

		void update(HCBUFFER h, BytesLength o, CByteBuffer d) noexcept;
		void update(HIBUFFER h, BytesLength o, CByteBuffer d) noexcept;
		void update(HSBUFFER h, BytesLength o, CByteBuffer d) noexcept;
		void update(HTBUFFER h, BytesLength o, CByteBuffer d) noexcept;
		void update(HVBUFFER h, BytesLength o, CByteBuffer d) noexcept;

		//! --------------------------------------------------------------------------- !//

		MByteBuffer map(HCBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept;
		MByteBuffer map(HIBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept;
		MByteBuffer map(HSBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept;
		MByteBuffer map(HTBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept;
		MByteBuffer map(HVBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept;

		void unmap(HCBUFFER h) noexcept;
		void unmap(HIBUFFER h) noexcept;
		void unmap(HSBUFFER h) noexcept;
		void unmap(HTBUFFER h) noexcept;
		void unmap(HVBUFFER h) noexcept;

		//! --------------------------------------------------------------------------- !//

		HGRAPHICPIPELINE create_GraphicPipeline(GraphicPipeline const &d) noexcept;
		HGRAPHICPIPELINE create_ComputePipeline(ComputePipeline const &d) noexcept;

		//! --------------------------------------------------------------------------- !//

		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture1D const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture2D const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureCM const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureMS const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture3D const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture1DArray const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture2DArray const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureMSArray const &v) noexcept;
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureCMArray const &v) noexcept;

		//! --------------------------------------------------------------------------- !//

		views::HCBUFFER create_CBufferView(HCBUFFER b, views::CBuffer const &v) noexcept;
		views::HIBUFFER create_IBufferView(HIBUFFER b, views::IBuffer const &v) noexcept;
		views::HSBUFFER create_SBufferView(HSBUFFER b, views::SBuffer const &v) noexcept;
		views::HTEXTURE create_TBufferView(HTBUFFER b, views::TBuffer const &v) noexcept;
		views::HVBUFFER create_VBufferView(HVBUFFER b, views::VBuffer const &v) noexcept;

		//! --------------------------------------------------------------------------- !//

		void dispose(HTEXTURE o) noexcept;
		void dispose(HCBUFFER o) noexcept;
		void dispose(HIBUFFER o) noexcept;
		void dispose(HSBUFFER o) noexcept;
		void dispose(HTBUFFER o) noexcept;
		void dispose(HVBUFFER o) noexcept;

		//! --------------------------------------------------------------------------- !//

		void dispose(HGRAPHICPIPELINE h) noexcept;
		void dispose(HCOMPUTEPIPELINE h) noexcept;

		//! --------------------------------------------------------------------------- !//

		void dispose(views::HTEXTURE o) noexcept;
		void dispose(views::HCBUFFER o) noexcept;
		void dispose(views::HFBUFFER o) noexcept;
		void dispose(views::HIBUFFER o) noexcept;
		void dispose(views::HSBUFFER o) noexcept;
		void dispose(views::HVBUFFER o) noexcept;
	private:
		UniquePhysicalDevice m_pdevice;
		UniqueAbstractDevice m_adevice;
	};
}