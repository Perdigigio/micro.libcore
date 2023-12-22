#ifndef MICRO_VK13_DRIVER_HH__GUARD_SRC
#define MICRO_VK13_DRIVER_HH__GUARD_SRC

#include <libvk13/driver.hh>

#include "instance.hh"

namespace micro::vk13
{
	namespace details
	{
		static inline constexpr auto MAX_COUNT_PHYSICAL_DEVICES = 64U;
		static inline constexpr auto MAX_COUNT_QUEUE_FAMILIES = 32U;

		using volk::VkBool32;
		using volk::VkResult;
		using volk::VkStructureType;
		using volk::VkInstance;
		using volk::VkPhysicalDevice;
		using volk::VkPhysicalDeviceType;
		using volk::VkPhysicalDeviceIDProperties;
		using volk::VkPhysicalDeviceProperties2;
		using volk::VkPhysicalDeviceVulkan11Properties;
		using volk::VkPhysicalDeviceVulkan12Properties;
		using volk::VkPhysicalDeviceVulkan13Properties;
		using volk::VkPhysicalDeviceMemoryProperties;
		using volk::VkQueueFamilyProperties;
		using volk::VkQueueFlags;

		static inline constexpr VkQueueFlags O_QUEUE_FLAGS = volk::VK_QUEUE_TRANSFER_BIT | volk::VK_QUEUE_COMPUTE_BIT | volk::VK_QUEUE_GRAPHICS_BIT;
		static inline constexpr VkQueueFlags G_QUEUE_FLAGS = volk::VK_QUEUE_TRANSFER_BIT | volk::VK_QUEUE_COMPUTE_BIT | volk::VK_QUEUE_GRAPHICS_BIT;
		static inline constexpr VkQueueFlags C_QUEUE_FLAGS = volk::VK_QUEUE_TRANSFER_BIT | volk::VK_QUEUE_COMPUTE_BIT;
		static inline constexpr VkQueueFlags T_QUEUE_FLAGS = volk::VK_QUEUE_TRANSFER_BIT;

		struct VkPhysicalDeviceInfo
		{
			VkPhysicalDeviceVulkan13Properties vulkan_13;
			VkPhysicalDeviceVulkan12Properties vulkan_12;
			VkPhysicalDeviceVulkan11Properties vulkan_11;
			VkPhysicalDeviceProperties2        vulkan_10;

			lib::Option<u32> gqueue;
			lib::Option<u32> cqueue;
			lib::Option<u32> tqueue;
		};

	}

	class RealPhysicalDevice : public PhysicalDevice
	{
	public:
		RealPhysicalDevice(details::VkPhysicalDevice device) noexcept;

		//! --------------------------------------------------------------------------- !//

		void dispose() noexcept override;

		//! --------------------------------------------------------------------------- !//

		uuid device_uuid() const noexcept override { return m_device_uuid; }
		uuid driver_uuid() const noexcept override { return m_driver_uuid; }

		lib::RString device_name() const noexcept override { return m_device_name; }
		lib::RString driver_name() const noexcept override { return m_driver_name; }
		lib::RString driver_info() const noexcept override { return m_driver_info; }

		//! --------------------------------------------------------------------------- !//

		inline auto gqueue_family() const noexcept { return m_gqueue_family; }
		inline auto cqueue_family() const noexcept { return m_cqueue_family; }
		inline auto tqueue_family() const noexcept { return m_tqueue_family; }

		//! --------------------------------------------------------------------------- !//

		inline auto handle() const noexcept { return m_device; }

	private:
		details::VkPhysicalDevice m_device;

		lib::LString m_device_name;
		lib::LString m_driver_name;
		lib::LString m_driver_info;
		uuid m_device_uuid;
		uuid m_driver_uuid;

		lib::Option<u32> m_gqueue_family;
		lib::Option<u32> m_cqueue_family;
		lib::Option<u32> m_tqueue_family;
	};
	
	///
	///

	inline auto &_real(UniquePhysicalDevice const &_ptr) noexcept { return static_cast<RealPhysicalDevice &>(*_ptr); }
	inline auto &_real(SharedPhysicalDevice const &_ptr) noexcept { return static_cast<RealPhysicalDevice &>(*_ptr); }

}

#endif