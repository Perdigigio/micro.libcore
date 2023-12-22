#include "driver.hh"

namespace micro::vk13
{
	namespace details
	{
		inline auto enum_physical_devices(VkInstance instance, size_t length, VkPhysicalDevice devices[]) noexcept
		{
			auto _length = static_cast<uint32_t>(length);

			if (!check_result<VkResult::VK_SUCCESS,
					  VkResult::VK_INCOMPLETE>(volk::vkEnumeratePhysicalDevices(instance, &_length, devices)))
			{
				LIBCORE_LOGFAIL(lib::cat("vkEnumeratePhysicalDevices failed"));
				LIBCORE_LOGFAIL(lib::cat("	instance...: ", (void const *)instance));
				LIBCORE_LOGFAIL(lib::cat("	length.....: ", length));
				LIBCORE_LOGFAIL(lib::cat("	devices....: ", (void const *)devices));

				_length = 0;
			} else
				LIBCORE_LOGINFO(lib::cat("vkEnumeratePhysicalDevices found ", _length, " device(s)"));

			return _length;
		}

		inline auto pack_physical_devices(size_t length, VkPhysicalDevice devices[]) noexcept
		{
			lib::Vector<UniquePhysicalDevice> _devices;

			for (auto i = 0U; i < length; ++i)
			{
				_devices.emplace_back(new (std::nothrow) RealPhysicalDevice{devices[i]});
			}

			return _devices;
		}

		inline auto enum_physical_devices(VkInstance instance) noexcept
		{
			VkPhysicalDevice _devices[MAX_COUNT_PHYSICAL_DEVICES] = {};

			using std::size;
			using std::data;

			auto _length = enum_physical_devices(instance, size(_devices),
								       data(_devices));

			///
			///

			return pack_physical_devices(_length, _devices);
		}

		inline auto get_physical_device_queues(VkPhysicalDevice device, u32 length, VkQueueFamilyProperties *queues)
		{
			volk::vkGetPhysicalDeviceQueueFamilyProperties(device, &length, queues);

			return length;
		}

		inline auto find_queue_family(VkPhysicalDevice device, VkQueueFlags flags) noexcept ->  lib::Option<u32>
		{
			VkQueueFamilyProperties _queues[MAX_COUNT_QUEUE_FAMILIES];

			using std::size;
			using std::data;

			auto _length =  get_physical_device_queues(device, size(_queues),
									   data(_queues));

			///
			///

			for (auto i = 0U; i < _length; ++i)
			{
				if ((_queues[i].queueFlags & O_QUEUE_FLAGS) == flags)
					return i;
			}

			///
			///

			return lib::Nullopt;
		}

		inline auto get_physical_device_info(VkPhysicalDevice device) noexcept
		{
			LIBCORE_EXPECTS(device && "Invalid device");

			VkPhysicalDeviceInfo _info =
			{
				.vulkan_13 = { .sType = volk::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES, .pNext = nullptr },
				.vulkan_12 = { .sType = volk::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES, .pNext = &_info.vulkan_13 },
				.vulkan_11 = { .sType = volk::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES, .pNext = &_info.vulkan_12 },
				.vulkan_10 = { .sType = volk::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,          .pNext = &_info.vulkan_11 },

				.gqueue = find_queue_family(device, G_QUEUE_FLAGS),
				.cqueue = find_queue_family(device, C_QUEUE_FLAGS),
				.tqueue = find_queue_family(device, T_QUEUE_FLAGS)
			};

			volk::vkGetPhysicalDeviceProperties2(device, &_info.vulkan_10);

			///
			///

			return _info;
		}


	}

	bool Driver::init(RString app, u32 app_ver,
			  RString eng, u32 eng_ver) noexcept
	{
		return Instance::init(app, app_ver,
				      eng, eng_ver);
		
	}

	//! ----------------------------------------------------------------------------------- !//

	RealPhysicalDevice::RealPhysicalDevice(details::VkPhysicalDevice device) noexcept : m_device{device}
	{
		auto _info = details::get_physical_device_info(device);

		m_device_name = _info.vulkan_10.properties.deviceName;
		m_driver_name = _info.vulkan_12.driverName;
		m_driver_info = _info.vulkan_12.driverInfo;
		m_device_uuid = make_uuid(_info.vulkan_11.deviceUUID);
		m_device_uuid = make_uuid(_info.vulkan_11.driverUUID);

		m_gqueue_family = _info.gqueue;
		m_cqueue_family = _info.cqueue;
		m_tqueue_family = _info.tqueue;
	}

	void RealPhysicalDevice::dispose() noexcept
	{
		delete this;
	}

	//! ----------------------------------------------------------------------------------- !//


	lib::Vector<UniquePhysicalDevice> Driver::enum_adapters() noexcept
	{
		return details::enum_physical_devices(Instance::get());
	}
}