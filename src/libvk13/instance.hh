#ifndef MICRO_VK13_VULKAN_HH__GUARD_SRC
#define MICRO_VK13_VULKAN_HH__GUARD_SRC

#include <libcore/lib/string.hh>
#include <libcore/lib/vector.hh>
#include <libcore/lib/logger.hh>
#include <libcore/lib/memory.hh>
#include <libcore/lib/panics.hh>
#include <libcore/lib/result.hh>
#include <libcore/lib.hh>

namespace volk
{
	#include "volk/volk.h"
}

#include <type_traits>

namespace micro::vk13
{
	using namespace micro::core;

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		using VkUnique = std::unique_ptr<std::remove_pointer_t<T>, void (*)(T)>;

	//! ----------------------------------------------------------------------------------- !//

	using VkUniqueInstance       = VkUnique<volk::VkInstance>;
	using VkUniquePhysicalDevice = VkUnique<volk::VkPhysicalDevice>;
	using VkUniqueDevice         = VkUnique<volk::VkDevice>;
	using VkUniqueQueue          = VkUnique<volk::VkQueue>;
	using VkUniqueCommandBuffer  = VkUnique<volk::VkCommandBuffer>;

	//! ----------------------------------------------------------------------------------- !//

	using VkUniqueDebugUtilsMessenger = VkUnique<volk::VkDebugUtilsMessengerEXT>;

	//! ----------------------------------------------------------------------------------- !//

	constexpr auto is_failure(volk::VkResult r) noexcept { return r != volk::VK_SUCCESS; }
	constexpr auto is_success(volk::VkResult r) noexcept { return r == volk::VK_SUCCESS; }

	//! ----------------------------------------------------------------------------------- !//

	template<volk::VkResult ... R>
		constexpr auto check_result(volk::VkResult r) noexcept { return ((r == R) || ...); }


	//! ----------------------------------------------------------------------------------- !//

	struct Instance
	{
		static volk::VkInstance get() noexcept;

		/// @brief Load/Link vulkan driver and creates a new VkInstance
		///
		/// @param app_name 
		/// @param app_version 
		/// @param eng_name 
		/// @param eng_version 
		///
		/// @return 
		static bool init(lib::RString app_name, u32 app_version,
				 lib::RString eng_name, u32 eng_version) noexcept;

		///
		///

		static void reset() noexcept;
	};
}


#endif