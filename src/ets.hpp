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
		Putc = 1,
		GetControlBlock = 5
	};

	/** Returned by GetControlBlock **/
	struct [[gnu::packed]] ControlBlock {
		u8 filler[0x64];
		u8 interfaceVersion; 	// should be 0x1 for this version
	};

	// Service call helpers (in svccall.asm)
	extern "C" {
		[[gnu::fastcall]] u32 ets_svccall0(u16 no);
		[[gnu::fastcall]] u32 ets_svccall1(u16 no, u32 arg);
		[[gnu::fastcall]] u32 ets_svccall2(u16 no, u32 arg, u32 arg2);
	}

	inline u32 Svc(SvcCall no) {
		return ets_svccall0(static_cast<u16>(no));
	}

	inline u32 Svc(SvcCall no, u32 arg) {
		return ets_svccall1(static_cast<u16>(no), arg);
	}

	inline u32 Svc(SvcCall no, u32 arg, u32 arg2) {
		return ets_svccall2(static_cast<u16>(no), arg, arg2);
	}

	// Service call interfaces

	namespace svc {
		inline ControlBlock* GetControlBlock() {
			return lib::BitCast<ControlBlock*>(Svc(SvcCall::GetControlBlock, 1));
		}

		inline void Outc(char c) {
			// Use the Monitor's putc service.
			static_cast<void>(Svc(SvcCall::Putc, static_cast<u32>(c)));
		}
	} // namespace svc

} // namespace ets
