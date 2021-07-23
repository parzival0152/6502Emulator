#pragma once
using Bit = bool;
using Byte = unsigned char;
using Word = unsigned short;


static constexpr Byte

	//LDA block
	LDA_IM	=	0xa9, // load A from imidiate
	LDA_Z	=	0xa5, // load A from zero page
	LDA_ZX	=	0xb5, // load A from zero page with X offset
	LDA_A	=	0xad, // laod A from absolute
	LDA_AX	=	0xbd, // laod A from absolute with X offset
	LDA_AY	=	0xb9, // laod A from absolute with Y offset
	LDA_IX	=	0xa1, // laod A from imidiate X
	LDA_IY	=	0xb1, // laod A from imidiate Y

	//LDX block
	LDX_IM	=	0xa2, // load X from imidiate
	LDX_Z	=	0xa6, // load X from zero page
	LDX_ZY	=	0xb6 , // load X from zero page with Y offset
	LDX_A	=	0xae, // laod X from absolute
	LDX_AY	=	0xbe, // laod X from absolute with Y offset

	//LDY block


	//STA block
	STA_Z	=	0x85, // put A in memory




	ADC_IM	=	0x69, // add with carry from imidate


	
	NOP		=	0xea; //no-op