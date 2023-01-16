#include "lib.hpp"

extern "C" int _start() {
	lib::Outs("Hello ETS Monitor World\nThe number of the day is: ");
	lib::OutH(0xABCDDCBA);

	// test a syscall (this does nothing ATM, though it's "supposed" to print a character)
	lib::ek::ets_syscall_helper(1, 't');
	return 0;
}
