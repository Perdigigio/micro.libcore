#include "device_rbuffer.hh"

namespace micro::vk13
{
	namespace details
	{
		static constexpr auto CBUFFER_BIT = volk::VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
						    volk::VK_BUFFER_USAGE_TRANSFER_DST_BIT |
						    volk::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

		static constexpr auto IBUFFER_BIT = volk::VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
						    volk::VK_BUFFER_USAGE_TRANSFER_DST_BIT |
						    volk::VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

		static constexpr auto SBUFFER_BIT = volk::VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
						    volk::VK_BUFFER_USAGE_TRANSFER_DST_BIT |
						    volk::VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

		static constexpr auto VBUFFER_BIT = volk::VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
						    volk::VK_BUFFER_USAGE_TRANSFER_DST_BIT |
						    volk::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

		static constexpr auto TBUFFER_BIT = volk::VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
						    volk::VK_BUFFER_USAGE_TRANSFER_DST_BIT |
						    volk::VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;

		static constexpr auto USAGE_DEFAULT = volk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | volk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | volk::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		static constexpr auto USAGE_DYNAMIC = volk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | volk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		static constexpr auto USAGE_STAGING = volk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | volk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | volk::VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

		///
		///

		inline auto create_handle(RealAbstractDevice const &device, VkDeviceSize size, [[maybe_unused]] Usage usage, VkBufferUsageFlags type) noexcept
		{
			VkBuffer _buffer = VK_NULL_HANDLE;

			auto const &_vtable = device.vtable();
			auto const &_device = device.handle();

			VkBufferCreateInfo _info =
			{
				.sType                 = volk::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
				.pNext                 = nullptr,
				.flags                 = 0,
				.size                  = size,
				.usage                 = type,
				.sharingMode           = volk::VK_SHARING_MODE_EXCLUSIVE,
				.queueFamilyIndexCount = 0,
				.pQueueFamilyIndices   = nullptr
			};

			if (is_failure(_vtable.vkCreateBuffer(_device, &_info, nullptr, &_buffer)))
			{
				LIBCORE_LOGFAIL("vkCreateBuffer failed: ");
				LIBCORE_LOGFAIL(cat("	.flags........:", fmt_hex(_info.flags)));
				LIBCORE_LOGFAIL(cat("	.size.........:", fmt_hex(_info.size)));
				LIBCORE_LOGFAIL(cat("	.usage........:", fmt_hex(_info.usage)));
				LIBCORE_LOGFAIL(cat("	.sharingMode..:", fmt_hex(_info.sharingMode)));
			} else
				LIBCORE_LOGINFO("vkCreateBuffer succeeded");

			///
			///

			return _buffer;
		}

		inline auto get_memory_requirements(RealAbstractDevice const & device, VkBuffer buffer) noexcept
		{
			VkMemoryRequirements _memory_reqs;

			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			_vtable.vkGetBufferMemoryRequirements(_device, buffer, &_memory_reqs);

			return _memory_reqs;
		}

		inline auto get_memory_flags(Usage usage) noexcept -> VkFlags
		{
			switch (usage)
			{
				case Usage::DEFAULT: return USAGE_DEFAULT;
				case Usage::DYNAMIC: return USAGE_DYNAMIC;
				case Usage::STAGING: return USAGE_STAGING;
			}

			///
			///

			LIBCORE_NOREACH("invalid usage");
		}

		inline auto get_memory_type(RealAbstractDevice const & device, Usage usage, VkMemoryRequirements const &requirements) noexcept
		{
			return device.get_memory_type(get_memory_flags(usage), requirements.memoryTypeBits).value();
		}

		inline auto create_memory(RealAbstractDevice const &device, Usage usage, VkMemoryRequirements const &requirements) noexcept
		{
			VkDeviceMemory _memory = VK_NULL_HANDLE;

			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			VkMemoryAllocateInfo _info =
			{
				.sType           = volk::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.pNext           = nullptr,
				.allocationSize  = requirements.size,
				.memoryTypeIndex = get_memory_type(device, usage, requirements)
			};

			if (is_failure(_vtable.vkAllocateMemory(_device, &_info, nullptr, &_memory)))
			{
				LIBCORE_LOGFAIL("vkAllocateMemory failed");
				LIBCORE_LOGFAIL(cat("	.allocationSize...: ", _info.allocationSize));
				LIBCORE_LOGFAIL(cat("	.memoryTypeIndex..: ", _info.memoryTypeIndex));
			} else
				LIBCORE_LOGINFO(cat("vkAllocateMemory allocated ", _info.allocationSize, " bytes"));

			///
			///

			return _memory;
		}

		inline auto create_memory(RealAbstractDevice const & device, VkBuffer buffer, Usage usage) noexcept
		{
			return create_memory(device, usage, get_memory_requirements(device, buffer));
		}

