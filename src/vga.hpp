//
// Simple debugging VGA output.
//
// (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include "types.hpp"

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
