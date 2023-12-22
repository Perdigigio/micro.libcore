#ifndef MICRO_GLES_DEVICE_HH__GUARD
#define MICRO_GLES_DEVICE_HH__GUARD

#include <libcore/driver/video.hh>

#include <libcore/lib/memory.hh>
#include <libcore/lib/string.hh>
#include <libcore/lib/vector.hh>
#include <libcore/lib/panics.hh>
#include <libcore/lib/result.hh>

#include <libcore/int.hh>

namespace micro::vk13
{
	using namespace micro::core;
	using namespace micro::core::lib;

	struct AdapterInfo
	{
		char device_name[256];
		uuid device_uuid;
		uuid driver_uuid;
	};

	template<class T>
		using UniqueHandle = std::unique_ptr<std::remove_pointer_t<T>, void (*)(T) noexcept>;


	//! ----------------------------------------------------------------------------------- !//

	struct AbstractObject;
	struct PhysicalDevice; ///! Like a VkPhysicalDevice
	struct AbstractDevice; ///! Like a VkDevice

	//! ----------------------------------------------------------------------------------- !//

	struct AbstractObject
	{
		virtual void dispose() noexcept = 0;
	};

	//! ----------------------------------------------------------------------------------- !//

	struct Deleter
	{
		inline auto operator()(AbstractObject *obj) const noexcept { obj->dispose(); }
	};

	template<class T> using UniqueObject = std::unique_ptr<T, Deleter>;
	template<class T> using SharedObject = std::shared_ptr<T>;

	struct PhysicalDevice : public AbstractObject
	{
		virtual uuid device_uuid() const noexcept = 0;
		virtual uuid driver_uuid() const noexcept = 0;

		virtual lib::RString device_name() const noexcept = 0;
		virtual lib::RString driver_name() const noexcept = 0;
		virtual lib::RString driver_info() const noexcept = 0;
	};

	struct AbstractDevice : public AbstractObject
	{};

	//! ----------------------------------------------------------------------------------- !//

	using UniquePhysicalDevice = UniqueObject<PhysicalDevice>;
	using UniqueAbstractDevice = UniqueObject<AbstractDevice>;
	using SharedPhysicalDevice = SharedObject<PhysicalDevice>;
	using SharedAbstractDevice = SharedObject<AbstractDevice>;

	//! ----------------------------------------------------------------------------------- !//

	struct Driver
	{
		static constexpr auto E_UNKNOWN = error{-1};
		static constexpr auto E_FAILURE = error{-2};

		static bool init(RString app_name, u32 app_version,
				 RString eng_name, u32 eng_version) noexcept;

		static lib::Vector<UniquePhysicalDevice> enum_adapters() noexcept;
	};


}

#endif