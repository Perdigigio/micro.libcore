#ifndef MICRO_LIBCORE_LIB_HH__GUARD
#define MICRO_LIBCORE_LIB_HH__GUARD

#include "int.hh"

#if defined(NDEBUG)
#	define LIBCORE_NDEBUG (1)
#else
#	define LIBCORE_NDEBUG (0)
#endif

namespace micro::core
{
	namespace flags
	{
		static constexpr auto dbg_build {LIBCORE_NDEBUG == 0};
		static constexpr auto rel_build {LIBCORE_NDEBUG != 0};
	}

	/// @brief Given a reference to B<D, X ...> performs upcast to D
	///
	/// @tparam D derived class
	/// @tparam B base class
	/// @tparam X optional params
	///
	template <template <class ...> class B, class D, class ... X>
		constexpr D & upcast(B<D, X ...> &base) noexcept { return static_cast<D &>(base); }

	/// @brief Given a reference to B<D, X ...> performs upcast to D
	///
	/// @tparam D derived class
	/// @tparam B base class
	/// @tparam X optional params
	///
	template <template <class ...> class B, class D, class ... X>
		constexpr D * upcast(B<D, X ...> *base) noexcept { return static_cast<D *>(base); }

	/// @brief Given a reference to B<D, X ...> performs upcast to D
	///
	/// @tparam D derived class
	/// @tparam B base class
	/// @tparam X optional params
	///
	template <
	template <class ...> class B, class D, class ... X>
		constexpr D const & upcast(B<D, X ...> const &base) noexcept { return static_cast<D const &>(base); }

	/// @brief Given a reference to B<D, X ...> performs upcast to D
	///
	/// @tparam D derived class
	/// @tparam B base class
	/// @tparam X optional params
	///
	template <
	template <class ...> class B, class D, class ... X>
		constexpr D const * upcast(B<D, X ...> const *base) noexcept { return static_cast<D const *>(base); }

	//! ----------------------------------------------------------------------------------- !//

	template<class T> struct Eq {};
	template<class T> struct Ne {};
	template<class T> struct Lt {};
	template<class T> struct Gt {};
	template<class T> struct Le {};
	template<class T> struct Ge {};

	//!
	//!

	template <class T> constexpr auto eq(Eq<T> const &l, Eq<T> const &r) noexcept -> bool { return upcast(l).eq(upcast(r)); }
	template <class T> constexpr auto ne(Ne<T> const &l, Ne<T> const &r) noexcept -> bool { return upcast(l).ne(upcast(r)); }
	template <class T> constexpr auto lt(Lt<T> const &l, Lt<T> const &r) noexcept -> bool { return upcast(l).lt(upcast(r)); }
	template <class T> constexpr auto gt(Gt<T> const &l, Gt<T> const &r) noexcept -> bool { return upcast(l).gt(upcast(r)); }
	template <class T> constexpr auto le(Le<T> const &l, Le<T> const &r) noexcept -> bool { return upcast(l).le(upcast(r)); }
	template <class T> constexpr auto ge(Ge<T> const &l, Ge<T> const &r) noexcept -> bool { return upcast(l).ge(upcast(r)); }

	//!
	//!

	template<class T> constexpr auto operator ==(Eq<T> const &l, Eq<T> const &r) noexcept { return eq(upcast(l), upcast(r)); }
	template<class T> constexpr auto operator !=(Ne<T> const &l, Ne<T> const &r) noexcept { return ne(upcast(l), upcast(r)); }
	template<class T> constexpr auto operator  <(Lt<T> const &l, Lt<T> const &r) noexcept { return lt(upcast(l), upcast(r)); }
	template<class T> constexpr auto operator  >(Gt<T> const &l, Gt<T> const &r) noexcept { return gt(upcast(l), upcast(r)); }
	template<class T> constexpr auto operator <=(Le<T> const &l, Le<T> const &r) noexcept { return le(upcast(l), upcast(r)); }
	template<class T> constexpr auto operator >=(Ge<T> const &l, Ge<T> const &r) noexcept { return ge(upcast(l), upcast(r)); }

	//! ----------------------------------------------------------------------------------- !//

	enum class comparison_r
	{
		eq, //! comparison returned equality
		lt, //! comparison returned less than
		gt, //! comparison returned greater than
	};

