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

	Bit C : 1; //status flags
	Bit Z : 1;
	Bit I : 1;
	Bit D : 1;
	Bit B : 1;
	Bit V : 1;
	Bit N : 1;

	void reset()
	{
		A = 0x0;
		X = 0x0;
		Y = 0x0;
		D = 0x0;
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
		Z = (A == 0x00);
		N = ((A & 0b10000000) > 0);
	}

	void LDXFlags() {
		Z = (X == 0x00);
		N = ((X & 0b10000000) > 0);
	}

	void LDYFlags() {
		Z = (Y == 0x00);
		N = ((Y & 0b10000000) > 0);
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

			case LDX_IM:
				X = fetchNextByte();
				LDXFlags();
				break;

			case LDX_Z:
				X = fetchByte(fetchNextByte());
				LDXFlags();
				break;

			case LDX_ZY:
				A = fetchByte(fetchNextByte() + X);
				LDXFlags();
				break;

			case LDX_A:
				A = fetchByte(fetchNextWord());
				LDXFlags();
				break;

			case LDX_AY:
				X = fetchByte(fetchNextWord() + Y);
				LDXFlags();
				break;

			case STA_Z:
				putByte(fetchNextByte(), A);
				break;

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
	cpu.Y = 0x04;
	cpu.MEM[0x0200] = LDA_IY;
	cpu.MEM[0x0201] = 0x06;
	cpu.MEM[0x0202] = NOP;
	cpu.MEM[0x0006] = 0x00;
	cpu.MEM[0x0007] = 0x80;
	cpu.MEM[0x8004] = 0xf4;
	cpu.execute();
	std::cout << std::bitset<16>(cpu.A) << std::endl;
	system("pause");
	return 0;
}