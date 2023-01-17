//
// A tiny test program.
//
// (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
//
// SPDX-License-Identifier: MIT
//

#include "lib.hpp"

// VGA debug output
#include "vga.hpp"

// The "special" sauce, so to speak
#include "ets.hpp"

void SvcTest() {
	auto controlBlock = ets::svc::GetControlBlock();

	lib::Outs<vga::Outc>("GetControlBlock/Svc(5) result: ");
	lib::Outh<vga::Outc>(lib::BitCast<u32>(controlBlock));
	lib::Outs<vga::Outc>("\n");

	lib::Outs<vga::Outc>("GetControlBlock/Svc(5) interface version: ");
	lib::Outh<vga::Outc>(controlBlock->interfaceVersion);
	lib::Outs<vga::Outc>("\n");
}

extern "C" int _start() {
	// Nudge the VGA debug output past any ETS stuff just so we can see it
	vga::gState.row = 10;

	lib::Outs<vga::Outc>("Hello ETS Monitor World\n");
	lib::Outs<ets::svc::Outc>("this should be printed by a ETS service call\n");

	// Do service call tests
	SvcTest();

	// Loop forever
	while(true);

	return 0;
}
