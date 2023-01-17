//
// A very tiny embedded library thing
//
// (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include "types.hpp"

namespace lib {

	/** identical to std::bit_cast<To, From> **/
	template<class To, class From> requires(sizeof(To) == sizeof(From))
	constexpr To BitCast(From from) {
		return __builtin_bit_cast(To, from);
	}

	constexpr auto Strlen(const char* str) {
		auto newptr = str;
		while(*(++newptr));
		return (newptr - str);
	}

	/**
	 * Output a string.
	 *
	 * \tparm Outc A function which takes a character to print.
	 * \param[in] str String.
	 */
	template<auto* Outc>
	void Outs(const char* str) {
		auto len = Strlen(str);
		for (auto i = 0 ; i < len; ++i)
			Outc(str[i]);
	}

	/**
	 * Output a hex value.
	 *
	 * \tparm Outc A function which takes a character to print.
	 * \param[in] value Value.
	 */
	template<auto* Outc, class T>
	void Outh(const T value) {
		constexpr auto NibLUT = "0123456789abcdef";

		Outc('0');
		Outc('x');

		auto shiftCount = sizeof(T) * 8; // bits
		while(shiftCount) {
			shiftCount -= 4; // take away a nibble at a time
			Outc(NibLUT[ (value >> shiftCount) & 0x0f ]);
		}
	}



} // namespace lib
