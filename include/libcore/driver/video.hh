#ifndef MICRO_CORE_LIB_DRIVER_VIDEO_HH__GUARD
#define MICRO_CORE_LIB_DRIVER_VIDEO_HH__GUARD

#include <libcore/lib.hh>
#include <libcore/lib/memory.hh>

#include <libcore/int.hh>

namespace micro::core::driver::video
{
	using HTEXTURE = struct TEXTURE_ *;
	using HCBUFFER = struct CBUFFER_ *;
	using HIBUFFER = struct IBUFFER_ *;
	using HSBUFFER = struct SBUFFER_ *;
	using HTBUFFER = struct TBUFFER_ *;
	using HVBUFFER = struct VBUFFER_ *;
	using HGRAPHICPIPELINE = struct GRAPHICPIPELINE_ *;
	using HCOMPUTEPIPELINE = struct COMPUTEPIPELINE_ *;

	//! ----------------------------------------------------------------------------------- !//

	enum class Format
	{
		UNKNOWN,

		R8G8B8A8,
		R8G8B8A8_UINT,
		R8G8B8A8_SINT,
		R8G8B8A8_UINT_NORMALIZED,
		R8G8B8A8_SINT_NORMALIZED,

		B8G8R8A8,
		B8G8R8A8_UINT,
		B8G8R8A8_SINT,
		B8G8R8A8_UINT_NORMALIZED,
		B8G8R8A8_SINT_NORMALIZED,

		R10G10B10A2,
		R10G10B10A2_UINT,
		R10G10B10A2_SINT,
		R10G10B10A2_UINT_NORMALIZED,
		R10G10B10A2_SINT_NORMALIZED,

		R16G16,
		R16G16_UINT,
		R16G16_SINT,
		R16G16_UINT_NORMALIZED,
		R16G16_SINT_NORMALIZED,
		R16G16_REAL,

		DEPTH_STENCIL_R24G8,
		DEPTH_STENCIL_R24X8,
		DEPTH_STENCIL_X24G8,
		DEPTH_STENCIL_D24S8,

		R32,
		R32_UINT,
		R32_SINT,
		R32_REAL,

		R16G16B16A16,
		R16G16B16A16_UINT,
		R16G16B16A16_SINT,
		R16G16B16A16_UINT_NORMALIZED,
		R16G16B16A16_SINT_NORMALIZED,
		R16G16B16A16_REAL,

		R32G32,
		R32G32_UINT,
		R32G32_SINT,
		R32G32_REAL,

		DEPTH_STENCIL_R32G8X24,
		DEPTH_STENCIL_R32X8X24,
		DEPTH_STENCIL_X32G8X24,
		DEPTH_STENCIL_D32S8X24,
		DEPTH_STENCIL_D32,

		R32G32B32,
		R32G32B32_UINT,
		R32G32B32_SINT,
		R32G32B32_REAL,

		R32G32B32A32,
		R32G32B32A32_UINT,
		R32G32B32A32_SINT,
		R32G32B32A32_REAL,

		COMPRESSED_S3TC_DXT1,
		COMPRESSED_S3TC_DXT3,
		COMPRESSED_S3TC_DXT5,
		COMPRESSED_RGTC_ATI1,
		COMPRESSED_RGTC_ATI2,
		COMPRESSED_BPTC_UF16,
		COMPRESSED_BPTC_SF16,
		COMPRESSED_BPTC_UINT_NORMALIZED,
	};

	enum class BytesLength : uintptr_t {};
	enum class UnitsLength : uintptr_t {};
	enum class Level : u32 {};
	enum class Layer : u32 {};
	enum class Slice : u32 {};

	enum class Levels : u32 {};
	enum class Layers : u32 {};
	enum class Texels : u32 {};
	enum class Slices : u32 {};
	enum class Stride : ptrdiff_t {};
	enum class Offset : ptrdiff_t {};
	enum class Length : ptrdiff_t {};

	//! ----------------------------------------------------------------------------------- !//

	namespace views
	{
		enum class HTEXTURE : u32 { EMPTY };
		enum class HCBUFFER : u32 { EMPTY };
		enum class HFBUFFER : u32 { EMPTY };
		enum class HIBUFFER : u32 { EMPTY };
		enum class HSBUFFER : u32 { EMPTY };
		enum class HVBUFFER : u32 { EMPTY };

		using LevelsSpan = NumericSpan<Level, Levels>;
		using LayersSpan = NumericSpan<Layer, Layers>;
		using SlicesSpan = NumericSpan<Slice, Slices>;

