#ifndef MICRO_VK13_ABSTRACT_DEVICE_HH__GUARD_SRC
#define MICRO_VK13_ABSTRACT_DEVICE_HH__GUARD_SRC

#include <libvk13/driver.hh>


#include "driver.hh"

namespace micro::vk13
{
	namespace details
	{
		using volk::VkDevice;
		using volk::VkDeviceCreateInfo;
		using volk::VkDeviceQueueCreateInfo;
		using volk::VkFlags;
		using volk::VkMemoryRequirements;
		using volk::VkPhysicalDevice;
		using volk::VkQueue;
		using volk::VkQueueFamilyProperties;
		using volk::VkQueueFlags;

		using VkDT = volk::VolkDeviceTable;


		//template<auto F, class ... Args>
		//inline auto dispatch(RealDevice const &d, Args ... args) noexcept
		//{
		//	return std::invoke(std::invoke(F, dtable(d)), device(d), args ...);
		//}

		struct DeviceState
		{
			VkDT                             vtable;
			VkDevice                         device;
			VkQueue                          gqueue;
			VkQueue                          cqueue;
			VkQueue                          tqueue;
			VkPhysicalDeviceMemoryProperties memory;
		};
	}


	class RealAbstractDevice : public AbstractDevice
	{
	public:
		RealAbstractDevice(RealPhysicalDevice const &device) noexcept;

		//! --------------------------------------------------------------------------- !//

		void dispose() noexcept override;

		//! --------------------------------------------------------------------------- !//

		constexpr auto const &handle() const noexcept { return m_device.device; }
		constexpr auto const &vtable() const noexcept { return m_device.vtable; }
		constexpr auto const &gqueue() const noexcept { return m_device.gqueue; }
		constexpr auto const &cqueue() const noexcept { return m_device.cqueue; }
		constexpr auto const &tqueue() const noexcept { return m_device.tqueue; }
		constexpr auto const &memory() const noexcept { return m_device.memory; }

		//! --------------------------------------------------------------------------- !//

		lib::Option<u32> get_memory_type(u32 reqs, u32 type) const noexcept;

		//! --------------------------------------------------------------------------- !//

		~RealAbstractDevice() noexcept;
	private:
		details::DeviceState m_device;
	};

	//! ----------------------------------------------------------------------------------- !//

	inline auto &_real(UniqueAbstractDevice const &_ptr) noexcept { return static_cast<RealAbstractDevice &>(*_ptr); }
	inline auto &_real(SharedAbstractDevice const &_ptr) noexcept { return static_cast<RealAbstractDevice &>(*_ptr); }
}

#endif