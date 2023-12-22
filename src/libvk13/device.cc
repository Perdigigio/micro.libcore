#include "device.hh"

namespace micro::vk13
{
	Device::Device(UniquePhysicalDevice const &device) noexcept :
		m_pdevice{new RealPhysicalDevice{_real(device)}},
		m_adevice{new RealAbstractDevice{_real(device)}}
	{}

	HCBUFFER Device::create_CBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i ) noexcept { return RBuffer::create_cbuffer(_real(m_adevice), u, l); }
	HIBUFFER Device::create_IBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i ) noexcept { return RBuffer::create_ibuffer(_real(m_adevice), u, l); }
	HSBUFFER Device::create_SBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i ) noexcept { return RBuffer::create_sbuffer(_real(m_adevice), u, l); }
	HVBUFFER Device::create_VBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i ) noexcept { return RBuffer::create_vbuffer(_real(m_adevice), u, l); }
	HTBUFFER Device::create_TBuffer(Usage u, Flags f, BytesLength l, CByteBuffer i ) noexcept { return RBuffer::create_tbuffer(_real(m_adevice), u, l); }

	MByteBuffer Device::map(HCBUFFER b, Flags f, BytesLength o, BytesLength l) noexcept { return static_cast<RBuffer *>(b)->map(m_adevice, f, o, l); }
	MByteBuffer Device::map(HIBUFFER b, Flags f, BytesLength o, BytesLength l) noexcept { return static_cast<RBuffer *>(b)->map(m_adevice, f, o, l); }
	MByteBuffer Device::map(HSBUFFER b, Flags f, BytesLength o, BytesLength l) noexcept { return static_cast<RBuffer *>(b)->map(m_adevice, f, o, l); }
	MByteBuffer Device::map(HVBUFFER b, Flags f, BytesLength o, BytesLength l) noexcept { return static_cast<RBuffer *>(b)->map(m_adevice, f, o, l); }
	MByteBuffer Device::map(HTBUFFER b, Flags f, BytesLength o, BytesLength l) noexcept { return static_cast<RBuffer *>(b)->map(m_adevice, f, o, l); }

	void Device::unmap(HCBUFFER b) noexcept { return static_cast<RBuffer *>(b)->unmap(m_adevice); }
	void Device::unmap(HIBUFFER b) noexcept { return static_cast<RBuffer *>(b)->unmap(m_adevice); }
	void Device::unmap(HSBUFFER b) noexcept { return static_cast<RBuffer *>(b)->unmap(m_adevice); }
	void Device::unmap(HVBUFFER b) noexcept { return static_cast<RBuffer *>(b)->unmap(m_adevice); }
	void Device::unmap(HTBUFFER b) noexcept { return static_cast<RBuffer *>(b)->unmap(m_adevice); }

	void Device::dispose(HCBUFFER b) noexcept { if (b) static_cast<RBuffer *>(b)->dispose(m_adevice); }
	void Device::dispose(HIBUFFER b) noexcept { if (b) static_cast<RBuffer *>(b)->dispose(m_adevice); }
	void Device::dispose(HSBUFFER b) noexcept { if (b) static_cast<RBuffer *>(b)->dispose(m_adevice); }
	void Device::dispose(HVBUFFER b) noexcept { if (b) static_cast<RBuffer *>(b)->dispose(m_adevice); }
	void Device::dispose(HTBUFFER b) noexcept { if (b) static_cast<RBuffer *>(b)->dispose(m_adevice); }
}