		using Texture2D = struct { Format format; LevelsSpan levels; };
		using Texture1D = struct { Format format; LevelsSpan levels; };
		using TextureCM = struct { Format format; LevelsSpan levels; };
		using Texture3D = struct { Format format; LevelsSpan levels; };
		using TextureMS = struct { Format format; };
		using Texture1DArray = struct { Format format; LevelsSpan levels; LayersSpan layers; };
		using Texture2DArray = struct { Format format; LevelsSpan levels; LayersSpan layers; };
		using TextureCMArray = struct { Format format; LevelsSpan levels; LayersSpan layers; };
		using TextureMSArray = struct { Format format; LayersSpan layers; };

		using BytesSpan = NumericSpan<BytesLength, u32>;
		using UnitsSpan = NumericSpan<UnitsLength, u32>;

		using CBuffer = struct { BytesSpan range; };
		using SBuffer = struct { BytesSpan range; };
		using IBuffer = struct { UnitsSpan range; Format format; };
		using TBuffer = struct { UnitsSpan range; Format format; };
		using VBuffer = struct { UnitsSpan range; Stride stride; };

		using FBuffer1D = struct { Format format; Level level; };
		using FBuffer2D = struct { Format format; Level level; };
		using FBuffer3D = struct { Format format; Level level; SlicesSpan slices; };
		using FBufferMS = struct { Format format; };
		using FBuffer1DArray = struct { Format format; Level level; LayersSpan layers; };
		using FBuffer2DArray = struct { Format format; Level level; LayersSpan layers; };
		using FBufferMSArray = struct { Format format; LayersSpan layers; };
	}

	//! ----------------------------------------------------------------------------------- !//

	using Extent1D = std::array<Texels, 1>;
	using Extent2D = std::array<Texels, 2>;
	using Extent3D = std::array<Texels, 3>;

	constexpr auto get_w(Extent1D const &e) noexcept { return std::get<0>(e); }
	constexpr auto get_w(Extent2D const &e) noexcept { return std::get<0>(e); }
	constexpr auto get_w(Extent3D const &e) noexcept { return std::get<0>(e); }
	constexpr auto get_h(Extent2D const &e) noexcept { return std::get<1>(e); }
	constexpr auto get_h(Extent3D const &e) noexcept { return std::get<1>(e); }
	constexpr auto get_d(Extent3D const &e) noexcept { return std::get<2>(e); }

	using Texture1D = struct { Format format; Extent1D extent; Layers layers; Levels levels; };
	using Texture2D = struct { Format format; Extent2D extent; Layers layers; Levels levels; };
	using Texture3D = struct { Format format; Extent3D extent; Levels levels; };
	using TextureCM = struct { Format format; Extent2D extent; Layers layers; Levels levels; };
	using TextureMS = struct { Format format; Extent2D extent; Layers layers; };

	//! ----------------------------------------------------------------------------------- !//

	using CByteBuffer = lib::CBufferView;
	using MByteBuffer = lib::MBufferView;

	//! ----------------------------------------------------------------------------------- !//

	using Subresource1D = struct { CByteBuffer data; };
	using Subresource2D = struct { CByteBuffer data; Stride rstride; };
	using Subresource3D = struct { CByteBuffer data; Stride rstride; Stride dstride; };

	using Subresource1DArray = std::span<Subresource1D>;
	using Subresource2DArray = std::span<Subresource2D>;
	using Subresource3DArray = std::span<Subresource3D>;

	//! ----------------------------------------------------------------------------------- !//

	using AttribName = std::span<char>;
	using AttribSlot = u32;
	using BufferSlot = u32;

	struct AttribConfig
	{
		AttribName attrib_name;
		AttribSlot attrib_slot;
		BufferSlot buffer_slot;

		Format format;
		Offset offset;
	};

	using VertexConfig = std::span<AttribConfig>;

	//! ----------------------------------------------------------------------------------- !//

	struct GraphicPipeline
	{
		CByteBuffer vshader;
		CByteBuffer hshader;
		CByteBuffer tshader;
		CByteBuffer gshader;
		CByteBuffer fshader;

		VertexConfig vconfig;
	};

	struct ComputePipeline
	{
		CByteBuffer cshader;
	};

	//! ----------------------------------------------------------------------------------- !//


	enum class Usage
	{
		DEFAULT,
		DYNAMIC,
		STAGING,
	};

	enum class Flags : u32 { EMPTY };

