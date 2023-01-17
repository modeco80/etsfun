//
// Stuff for interacting with the Phar Lap ETS kernel.
//
// (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include "types.hpp"

namespace ets {

	/** Known service calls. */
	enum class SvcCall : u16 {
		Putc = 1
	};

	extern "C" [[gnu::fastcall]] u32 __ets_svccall0(u16 no);
	extern "C" [[gnu::fastcall]] u32 __ets_svccall1(u16 no, u32 arg);

	inline u32 Svc(SvcCall no) {
		return __ets_svccall0(static_cast<u16>(no));
	}

	inline u32 Svc(SvcCall no, u32 arg) {
		return __ets_svccall1(static_cast<u16>(no), arg);
	}

	inline void Outc(char c) {
		// use the kernel's putc service.
		static_cast<void>(Svc(SvcCall::Putc, static_cast<u32>(c)));
	}
} // namespace ets
