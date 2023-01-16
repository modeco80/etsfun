//
// A very tiny embedded library thing
//
// (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
//
// SPDX-License-Identifier: MIT

#pragma once

#include "types.hpp"

namespace lib {

	constexpr auto Strlen(const char* str) {
		auto newptr = str;
		while(*(++newptr));
		return (newptr - str);
	}

	template<auto* Outc>
	void Outs(const char* str) {
		auto len = Strlen(str);
		for (auto i = 0 ; i < len; ++i)
			Outc(str[i]);
	}

	template<auto* Outc, class T>
	void OutH(const T value) {
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
