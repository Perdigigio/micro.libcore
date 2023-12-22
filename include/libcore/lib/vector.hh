#ifndef MICRO_LIBCORE_LIB_VECTOR_HH__GUARD
#define MICRO_LIBCORE_LIB_VECTOR_HH__GUARD

#include <vector>

namespace micro::core::lib
{
	namespace vector
	{
		template<class T>
			using Allocator = std::allocator<T>;
	}

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
		using Vector = std::vector<T, vector::Allocator<T>>;

	//! ----------------------------------------------------------------------------------- !//

	

} // namespace micro::core::lib

#endif