		inline auto delete_memory(RealAbstractDevice const &device, VkDeviceMemory memory) noexcept
		{
			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			_vtable.vkFreeMemory(_device, memory, nullptr);
		}

		inline auto delete_handle(RealAbstractDevice const &device, VkBuffer buffer) noexcept
		{
			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			_vtable.vkDestroyBuffer(_device, buffer, nullptr);
		}

		inline auto create_buffer(RealAbstractDevice const & device, VkBufferUsageFlags type, Usage usage, BytesLength length) noexcept
		{
			auto _length = static_cast<VkDeviceSize>(length);

			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			auto _handle = create_handle(device, _length, usage, type);
			auto _memory = create_memory(device, _handle, usage);

			if (is_failure(_vtable.vkBindBufferMemory(_device, _handle, _memory, 0)))
			{
				LIBCORE_LOGFAIL("vkBindBufferMemory failed");
				LIBCORE_LOGFAIL(cat("	_device: ", _device));
				LIBCORE_LOGFAIL(cat("	_handle: ", _handle));
				LIBCORE_LOGFAIL(cat("	_memory: ", _memory));

				delete_memory(device, std::exchange(_memory, VK_NULL_HANDLE));
				delete_handle(device, std::exchange(_handle, VK_NULL_HANDLE));
			}

			CBufferState _state
			{
				.handle       = _handle,
				.memory       = _memory,
				.requirements = get_memory_requirements(device, _handle),
				.properties   = get_memory_flags(usage)
			};

			///
			///

			return _state;
		}

		inline auto map_buffer(RealAbstractDevice const &device, VkDeviceMemory memory, VkDeviceSize offset,
												VkDeviceSize length) noexcept
		{
			void *_data = nullptr;

			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			if (is_failure(_vtable.vkMapMemory(_device, memory, offset, length, {}, &_data)))
			{
				LIBCORE_LOGFAIL("vkMapMemory failed");
				LIBCORE_LOGFAIL(cat("	memory..: ", memory));
				LIBCORE_LOGFAIL(cat("	offset..: ", offset));
				LIBCORE_LOGFAIL(cat("	length..: ", length));
			}

			///
			///

			return std::span{static_cast<std::byte *>(_data), length};
		}

		inline auto unmap_buffer(RealAbstractDevice const &device, VkDeviceMemory memory)
		{
			auto const &_device = device.handle();
			auto const &_vtable = device.vtable();

			_vtable.vkUnmapMemory(_device, memory);
		}
	}

	//! ----------------------------------------------------------------------------------- !//

	HCBUFFER RBuffer::create_cbuffer(RealAbstractDevice const &d, Usage u, BytesLength l) noexcept
	{
		return new (std::nothrow) RBuffer{details::create_buffer(d, details::CBUFFER_BIT, u, l)};
	}

	HIBUFFER RBuffer::create_ibuffer(RealAbstractDevice const &d, Usage u, BytesLength l) noexcept
	{
		return new (std::nothrow) RBuffer{details::create_buffer(d, details::IBUFFER_BIT, u, l)};
	}

	HSBUFFER RBuffer::create_sbuffer(RealAbstractDevice const &d, Usage u, BytesLength l) noexcept
	{
		return new (std::nothrow) RBuffer{details::create_buffer(d, details::SBUFFER_BIT, u, l)};
	}

	HVBUFFER RBuffer::create_vbuffer(RealAbstractDevice const &d, Usage u, BytesLength l) noexcept
	{
		return new (std::nothrow) RBuffer{details::create_buffer(d, details::VBUFFER_BIT, u, l)};
	}

	HTBUFFER RBuffer::create_tbuffer(RealAbstractDevice const &d, Usage u, BytesLength l) noexcept
	{
		return new (std::nothrow) RBuffer{details::create_buffer(d, details::TBUFFER_BIT, u, l)};
	}

	//! ----------------------------------------------------------------------------------- !//

	MByteBuffer RBuffer::map(UniqueAbstractDevice const &device, Flags f, BytesLength offset,
									      BytesLength length) const noexcept
	{
		auto _offset = static_cast<details::VkDeviceSize>(offset);
		auto _length = static_cast<details::VkDeviceSize>(length);

		if (_length == VK_WHOLE_SIZE)
		{
			/// Adjust size
			///

			_length = m_state.requirements.size - _offset;
		}

		return details::map_buffer(_real(device), m_state.memory, _offset, _length);
	}

	void RBuffer::unmap(UniqueAbstractDevice const &device) const noexcept
	{
		details::unmap_buffer(_real(device), m_state.memory);
	}

	void RBuffer::dispose(UniqueAbstractDevice const &d) noexcept
	{
		details::delete_memory(_real(d), std::exchange(m_state.memory, VK_NULL_HANDLE));
		details::delete_handle(_real(d), std::exchange(m_state.handle, VK_NULL_HANDLE));

		///
		///

		delete this;
	}
}