	constexpr auto operator |(Flags a, Flags b) noexcept { return Flags{ static_cast<u32>(a) | static_cast<u32>(b) }; }
	constexpr auto operator &(Flags a, Flags b) noexcept { return Flags{ static_cast<u32>(a) & static_cast<u32>(b) }; }

	struct FLAGS
	{
		static constexpr Flags CREATE_MAPPABLE_R { 001 };
		static constexpr Flags CREATE_MAPPABLE_W { 002 };
		static constexpr Flags CREATE_MAPPABLE_PERSISTENT { 004 };

		static constexpr Flags MAP_R { 001 };
		static constexpr Flags MAP_W { 002 };
		static constexpr Flags MAP_PERSISTENT { 004 };
		static constexpr Flags MAP_INVALIDATE { 010 };
		static constexpr Flags MAP_INVALIDATE_RANGE { 020 };

		static constexpr Flags BIND_RENDER_TARGET_COLOR { 001 };
		static constexpr Flags BIND_RENDER_TARGET_DEPTH { 002 };
		static constexpr Flags BIND_SHADER_SOURCE { 004 };
	};

	template<class T>
	struct Device
	{
		HTEXTURE create_Texture(Usage u, Flags f, Texture1D const &d, Subresource1DArray a = {}) noexcept { return upcast(this)->create_Texture(u, f, d, a); }
		HTEXTURE create_Texture(Usage u, Flags f, Texture2D const &d, Subresource2DArray a = {}) noexcept { return upcast(this)->create_Texture(u, f, d, a); }
		HTEXTURE create_Texture(Usage u, Flags f, Texture3D const &d, Subresource3DArray a = {}) noexcept { return upcast(this)->create_Texture(u, f, d, a); }
		HTEXTURE create_Texture(Usage u, Flags f, TextureCM const &d, Subresource2DArray a = {}) noexcept { return upcast(this)->create_Texture(u, f, d, a); }
		HTEXTURE create_Texture(Usage u, Flags f, TextureMS const &d, Subresource2DArray a = {}) noexcept { return upcast(this)->create_Texture(u, f, d, a); }

		//! --------------------------------------------------------------------------- !//

		void update(HTEXTURE h, Level u, Layer v, Subresource1D d) noexcept { upcast(this)->update(h, u, v, d); }
		void update(HTEXTURE h, Level u, Layer v, Subresource2D d) noexcept { upcast(this)->update(h, u, v, d); }
		void update(HTEXTURE h, Level u, Layer v, Subresource3D d) noexcept { upcast(this)->update(h, u, v, d); }

		//! --------------------------------------------------------------------------- !//

