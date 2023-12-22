#include "instance.hh"

namespace micro::vk13
{
	///
	/// GLOBAL STATE =(
	///

	static VkUniqueInstance _instance = {nullptr, nullptr};
	static VkUniqueDebugUtilsMessenger _messenger = {nullptr, nullptr};

	///
	///

	namespace details
	{
		

		using volk::VkBool32;
		using volk::VkResult;
		using volk::VkStructureType;
		using volk::VkApplicationInfo;
		using volk::VkInstanceCreateInfo;
		using volk::VkInstance;

		using volk::VkDebugUtilsMessengerCreateInfoEXT;
		using volk::VkDebugUtilsMessengerCreateFlagsEXT;
		using volk::VkDebugUtilsMessageSeverityFlagBitsEXT;
		using volk::VkDebugUtilsMessengerCallbackDataEXT;
		using volk::VkDebugUtilsMessageTypeFlagsEXT;
		using volk::VkDebugUtilsMessageTypeFlagBitsEXT;
		using volk::VkDebugUtilsMessengerEXT;

		using ExtView = lib::Span<char const * const>;
		using LyrView = lib::Span<char const * const>;

		static constexpr std::initializer_list<char const *> required_lyrs = {};
		static constexpr std::initializer_list<char const *> required_exts =
		{
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
			///VK_KHR_SURFACE_EXTENSION_NAME,
			///VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		inline auto delete_instance(VkInstance instance)
		{
			LIBCORE_EXPECTS(instance == volk::volkGetLoadedInstance());

			if constexpr (micro::core::flags::dbg_build)
			{
				_messenger.reset();
			}

			volk::vkDestroyInstance(instance, nullptr);
		}

		inline auto create_instance(VkApplicationInfo const &info, LyrView lyrs,
									   ExtView exts) noexcept
		{
			VkInstance _inst = {};

			using std::size;
			using std::data;

			VkInstanceCreateInfo _info =
			{
				.sType                   = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
				.pNext                   = nullptr,
				.flags                   = 0,
				.pApplicationInfo        = &info,
				.enabledLayerCount       = static_cast<u32>(size(lyrs)),
				.ppEnabledLayerNames     = data(lyrs),
				.enabledExtensionCount   = static_cast<u32>(size(exts)),
				.ppEnabledExtensionNames = data(exts)
			};

			if (vk13::is_failure(volk::vkCreateInstance(&_info, nullptr, &_inst)))
			{
				LIBCORE_LOGFAIL("vkCreateInstance failed");

				LIBCORE_LOGFAIL("VkApplicationInfo");
				LIBCORE_LOGFAIL(lib::cat("	|__ pApplicationName....: ", info.pApplicationName));
				LIBCORE_LOGFAIL(lib::cat("	|__ applicationVersion..: ", info.applicationVersion));
				LIBCORE_LOGFAIL(lib::cat("	|__ pEngineName.........: ", info.pEngineName));
				LIBCORE_LOGFAIL(lib::cat("	|__ EngineVersion.......: ", info.engineVersion));
				LIBCORE_LOGFAIL(lib::cat("	|__ apiVersion:.........: ", VK_API_VERSION_MAJOR(info.apiVersion), ".",
											     VK_API_VERSION_MINOR(info.apiVersion)));

				LIBCORE_LOGFAIL("VkInstanceCreateInfo");

				for (auto i = 0; auto lyr : lyrs)
					LIBCORE_LOGFAIL(lib::cat("	|__ ppEnabledLayerNames[", i++, "]......: ", lib::LString{lyr}));
				for (auto i = 0; auto ext : exts)
					LIBCORE_LOGFAIL(lib::cat("	|__ ppEnabledExtensionNames[", i++, "]..: ", lib::LString{ext}));
			} else
				LIBCORE_LOGINFO("vkCreateInstance succeeded");

			///
			///

			return VkUniqueInstance{_inst, delete_instance};
		}

		inline auto create_instance(lib::LString app, u32 app_ver,
					    lib::LString eng, u32 eng_ver) noexcept
		{
			using std::data;

			VkApplicationInfo _info =
			{
				.sType              = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO,
				.pNext              = nullptr,
				.pApplicationName   = data(app),
				.applicationVersion = app_ver,
				.pEngineName        = data(eng),
				.engineVersion      = eng_ver,
				.apiVersion         = VK_API_VERSION_1_3
			};

			///
			///

			return create_instance(_info, required_lyrs, required_exts);
		}

		VkBool32 debug_utils_messenger_callback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
							VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
							VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
							void                                       *pUserData)
		{

			LIBCORE_LOGINFO(lib::cat("[", lib::LString{pCallbackData->pMessageIdName}, "] ", lib::LString{pCallbackData->pMessage}));

			return VK_TRUE;
		}

