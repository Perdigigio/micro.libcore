cmake_minimum_required(VERSION 3.12)

	project(Micro LANGUAGES C CXX VERSION 1.0.0)

	option(BUILD_WITH_ARM_INTRINSICS "enables ARM intrinsics" OFF)
	option(BUILD_WITH_SSE_INTRINSICS "enables SSE intrinsics" OFF)
	option(BUILD_WITH_AVX_INTRINSICS "enables AVX intrinsics" OFF)

	find_package (Threads)
	find_package (VulkanHeaders CONFIG)


	add_library(core STATIC src/libcore/lib/memory.cc
				src/libcore/lib/buffer.cc
				src/libcore/lib/logger.cc
				src/libcore/lib/panics.cc
				src/libcore/lib/string.cc
				src/libcore/driver/video.cc
				src/libcore/graphic/cubemap.cc
				src/libcore/graphic/ibuffer.cc
				src/libcore/graphic/surface.cc
				src/libcore/graphic/texture.cc
				src/libcore/graphic/vbuffer.cc
				$<$<PLATFORM_ID:Unix,Linux>:src/libcore/io/file_nix.cc>
				$<$<PLATFORM_ID:Unix,Linux>:src/libcore/io/mmap_nix.cc>
				$<$<PLATFORM_ID:Windows>:src/libcore/io/file_win.cc>
				$<$<PLATFORM_ID:Windows>:src/libcore/io/mmap_win.cc>)

	target_link_libraries(core PRIVATE Threads::Threads)

	add_library(micro::core ALIAS core)

	###########################################################################################
	##                                       libvk13                                         ##
	###########################################################################################

	add_library(volk STATIC src/libvk13/volk/volk.c
				src/libvk13/volk/volk.h)

	add_library(vk13 STATIC src/libvk13/abstract_device.cc
				src/libvk13/device_adapter.cc
				src/libvk13/device_rbuffer.cc
				src/libvk13/device_context.cc
				src/libvk13/device_debug_callback.cc
				src/libvk13/device_factory.cc
				src/libvk13/device_texture.cc
				src/libvk13/device.cc
				src/libvk13/driver.cc
				src/libvk13/instance.cc)

	target_link_libraries(vk13 PRIVATE core)
	target_link_libraries(vk13 PRIVATE volk)

	target_link_libraries(vk13 PRIVATE Vulkan::Headers)
	target_link_libraries(volk PRIVATE Vulkan::Headers)


	#target_compile_definitions(vk13 PRIVATE VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1)

	target_include_directories(vk13 PUBLIC ${PROJECT_SOURCE_DIR}/include)

	# FEATURES
	#

	target_compile_features(core PUBLIC cxx_std_20)
	target_compile_features(vk13 PUBLIC cxx_std_20)


	# INCLUDE
	#

	target_include_directories(core INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

	target_include_directories(core PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)


	# INSTALLATION
	#

	include(GNUInstallDirs)

	#install(FILES "${PROJECT_SOURCE_DIR}/include/libmath/matrix.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x2.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x2_arm.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x2_sse.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x3.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2x4.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix2xN_transform.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x2.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x3.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x3_arm.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x3_sse.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3x4.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix3xN_transform.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x2.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x3.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x4.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x4_arm.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4x4_sse.inl     "
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/matrix4xN_transform.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector2.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector2_arm.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector2_sse.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector3.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector3_arm.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector3_sse.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector4.hh"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector4_arm.inl"
	#	      "${PROJECT_SOURCE_DIR}/include/libmath/vector4_sse.inl" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libmath COMPONENT dev)
    #
	#target_include_directories(libmath INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

	add_executable(__test src/test.cc)

	target_link_libraries(__test PUBLIC vk13 ${CMAKE_DL_LIBS} Vulkan::Headers)

	# TESTING
	#

	include(CTest)

	if(BUILD_TESTING)

		add_executable(libcore-test-int test/int.cc)
		add_executable(libcore-test-lib test/lib.cc)
		add_executable(libcore-test-lib-handle test/lib_handle.cc)


		add_test(NAME int COMMAND $<TARGET_FILE:libcore-test-int>)
		add_test(NAME lib COMMAND $<TARGET_FILE:libcore-test-lib>)
		add_test(NAME lib_handle COMMAND $<TARGET_FILE:libcore-test-lib>)


		target_link_libraries(libcore-test-int PRIVATE core)
		target_link_libraries(libcore-test-lib PRIVATE core)
		target_link_libraries(libcore-test-lib-handle PRIVATE core)

		target_compile_features(libcore-test-int PUBLIC cxx_std_17)
		target_compile_features(libcore-test-lib PUBLIC cxx_std_17)
		target_compile_features(libcore-test-lib-handle PUBLIC cxx_std_17)

		#target_compile_options(libcore-test-lib-handle PUBLIC -fsanitize=address,leak,undefined)
		#target_link_options(libcore-test-lib-handle PUBLIC -fsanitize=address,leak,undefined)


	endif()

	# ALIAS
	#
	