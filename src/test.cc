#include <exception>
#include <iostream>
#include <iomanip>

#include <libvk13/driver.hh>
#include <libvk13/device.hh>

#include <libcore/lib/panics.hh>
#include <libcore/lib/logger.hh>
#include <libcore/lib/string.hh>

#include <xmmintrin.h>

auto const &app = "test";
auto const &eng = "test";
auto const &app_ver = 1;
auto const &eng_ver = 1;

int main()
{
	using namespace micro::core::lib;
	using namespace micro::core::driver;

	std::set_terminate([]
	{
		try
		{
			std::rethrow_exception(std::current_exception());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	});

	GlobalLogger::setup(ANSILogger{});

	auto _init = micro::vk13::Driver::init(app, app_ver,
					       eng, eng_ver);

	if (!_init)
		return -1;

	auto hadapters =  micro::vk13::Driver::enum_adapters();

	for (auto const&hadapter : hadapters)
	{
		LIBCORE_LOGINFO(cat("device_name...: ", hadapter->device_name()));
		LIBCORE_LOGINFO(cat("driver_name...: ", hadapter->driver_name()));
		LIBCORE_LOGINFO(cat("driver_info...: ", hadapter->driver_info()));

		LIBCORE_LOGINFO(cat("device_uuid...: ", hadapter->device_uuid()));
		LIBCORE_LOGINFO(cat("driver_uuid...: ", hadapter->driver_uuid()));
	}

	micro::vk13::Device _device1 {hadapters[0]};

	auto vbuffer = _device1.create_CBuffer(video::Usage::DEFAULT, video::Flags{0}, video::BytesLength{1024 * 4 * sizeof(micro::core::u32[4])}, {});
	auto ibuffer = _device1.create_CBuffer(video::Usage::DYNAMIC, video::Flags{0}, video::BytesLength{1024 * 2 * sizeof(micro::core::u32[3])}, {});

	auto vbuffer_map = _device1.map(vbuffer, video::Flags{0}, video::BytesLength{0}, video::BytesLength{~0ULL});
	auto ibuffer_map = _device1.map(ibuffer, video::Flags{0}, video::BytesLength{0}, video::BytesLength{~0ULL});

	alignas(16) float _v1 [4] = { 0.f, 0.f, 0.f, 1.f };
	alignas(16) float _v2 [4] = { 1.f, 0.f, 0.f, 1.f };
	alignas(16) float _v3 [4] = { 1.f, 1.f, 0.f, 1.f };
	alignas(16) float _v4 [4] = { 0.f, 1.f, 0.f, 1.f };

	for (auto i = 0U; i < 1024; i++)
	{
		using std::data;

		_mm_stream_ps(reinterpret_cast<float *>(data(vbuffer_map.subspan(i * 64 + 0x00, 16))), _mm_load_ps(_v1));
		_mm_stream_ps(reinterpret_cast<float *>(data(vbuffer_map.subspan(i * 64 + 0x10, 16))), _mm_load_ps(_v2));
		_mm_stream_ps(reinterpret_cast<float *>(data(vbuffer_map.subspan(i * 64 + 0x20, 16))), _mm_load_ps(_v3));
		_mm_stream_ps(reinterpret_cast<float *>(data(vbuffer_map.subspan(i * 64 + 0x30, 16))), _mm_load_ps(_v4));

		new (data(ibuffer_map.subspan(i * 24, 12)) + 0x0) micro::core::u32[3]{0, 1, 2};
		new (data(ibuffer_map.subspan(i * 24, 12)) + 0xC) micro::core::u32[3]{0, 3, 2};
	}

	_mm_sfence();

	_device1.unmap(ibuffer);
	_device1.unmap(vbuffer);



	auto vbuffer_map2 = _device1.map(vbuffer, video::Flags{0}, video::BytesLength{0}, video::BytesLength{~0ULL});
	auto ibuffer_map2 = _device1.map(ibuffer, video::Flags{0}, video::BytesLength{0}, video::BytesLength{~0ULL});

	

	alignas(16) float __v1 [4];
	alignas(16) float __v2 [4];
	alignas(16) float __v3 [4];
	alignas(16) float __v4 [4];

	_mm_store_ps(__v1, _mm_load_ps(reinterpret_cast<float *>(data(vbuffer_map2)) + 0x0));
	_mm_store_ps(__v2, _mm_load_ps(reinterpret_cast<float *>(data(vbuffer_map2)) + 0x4));
	_mm_store_ps(__v3, _mm_load_ps(reinterpret_cast<float *>(data(vbuffer_map2)) + 0x8));
	_mm_store_ps(__v4, _mm_load_ps(reinterpret_cast<float *>(data(vbuffer_map2)) + 0xC));

	for (auto B : __v1) std::cout << std::hex << static_cast<int>(B) << " "; std::cout << std::endl;
	for (auto B : __v2) std::cout << std::hex << static_cast<int>(B) << " "; std::cout << std::endl;
	for (auto B : __v3) std::cout << std::hex << static_cast<int>(B) << " "; std::cout << std::endl;
	for (auto B : __v4) std::cout << std::hex << static_cast<int>(B) << " "; std::cout << std::endl;

	//for (auto B : ibuffer_map2) std::cout << std::hex << static_cast<int>(B) << " ";


	_device1.unmap(ibuffer);
	_device1.unmap(vbuffer);

	_device1.dispose(ibuffer);
	_device1.dispose(vbuffer);

	std::cout << "fine" << std::endl;



	return 0;
}