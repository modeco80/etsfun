//
// A tiny test program.
//
// (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
//
// SPDX-License-Identifier: MIT
//

#include "lib.hpp"

// The "special" sauce, so to speak
#include "ets.hpp"
#include "vga.hpp"

void SvcTest() {
	// test a unknown syscall (some Phar Lap init code tests a value here and treats it like a pointer)
	auto unk = ets::Svc(static_cast<ets::SvcCall>(5));

	lib::Outs<vga::Outc>("Svc(5) result: ");
	lib::Outh<vga::Outc>(unk);
	lib::Outs<vga::Outc>("\n");

	// Let's treat it like a pointer like the aforementioned init code does.
	lib::Outs<vga::Outc>("Svc(5) result treated as a u8* + 100: ");
	lib::Outh<vga::Outc>(lib::BitCast<u8*>(unk)[100]);
	lib::Outs<vga::Outc>("\n");
}

extern "C" int _start() {
	// Nudge the VGA debug output past any ETS stuff just so we can see it
	vga::gState.row = 10;

	lib::Outs<vga::Outc>("Hello ETS Monitor World\n");
	lib::Outs<ets::Outc>("this should be printed by a ETS service call\n");

	// Do service call tests
	SvcTest();

	// Loop forever
	while(true);

	return 0;
}
