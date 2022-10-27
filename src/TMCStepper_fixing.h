#pragma once

namespace _TMC_FIXING
{

// BEGIN https://en.cppreference.com/w/cpp/types/add_reference
namespace detail {
 
template <class T>
struct type_identity { using type = T; };
 
template <class T>
auto try_add_rvalue_reference(int) -> type_identity<T&&>;
template <class T>
auto try_add_rvalue_reference(...) -> type_identity<T>;
 
} // namespace detail
 
template <class T>
struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {};

// END https://en.cppreference.com/w/cpp/types/add_reference
    
// BEGIN https://en.cppreference.com/w/cpp/utility/declval
template<typename T> constexpr bool always_false = false;
 
template<typename T>
typename add_rvalue_reference<T>::type declval() noexcept {
    static_assert(always_false<T>, "declval not allowed in an evaluated context");
}

// END https://en.cppreference.com/w/cpp/utility/declval

struct true_type {
    enum { value = true };
};
struct false_type {};
    enum { value = false };
};

// Since we don't have C++20 we need to do some ugly hacks to ensure compat.
// https://stackoverflow.com/questions/63253287/using-sfinae-to-detect-method-with-gcc
// Did you know that ATMEL AVR does not support standard C++ headers???
#define __DEF_HAS_METH( methName ) \
	template<typename T> \
	struct ___has_##methName \
	{ \
    template<typename C> \
    static constexpr auto test(...) -> _TMC_FIXING::false_type; \
		template<typename C> \
		static constexpr auto test(int) \
		-> decltype(static_cast<void>(_TMC_FIXING::declval<C>().methName(0)), _TMC_FIXING::true_type()); \
    using result_type       = decltype(test<T>(0)); \
    static const bool value = result_type::value; \
	}
#define __HAS_METH( className, methName ) \
	( ___has_##methName <className>::value )

__DEF_HAS_METH( setMISO );
__DEF_HAS_METH( setMOSI );
__DEF_HAS_METH( setSCLK );

#define SPI_SET_PIN_HELPER( pinDescName ) \
	template <bool hasPin> \
	struct _spiInitHelper_##pinDescName \
	{}; \
	template <> \
	struct _spiInitHelper_##pinDescName <true> \
	{ \
		template <typename SPIClassT> \
		static void spiSet##pinDescName( SPIClassT& spi, uint16_t pin )	{ spi.set##pinDescName( pin ); } \
	}; \
	template <> \
	struct _spiInitHelper_##pinDescName <false> \
	{ \
		template <typename SPIClassT> \
		static void spiSet##pinDescName( SPIClassT& spi, uint16_t pin )	{} \
	}

SPI_SET_PIN_HELPER( MISO );
SPI_SET_PIN_HELPER( MOSI );
SPI_SET_PIN_HELPER( SCLK );

#define SPI_INIT_PIN( spi, pinDescName, val ) _spiInitHelper_##pinDescName <__HAS_METH(SPIClass, set##pinDescName)> ::spiSet##pinDescName( spi, val )