		///
		///

		inline auto delete_debug_utils_messenger(VkDebugUtilsMessengerEXT messenger) noexcept
		{
			volk::vkDestroyDebugUtilsMessengerEXT(volk::volkGetLoadedInstance(), messenger, nullptr);
		}

		inline auto create_debug_utils_messenger(VkInstance instance) noexcept
		{
			VkDebugUtilsMessengerEXT _messenger = {};

			constexpr VkDebugUtilsMessageTypeFlagsEXT _message_severity =
			{
				volk::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
				volk::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				volk::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
				volk::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
			};

			constexpr VkDebugUtilsMessageTypeFlagsEXT _message_type =
			{
				volk::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				volk::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				volk::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
			};

			VkDebugUtilsMessengerCreateInfoEXT const _info =
			{
				.sType           = volk::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
				.pNext           = nullptr,
				.flags           = 0,
				.messageSeverity = _message_severity,
				.messageType     = _message_type,
				.pfnUserCallback = debug_utils_messenger_callback,
				.pUserData       = nullptr
			};

			if (!volk::vkCreateDebugUtilsMessengerEXT || vk13::is_failure(volk::vkCreateDebugUtilsMessengerEXT(instance, &_info, nullptr, &_messenger)))
			{
				LIBCORE_LOGINFO(lib::cat("instance:", instance));

				LIBCORE_LOGINFO("VkDebugUtilsMessengerCreateInfoEXT");
				LIBCORE_LOGINFO(lib::cat("	|__ messageSeverity..: ", _info.messageSeverity));
				LIBCORE_LOGINFO(lib::cat("	|__ messageType......: ", _info.messageType));
				LIBCORE_LOGINFO(lib::cat("	|__ pfnUserCallback..: ", "debug_utils_messenger_callback"));
				LIBCORE_LOGINFO(lib::cat("	|__ pUserData........: ", _info.pUserData));
			} else
				LIBCORE_LOGINFO("vkCreateDebugUtilsMessengerEXT succeeded");

			///
			///

			return VkUniqueDebugUtilsMessenger{_messenger, delete_debug_utils_messenger};
		}
	}

	///
	///

	volk::VkInstance Instance::get() noexcept
	{
		return _instance.get();
	}

	bool Instance::init(lib::RString app_name, u32 app_version,
			    lib::RString eng_name, u32 eng_version) noexcept
	{
		static auto const _volk = volk::volkInitialize();

		if (is_success(_volk))
		{
			_instance = details::create_instance(lib::LString{app_name}, app_version,
							     lib::LString{eng_name}, eng_version);

			if (!_instance)
			{
				LIBCORE_LOGFAIL("details::create_instance failed");
				LIBCORE_LOGFAIL(lib::cat("	app_name.....: ", app_name));
				LIBCORE_LOGFAIL(lib::cat("	app_version..: ", app_version));
				LIBCORE_LOGFAIL(lib::cat("	eng_name.....: ", eng_name));
				LIBCORE_LOGFAIL(lib::cat("	eng_version..: ", eng_version));
			}

			volk::volkLoadInstanceOnly(_instance.get());

			if constexpr(micro::core::flags::dbg_build)
			{
				_messenger = details::create_debug_utils_messenger(_instance.get());
			}
		}

		///
		///

		return !!_instance;
	}

	void Instance::reset() noexcept
	{
		_instance.reset();
	}

}