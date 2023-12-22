#include "abstract_device.hh"

namespace micro::vk13
{
	namespace details
	{
		struct InitDeviceTable : public volk::VolkDeviceTable
		{
			inline InitDeviceTable(VkDevice device) noexcept { volk::volkLoadDeviceTable(this, device); }
		};

		///
		///

		inline auto queue_create_info(u32 family) noexcept
		{
			static constexpr auto priority = 1.f;

			///
			///

			VkDeviceQueueCreateInfo _info =
			{
				.sType            = volk::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.pNext            = nullptr,
				.flags            = 0,
				.queueFamilyIndex = family,
				.queueCount       = 1,
				.pQueuePriorities = &priority
			};

			return _info;
		}

		inline auto create_device(RealPhysicalDevice const &device) noexcept
		{
			VkDevice _device = VK_NULL_HANDLE;

			using std::size;
			using std::data;

			lib::Vector<VkDeviceQueueCreateInfo> _queues;

			if (device.gqueue_family()) _queues.push_back(queue_create_info(device.gqueue_family().value()));
			if (device.cqueue_family()) _queues.push_back(queue_create_info(device.cqueue_family().value()));
			if (device.tqueue_family()) _queues.push_back(queue_create_info(device.tqueue_family().value()));

			if (_queues.empty())
			{
				LIBCORE_LOGWARN("Device will have no queues");
			}

			VkDeviceCreateInfo _info =
			{
				.sType                   = volk::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
				.pNext                   = nullptr,
				.flags                   = 0,
				.queueCreateInfoCount    = static_cast<u32>(size(_queues)),
				.pQueueCreateInfos       = data(_queues),
				.enabledLayerCount       = 0,
				.ppEnabledLayerNames     = nullptr,
				.enabledExtensionCount   = 0,
				.ppEnabledExtensionNames = nullptr,
				.pEnabledFeatures        = nullptr
			};

			if (is_failure(volk::vkCreateDevice(device.handle(), &_info, nullptr, &_device)))
			{
				///
				/// TODO: LOG

				return DeviceState{};
			} else
				LIBCORE_LOGINFO("vkCreateDevice succeeded");

			InitDeviceTable _vtable{_device};

			///
			/// Init the state vector
			///

			DeviceState _state
			{
				.vtable = _vtable,
				.device = _device,

				.gqueue = VK_NULL_HANDLE,
				.cqueue = VK_NULL_HANDLE,
				.tqueue = VK_NULL_HANDLE
			};

			///////////////////////////////////////////////////////////////////////////

			if (device.gqueue_family())
				_vtable.vkGetDeviceQueue(_device, device.gqueue_family().value(), 0, &_state.gqueue);
			if (device.cqueue_family())
				_vtable.vkGetDeviceQueue(_device, device.cqueue_family().value(), 0, &_state.cqueue);
			if (device.tqueue_family())
				_vtable.vkGetDeviceQueue(_device, device.tqueue_family().value(), 0, &_state.tqueue);

			///////////////////////////////////////////////////////////////////////////
			
			volk::vkGetPhysicalDeviceMemoryProperties(device.handle(), &_state.memory);

			///
			///

			return _state;
		}
	}

	RealAbstractDevice::RealAbstractDevice(RealPhysicalDevice const &device) noexcept : m_device{details::create_device(device)}
	{}

	void RealAbstractDevice::dispose() noexcept
	{
		delete this;
	}

	lib::Option<u32> RealAbstractDevice::get_memory_type(u32 flag, u32 type) const noexcept
	{
		auto const &_size = memory().memoryTypeCount;
		auto const &_data = memory().memoryTypes;

		/// Same as LunarG
		///

		for (auto i = 0U; i < _size; i++)
		{
			if ((type & 1) != 0 && (_data[i].propertyFlags & flag) == flag)
			{
				return i;
			}

			type >>= 1;
		}

		///
		///

		return lib::Nullopt;
	}

	RealAbstractDevice::~RealAbstractDevice() noexcept
	{
		vtable().vkDestroyDevice(handle(), nullptr);
	}

}