#pragma once
using Bit = bool;
using Byte = unsigned char;
using Word = unsigned short;


static constexpr Byte

	//LDA block
	LDA_IM	=	0xa9, // load A from imidiate
	LDA_Z	=	0xa5, // load A from zero page
	LDA_ZX	=	0xb5, // load A from zero page with X offset
	LDA_A	=	0xad, // load A from absolute
	LDA_AX	=	0xbd, // load A from absolute with X offset
	LDA_AY	=	0xb9, // load A from absolute with Y offset
	LDA_IX	=	0xa1, // load A from indexed indirect X
	LDA_IY	=	0xb1, // load A from indirect indexed Y

	//LDX block
	LDX_IM	=	0xa2, // load X from imidiate
	LDX_Z	=	0xa6, // load X from zero page
	LDX_ZY	=	0xb6, // load X from zero page with Y offset
	LDX_A	=	0xae, // laod X from absolute
	LDX_AY	=	0xbe, // laod X from absolute with Y offset

	//LDY block
	LDY_IM	=	0xa0, // load Y from imidiate
	LDY_Z	=	0xa4, // load Y from zero page
	LDY_ZX	=	0xb4, // load Y from zero page with X offset
	LDY_A	=	0xac, // laod Y from absolute
	LDY_AX	=	0xbc, // laod Y from absolute with X offset

	//STA block
	STA_Z	=	0x85, // put A in zero page
	STA_ZX	=	0x95, // put A in zero page with X offset
	STA_A	=	0x8d, // put A in absolute
	STA_AX	=	0x9d, // put A in absolute with X offset
	STA_AY	=	0x99, // put A in absolute with Y offset
	STA_IX	=	0x81, // put A in indexed indirect X
	STA_IY	=	0x91, // put A in indirect indexed Y




	ADC_IM	=	0x69, // add with carry from imidate


	
	NOP		=	0xea; //no-op