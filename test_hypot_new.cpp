/*
g++ -DOLDOLDWAY=1 -o test_hypot_old2 test_hypot_new.cpp
./test_hypot_old2 > test_hypot_old2.txt

g++ -DOLDWAY=1 -o test_hypot_old test_hypot_new.cpp
./test_hypot_old > test_hypot_old.txt

g++ -UOLDWAY -o test_hypot_new test_hypot_new.cpp
./test_hypot_new > test_hypot_new.txt

kdiff3 test_hypot_old2.txt test_hypot_old.txt test_hypot_new.txt
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

  namespace __detail
  {
    // Avoid including all of <algorithm>
    template<typename _Tp>
      constexpr _Tp
      __fmax3(_Tp __x, _Tp __y, _Tp __z)
      { return std::max(std::max(__x, __y), __z); }

    template<typename _Tp>
      constexpr _Tp
      __hypot3(_Tp __x, _Tp __y, _Tp __z)
      {
	if (std::isnan(__x) || std::isnan(__y) || std::isnan(__z))
	  return std::numeric_limits<_Tp>::quiet_NaN();
	else
	  {
	    __x = std::abs(__x);
	    __y = std::abs(__y);
	    __z = std::abs(__z);
	    const auto __amax = __fmax3(__x, __y, __z);
	    if (__amax == _Tp{0})
	      return _Tp{0};
	    else if (std::isinf(__amax))
	      return std::numeric_limits<_Tp>::infinity();
	    else
	      {
#if defined(OLDOLDWAY)
		__x /= __amax;
		__y /= __amax;
		__z /= __amax;
		return __amax * std::sqrt(__x * __x + __y * __y + __z * __z);
#elif defined(OLDWAY)
		const auto __scale = _Tp{1} / __amax;
		__x *= __scale;
		__y *= __scale;
		__z *= __scale;
		return std::sqrt(__x * __x + __y * __y + __z * __z) / __scale;
#else
		const auto __scale = _Tp{1} / __amax;
		const auto __l0 = __scale * std::min(__z, std::max(__x, __y));
		const auto __l1 = __scale * std::min(__y, __x);
		// Add the two smaller values first.
		const auto __lo = __l0 * __l0 + __l1 * __l1;
		return std::sqrt(_Tp{1} + __lo) / __scale;
#endif
	      }
	  }
      }
  }

  /**
   * Return the three-dimensional hypoteneuse @f$ \sqrt{x^2 + y^2 + z^2} @f$
   * for @c float arguments x, y, and z.
   */
  constexpr inline float
  hypot(float __x, float __y, float __z)
  { return __detail::__hypot3<float>(__x, __y, __z); }

  /**
   * Return the three-dimensional hypoteneuse @f$ \sqrt{x^2 + y^2 + z^2} @f$
   * for <tt>long double</tt> arguments x, y, and z.
   */
  constexpr inline long double
  hypot(long double __x, long double __y, long double __z)
  { return __detail::__hypot3<long double>(__x, __y, __z); }

  /**
   * Return the three-dimensional hypoteneuse @f$ \sqrt{x^2 + y^2 + z^2} @f$
   * for real arguments x, y, and z.
   */
  template<typename _Tp, typename _Up, typename _Vp>
    constexpr typename __gnu_cxx::__promote_3<_Tp, _Up, _Vp>::__type
    hypot(_Tp __x, _Up __y, _Vp __z)
    {
      using __type = typename __gnu_cxx::__promote_3<_Tp, _Up, _Vp>::__type;
      return __detail::__hypot3<__type>(__x, __y, __z);
    }

template<typename _Tp>
  void
  test_hypot()
  {
    constexpr _Tp inf = std::numeric_limits<_Tp>::infinity();
    constexpr _Tp nan = std::numeric_limits<_Tp>::quiet_NaN();
    constexpr _Tp tiny = std::numeric_limits<_Tp>::epsilon();
    constexpr _Tp huge = std::numeric_limits<_Tp>::max() / 16;
    constexpr _Tp subn = std::numeric_limits<_Tp>::min();
    //const long double sqrt2 = std::sqrt(2.0L);
    const _Tp sqrt2 = std::sqrt(_Tp{2});

    std::cout << '\n';
    std::cout.precision(std::numeric_limits<_Tp>::max_digits10);
    const auto width = 8 + std::cout.precision();

    std::cout << "hypot(inf,   1,   1) = " << hypot(inf, _Tp{1}, _Tp{1}) << '\n';
    std::cout << "hypot(inf, inf,   1) = " << hypot(inf, inf, _Tp{1}) << '\n';
    std::cout << "hypot(inf, inf, inf) = " << hypot(inf, inf, inf) << '\n';

    std::cout << "hypot(nan,   1,   1) = " << hypot(nan, _Tp{1}, _Tp{1}) << '\n';
    std::cout << "hypot(nan, nan,   1) = " << hypot(nan, nan, _Tp{1}) << '\n';
    std::cout << "hypot(nan, nan, nan) = " << hypot(nan, nan, nan) << '\n';

    std::cout << "huge = " << huge << '\n';
    std::cout << "hypot(huge,    1,   1)                  = " << hypot(huge, _Tp{1}, _Tp{1}) / huge << '\n';
    std::cout << "hypot(huge, huge,   1) / huge - sqrt(2) = "
              << hypot(huge, huge, _Tp{1}) / huge - sqrt2 << '\n';
    std::cout << "hypot(2*huge, 3*huge, 6*huge) / huge = "
              << hypot(_Tp{2} * huge, _Tp{3} * huge, _Tp{6} * huge) / huge << '\n';

    std::cout << "tiny = " << tiny << '\n';
    std::cout << "hypot(tiny,    1,   1) - sqrt(2)     = "
              << hypot(tiny, _Tp{1}, _Tp{1}) - sqrt2 << '\n';
    std::cout << "hypot(tiny, tiny,   1) - 1           = "
              << hypot(tiny, tiny, _Tp{1}) - _Tp{1} << '\n';
    std::cout << "hypot(2*tiny, 3*tiny, 6*tiny) / tiny = "
              << hypot(_Tp{2} * tiny, _Tp{3} * tiny, _Tp{6} * tiny) / tiny << '\n';

    std::cout << "subn = " << subn << '\n';
    std::cout << "hypot(subn,    1,   1) - sqrt(2)     = "
              << hypot(subn, _Tp{1}, _Tp{1}) - sqrt2 << '\n';
    std::cout << "hypot(subn, subn,   1) - 1           = "
              << hypot(subn, subn, _Tp{1}) - _Tp{1} << '\n';
    std::cout << "hypot(2*subn, 3*subn, 6*subn) / subn = "
              << hypot(_Tp{2} * subn, _Tp{3} * subn, _Tp{6} * subn) / subn << '\n';
  }

int
main()
{
  test_hypot<float>();
  test_hypot<double>();
  test_hypot<long double>();

  return 0;
}