	template <class T>
	struct Comparable : public Eq<T>,
			    public Ne<T>,
			    public Lt<T>,
			    public Gt<T>,
			    public Le<T>,
			    public Ge<T>
	{
		constexpr auto eq(T const &rhs) const noexcept { return upcast(this)->compare(rhs) == comparison_r::eq; }
		constexpr auto ne(T const &rhs) const noexcept { return upcast(this)->compare(rhs) != comparison_r::eq; }
		constexpr auto gt(T const &rhs) const noexcept { return upcast(this)->compare(rhs) == comparison_r::gt; }
		constexpr auto lt(T const &rhs) const noexcept { return upcast(this)->compare(rhs) == comparison_r::lt; }
		constexpr auto le(T const &rhs) const noexcept { return upcast(this)->compare(rhs) != comparison_r::gt; }
		constexpr auto ge(T const &rhs) const noexcept { return upcast(this)->compare(rhs) != comparison_r::lt; }
	};

	//! ----------------------------------------------------------------------------------- !//

	template<class T>
	//! @brief compares two operands using lt operator
	//!
	//! @param lhs 1st operand
	//! @param rhs 2nd operand
	//!
	constexpr auto compare(Comparable<T> const &lhs,
			       Comparable<T> const &rhs) noexcept { return upcast(lhs).compare(upcast(rhs)); }

	//! ----------------------------------------------------------------------------------- !//

	template<class T> struct Add {};
	template<class T> struct Sub {};
	template<class T> struct Mul {};
	template<class T> struct Div {};

	//! ----------------------------------------------------------------------------------- !//

	template <class T>
	//! @brief if add(lhs, rhs) exists, performs addition
	//!
	//! @param lhs 1st operand
	//! @param rhs 2nd operand
	//!
	constexpr auto add(Add<T> const &lhs,
			   Add<T> const &rhs) noexcept { return upcast(lhs).add(upcast(rhs)); }

	template <class T>
	//! @brief if sub(lhs, rhs) exists, performs subtraction
	//!
	//! @param lhs 1st operand
	//! @param rhs 2nd operand
	//!
	constexpr auto sub(Sub<T> const &lhs,
			   Sub<T> const &rhs) noexcept { return upcast(lhs).sub(upcast(rhs)); }

	template <class T>
	//! @brief if mul(lhs, rhs) exists, performs multiplication
	//!
	//! @param lhs 1st operand
	//! @param rhs 2nd operand
	//!
	constexpr auto mul(Mul<T> const &lhs,
			   Mul<T> const &rhs) noexcept { return upcast(lhs).mul(upcast(rhs)); }

	template <class T>
	//! @brief if div(lhs, rhs) exists, performs division
	//!
	//! @param lhs 1st operand
	//! @param rhs 2nd operand
	//!
	constexpr auto div(Div<T> const &lhs,
			   Div<T> const &rhs) noexcept { return upcast(lhs).div(upcast(rhs)); }

	//! ----------------------------------------------------------------------------------- !//

	template <class T> constexpr auto operator +(Add<T> const &lhs, Add<T> const &rhs) noexcept { return add(upcast(lhs), upcast(rhs)); }
	template <class T> constexpr auto operator -(Sub<T> const &lhs, Sub<T> const &rhs) noexcept { return sub(upcast(lhs), upcast(rhs)); }
	template <class T> constexpr auto operator *(Mul<T> const &lhs, Mul<T> const &rhs) noexcept { return mul(upcast(lhs), upcast(rhs)); }
	template <class T> constexpr auto operator /(Div<T> const &lhs, Div<T> const &rhs) noexcept { return div(upcast(lhs), upcast(rhs)); }

	//! ----------------------------------------------------------------------------------- !//

	template<class T> constexpr T const &min(T const &a, T const &b) noexcept { return a < b ? a : b; }
	template<class T> constexpr T const &max(T const &a, T const &b) noexcept { return a < b ? b : a; }

	//! ----------------------------------------------------------------------------------- !//

	template<class T /** Offset **/,
		 class U /** Length **/>
	struct NumericSpan
	{
		T offset;
		U length;
	};

	template<class T, class U> constexpr T offset(NumericSpan<T, U> const &a) noexcept { return a.offset; }
	template<class T, class U> constexpr U length(NumericSpan<T, U> const &a) noexcept { return a.length; }

	//! ----------------------------------------------------------------------------------- !//

	template<class R, class ... Args> using FRef = R (&)(Args ...);
	template<class R, class ... Args> using FPtr = R (*)(Args ...);

}

#endif //! MICRO_LIBCORE_LIB_HH__GUARD