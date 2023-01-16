#include "lib.hpp"

// The "special" sauce, so to speak
#include "ets.hpp"
#include "vga.hpp"

void SvcTest() {
	// test a unknown syscall (some Phar Lap init code tests a value here and treats it like a pointer)
	auto unk = ets::Svc(static_cast<ets::SvcCall>(5));

	lib::Outs<vga::Outc>("Svc(5) result: ");
	lib::OutH<vga::Outc>(unk);
	lib::Outs<vga::Outc>("\n");

	// Let's treat it like a pointer like the aforementioned init code does.
	auto ptr = reinterpret_cast<u8*>(unk);
	lib::Outs<vga::Outc>("Svc(5) result treated as a pointer + 100: ");
	lib::OutH<vga::Outc>(ptr[100]);
	lib::Outs<vga::Outc>("\n");
}

extern "C" int _start() {
	// Nudge the VGA debug console past any ETS stuff
	vga::gState.row = 15;

	lib::Outs<vga::Outc>("Hello ETS Monitor World\n");
	lib::Outs<ets::Outc>("this should be printed by a ETS service call\n");

	SvcTest();

	// Loop forever
	while(true);

	return 0;
}
