#ifndef MICRO_VK13_DEVICE_RBUFFER_HH__GUARD_SRC
#define MICRO_VK13_DEVICE_RBUFFER_HH__GUARD_SRC

#include <libcore/driver/video.hh>

//! ------------------------------------------------------------------------------------------- !//

namespace micro::core::driver::video
{
	/// Dummy types for Handles
	///

	struct CBUFFER_ {};
	struct IBUFFER_ {};
	struct SBUFFER_ {};
	struct VBUFFER_ {};
	struct TBUFFER_ {};
}

//! ------------------------------------------------------------------------------------------- !//

#include "abstract_device.hh"

//! ------------------------------------------------------------------------------------------- !//

namespace micro::vk13
{
	using namespace micro::core::driver::video;

	///
	///

	namespace details
	{
		using volk::VkResult;
		using volk::VkBuffer;
		using volk::VkBufferCreateInfo;
		using volk::VkBufferUsageFlags;
		using volk::VkDeviceSize;
		using volk::VkDeviceMemory;
		using volk::VkMemoryAllocateInfo;

		struct CBufferState
		{
			VkBuffer             handle;
			VkDeviceMemory       memory;
			VkMemoryRequirements requirements;
			VkFlags              properties;
		};
	}

	///
	///

	class RBuffer : public CBUFFER_,
			public IBUFFER_,
			public SBUFFER_,
			public VBUFFER_,
			public TBUFFER_

	{
	public:
		inline RBuffer(details::CBufferState const &state) noexcept : m_state{state}
		{
			LIBCORE_ASSURES(m_state.handle != VK_NULL_HANDLE);
			LIBCORE_ASSURES(m_state.memory != VK_NULL_HANDLE);
		}

		//! --------------------------------------------------------------------------- !//

		static HCBUFFER create_cbuffer(RealAbstractDevice const &device, Usage u, BytesLength l) noexcept;
		static HIBUFFER create_ibuffer(RealAbstractDevice const &device, Usage u, BytesLength l) noexcept;
		static HSBUFFER create_sbuffer(RealAbstractDevice const &device, Usage u, BytesLength l) noexcept;
		static HVBUFFER create_vbuffer(RealAbstractDevice const &device, Usage u, BytesLength l) noexcept;
		static HTBUFFER create_tbuffer(RealAbstractDevice const &device, Usage u, BytesLength l) noexcept;

		//! --------------------------------------------------------------------------- !//

		MByteBuffer map(UniqueAbstractDevice const &, Flags f, BytesLength o, BytesLength l) const noexcept;

		//! --------------------------------------------------------------------------- !//

		void unmap(UniqueAbstractDevice const &) const noexcept;
		void flush(UniqueAbstractDevice const &) const noexcept;

		//! --------------------------------------------------------------------------- !//

		void dispose(UniqueAbstractDevice const &device) noexcept;

		//! --------------------------------------------------------------------------- !//

		inline ~RBuffer() noexcept
		{
			LIBCORE_EXPECTS(m_state.handle == VK_NULL_HANDLE);
			LIBCORE_EXPECTS(m_state.memory == VK_NULL_HANDLE);
		}

	private:
		details::CBufferState m_state = {};
	};
};

#endif