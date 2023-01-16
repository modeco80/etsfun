#pragma once
// A very tiny embedded library thing

using u8 = unsigned char;
using s8 = char;
using u16 = unsigned short;
using s16 = short;
using u32 = unsigned int;
using s32 = int;

namespace lib {

	constexpr auto Strlen(const char* str) {
		auto newptr = str;
		while(*(++newptr));
		return (newptr - str);
	}

	// Very simple VGA output. Kinda sucks
	namespace vga {

		struct VgaState {
			u8 row = 0;
			u8 column = 0;

			u8 color = 0;

			constexpr VgaState() {
				Reset();
			}

			constexpr void Reset() {
				row = 0;
				column = 0;
				color = VgaColor(0xf, 0x1);
			}

			void NewLine() {
				row++;
				column = 0;
			}

			void CarriageReturn() {
				column = 0;
			}

			constexpr static u8 VgaColor(u8 fg, u8 bg) {
				return fg | bg << 4;
			}

			constexpr static u16 VgaTextEntry(u8 character, u8 color) {
				return static_cast<u16>(character) | static_cast<u16>(color) << 8;
			}

			static void OutcAt(char c, u8 x, u8 y, u8 color) {
				reinterpret_cast<u16*>(0xb8000)[y * 80 + x] = VgaTextEntry(static_cast<u8>(c), color);
			}

			void Outc(char c) {
				if(c == '\r')
					CarriageReturn();

				if(c == '\n')
					return NewLine();

				OutcAt(c, column, row, color);

				if(++column == 80) {
					column = 0;
					if(++row == 25)
						row = 0;
				}
			}
		};

		constinit static VgaState gState;

		void Outc(char c) {
			gState.Outc(c);
		}

	} // namespace vga

	template<auto* Outc = vga::Outc>
	void Outs(const char* str) {
		auto len = Strlen(str);
		for (auto i = 0 ; i < len; ++i)
			Outc(str[i]);
	}

	template<class T, auto* Outc = vga::Outc>
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

	// Stuff for interacting with ETS (doesn't seem to work ATM)
	namespace ek {
		extern "C" u32 ets_syscall_helper(u16 no, u16 arg);
	}

} // namespace lib