		HCBUFFER create_CBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i = {}) noexcept { return upcast(this)->create_CBuffer(u, f, l, i); }
		HIBUFFER create_IBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i = {}) noexcept { return upcast(this)->create_IBuffer(u, f, l, i); }
		HSBUFFER create_SBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i = {}) noexcept { return upcast(this)->create_SBuffer(u, f, l, i); }
		HTBUFFER create_TBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i = {}) noexcept { return upcast(this)->create_TBuffer(u, f, l, i); }
		HVBUFFER create_VBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i = {}) noexcept { return upcast(this)->create_VBuffer(u, f, l, i); }

		//! --------------------------------------------------------------------------- !//

		void update(HCBUFFER h, BytesLength o, CByteBuffer d) noexcept { upcast(this)->update(h, o, d); }
		void update(HIBUFFER h, BytesLength o, CByteBuffer d) noexcept { upcast(this)->update(h, o, d); }
		void update(HSBUFFER h, BytesLength o, CByteBuffer d) noexcept { upcast(this)->update(h, o, d); }
		void update(HTBUFFER h, BytesLength o, CByteBuffer d) noexcept { upcast(this)->update(h, o, d); }
		void update(HVBUFFER h, BytesLength o, CByteBuffer d) noexcept { upcast(this)->update(h, o, d); }

		//! --------------------------------------------------------------------------- !//

		MByteBuffer map(HCBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept { return upcast(this)->map(h, f, o, l); }
		MByteBuffer map(HIBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept { return upcast(this)->map(h, f, o, l); }
		MByteBuffer map(HSBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept { return upcast(this)->map(h, f, o, l); }
		MByteBuffer map(HTBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept { return upcast(this)->map(h, f, o, l); }
		MByteBuffer map(HVBUFFER h, Flags f, BytesLength o, BytesLength l) noexcept { return upcast(this)->map(h, f, o, l); }

		void unmap(HCBUFFER h) noexcept { return upcast(this)->unmap(h); }
		void unmap(HIBUFFER h) noexcept { return upcast(this)->unmap(h); }
		void unmap(HSBUFFER h) noexcept { return upcast(this)->unmap(h); }
		void unmap(HTBUFFER h) noexcept { return upcast(this)->unmap(h); }
		void unmap(HVBUFFER h) noexcept { return upcast(this)->unmap(h); }

		//! --------------------------------------------------------------------------- !//

		HGRAPHICPIPELINE create_GraphicPipeline(GraphicPipeline const &d) noexcept { return upcast(this)->create_GraphicPipeline(d); }
		HGRAPHICPIPELINE create_ComputePipeline(ComputePipeline const &d) noexcept { return upcast(this)->create_ComputePipeline(d); }

		//! --------------------------------------------------------------------------- !//

		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture1D const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture2D const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureCM const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureMS const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture3D const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture1DArray const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::Texture2DArray const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureMSArray const &v) noexcept { return upcast(this)->create_TextureView(t, v); }
		views::HTEXTURE create_TextureView(HTEXTURE t, views::TextureCMArray const &v) noexcept { return upcast(this)->create_TextureView(t, v); }

		//! --------------------------------------------------------------------------- !//

		views::HCBUFFER create_CBufferView(HCBUFFER b, views::CBuffer const &v) noexcept { return upcast(this)->create_CBufferView(b, v); }
		views::HIBUFFER create_IBufferView(HIBUFFER b, views::IBuffer const &v) noexcept { return upcast(this)->create_IBufferView(b, v); }
		views::HSBUFFER create_SBufferView(HSBUFFER b, views::SBuffer const &v) noexcept { return upcast(this)->create_SBufferView(b, v); }
		views::HTEXTURE create_TBufferView(HTBUFFER b, views::TBuffer const &v) noexcept { return upcast(this)->create_TBufferView(b, v); }
		views::HVBUFFER create_VBufferView(HVBUFFER b, views::VBuffer const &v) noexcept { return upcast(this)->create_VBufferView(b, v); }

		//! --------------------------------------------------------------------------- !//

		void dispose(HTEXTURE o) noexcept { upcast(this)->dispose(o); }
		void dispose(HCBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(HIBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(HSBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(HTBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(HVBUFFER o) noexcept { upcast(this)->dispose(o); }

		//! --------------------------------------------------------------------------- !//

		void dispose(HGRAPHICPIPELINE h) noexcept { upcast(this)->dispose(h); }
		void dispose(HCOMPUTEPIPELINE h) noexcept { upcast(this)->dispose(h); }

		//! --------------------------------------------------------------------------- !//

		void dispose(views::HTEXTURE o) noexcept { upcast(this)->dispose(o); }
		void dispose(views::HCBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(views::HFBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(views::HIBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(views::HSBUFFER o) noexcept { upcast(this)->dispose(o); }
		void dispose(views::HVBUFFER o) noexcept { upcast(this)->dispose(o); }
	};

	enum class CBUFFER_SLOT : u32 {};
	enum class SBUFFER_SLOT : u32 {};
	enum class TEXTURE_SLOT : u32 {};
	enum class VBUFFER_SLOT : u32 {};

	template<class T>
	struct DeviceContext
	{
		void bind(HGRAPHICPIPELINE h) noexcept { upcast(this)->bind(h); }
		void bind(HCOMPUTEPIPELINE h) noexcept { upcast(this)->bind(h); }

		//! --------------------------------------------------------------------------- !//

		void bind(CBUFFER_SLOT s, views::HCBUFFER h) noexcept { upcast(this)->bind(s, h); }
		void bind(SBUFFER_SLOT s, views::HSBUFFER h) noexcept { upcast(this)->bind(s, h); }
		void bind(TEXTURE_SLOT s, views::HTEXTURE h) noexcept { upcast(this)->bind(s, h); }
		void bind(VBUFFER_SLOT s, views::HVBUFFER h) noexcept { upcast(this)->bind(s, h); }

		//! --------------------------------------------------------------------------- !//

		void bind(views::HFBUFFER h) noexcept { upcast(this)->bind(h); }
		void bind(views::HIBUFFER h) noexcept { upcast(this)->bind(h); }

		//! --------------------------------------------------------------------------- !//

		void draw(UnitsLength );
		
	};
}

#endif