#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include "Definitions.h"



struct CPU
{
	static constexpr Word Stack = 0x0100;

	Byte MEM[0xffff];

	Byte A, X, Y; //registers

	Byte SP;//stack pointer

	Word PC; //program counter

	Byte PS; //program status register
	//NV-BDIZC

	void reset()
	{
		A = 0x0;
		X = 0x0;
		Y = 0x0;
		PS &= 0b11110111;
		PC = 0x0200;
		SP = 0x00;
		for (int i = 0; i < 0xffff; i++)
		{
			MEM[i] = 0;
		}
	}

	Byte fetchByte(Word address) {
		return MEM[address];
	}

	Word fetchWord(Word address) {//little endian fetch order
		Word temp = MEM[address + 1];
		temp <<= 8;
		temp += MEM[address];
		return temp;
	}

	Byte fetchNextByte() {
		return MEM[PC++];
	}

	Word fetchNextWord() {
		Byte a = fetchNextByte();
		Byte b = fetchNextByte();
		return (b << 8) + a;
	}

	void putByte(Word address, Byte data) {
		MEM[address] = data;
	}

	void putWord(Word address, Word data) {
		MEM[address] = data & 0x00ff;
		MEM[address + 1] = data >> 8;
	}

	void LDAFlags() {
		if (A == 0x0)
			PS |= 0x02;
		else
			PS &= 0b11111101;
		PS |= (A & 0b10000000);
	}

	void LDXFlags() {
		if (X == 0x0)
			PS |= 0x02;
		else
			PS &= 0b11111101;
		PS |= (X & 0b10000000);
	}

	void LDYFlags() {
		if (Y == 0x0)
			PS |= 0x02;
		else
			PS &= 0b11111101;
		PS |= (Y & 0b10000000);
	}

	void execute() {
		bool isRunning = true;
		while (isRunning)
		{
			Byte instruction = fetchNextByte();
			switch (instruction)
			{
			case NOP:
				isRunning = false;
				break;
#pragma region LDA
			case LDA_IM:
				A = fetchNextByte();
				LDAFlags();
				break;

			case LDA_Z:
				A = fetchByte(fetchNextByte());
				LDAFlags();
				break;

			case LDA_ZX:
				A = fetchByte(fetchNextByte() + X);
				LDAFlags();
				break;

			case LDA_A:
				A = fetchByte(fetchNextWord());
				LDAFlags();
				break;

			case LDA_AX:
				A = fetchByte(fetchNextWord() + X);
				LDAFlags();
				break;

			case LDA_AY:
				A = fetchByte(fetchNextWord() + Y);
				LDAFlags();
				break;

			case LDA_IX:
				A = fetchByte(fetchWord(fetchNextByte() + X));
				LDAFlags();
				break;

			case LDA_IY:
				A = fetchByte(fetchWord(fetchNextByte()) + Y);
				LDAFlags();
				break;
#pragma endregion
#pragma region LDX
			case LDX_IM:
				X = fetchNextByte();
				LDXFlags();
				break;

			case LDX_Z:
				X = fetchByte(fetchNextByte());
				LDXFlags();
				break;

			case LDX_ZY:
				X = fetchByte(fetchNextByte() + X);
				LDXFlags();
				break;

			case LDX_A:
				X = fetchByte(fetchNextWord());
				LDXFlags();
				break;

			case LDX_AY:
				X = fetchByte(fetchNextWord() + Y);
				LDXFlags();
				break;
#pragma endregion
#pragma region LDY
			case LDY_IM:
				Y = fetchNextByte();
				LDYFlags();
				break;

			case LDY_Z:
				Y = fetchByte(fetchNextByte());
				LDYFlags();
				break;

			case LDY_ZX:
				Y = fetchByte(fetchNextByte() + Y);
				LDYFlags();
				break;

			case LDY_A:
				Y = fetchByte(fetchNextWord());
				LDYFlags();
				break;

			case LDY_AX:
				Y = fetchByte(fetchNextWord() + X);
				LDYFlags();
				break;
#pragma endregion
#pragma region STA
			case STA_Z:
				putByte(fetchNextByte(), A);
				break;

			case STA_ZX:
				putByte(fetchNextByte() + X, A);
				break;

			case STA_A:
				putByte(fetchNextWord(), A);
				break;

			case STA_AX:
				putByte(fetchNextWord() + X, A);
				break;

			case STA_AY:
				putByte(fetchNextWord() + Y, A);
				break;

			case STA_IX:
				putByte(fetchWord(fetchNextByte() + X), A);
				break;

			case STA_IY:
				putByte(fetchWord(fetchNextByte()) + Y, A);
				break;

#pragma endregion

			default:
				break;
			}
		}
	}
};

int main()
{
	CPU cpu;
	cpu.reset();
	cpu.MEM[0x0200] = LDY_IM;
	cpu.MEM[0x0201] = 0x06;
	cpu.MEM[0x0202] = NOP;
	cpu.MEM[0x0006] = 0x00;
	cpu.MEM[0x0007] = 0x80;
	cpu.MEM[0x8004] = 0xf4;
	cpu.execute();
	std::cout << std::hex << (int)(cpu.Y) << std::endl;
	system("pause");
	return 0;
}