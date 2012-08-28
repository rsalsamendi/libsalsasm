/*
Copyright (c) 2012 Ryan Salsamendi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "salsasm_types.h"


typedef bool (*DecodeOperandsFunc)(X86DecoderState* state);

static const X86Operation primaryOpCodeTableArithmetic[] =
{
	X86_ADD, X86_ADC, X86_AND, X86_XOR,
	X86_OR, X86_SBB, X86_SUB, X86_CMP
};

static const X86OperandType primaryOpCodeModRm[5][8] =
{
	// 8bit
	{X86_AL, X86_CL, X86_DL, X86_BL, X86_AH, X86_CH, X86_DH, X86_BH},

	// 16bit
	{X86_AX, X86_CX, X86_DX, X86_BX, X86_SP, X86_BP, X86_SI, X86_DI},

	// 32bit
	{X86_EAX, X86_ECX, X86_EDX, X86_EBX, X86_ESP, X86_EBP, X86_ESI, X86_EDI},

	// 64bit
	{X86_MM0, X86_MM1, X86_MM2, X86_MM3, X86_MM4, X86_MM5, X86_MM6, X86_MM7},

	// 128bit
	{X86_XMM0, X86_XMM1, X86_XMM2, X86_XMM3, X86_XMM4, X86_XMM5, X86_XMM6, X86_XMM7},
};

typedef enum ModRMDisplacementEncoding
{
	X86_DISP_NONE = 0,
	X86_DISP8,
	X86_DISP16,
	X86_DISP32,
	X86_DISP64
} ModRMDisplacementEncoding;

static bool DecodeModRm8(X86DecoderState* state)
{
	uint8_t modRm;
	uint8_t mod;

	if (!state->fetch(state->ctxt, 1, &modRm))
		return false;

	// Source is a GPR
	state->instr->operands[1].operandType = (X86OperandType)(X86_AX + (modRm & 7));

	mod = (modRm >> 6);
	if (mod == 3)
	{
		// Both source and destination are GPRs
		state->instr->operands[0].operandType = (X86OperandType)(X86_AX + ((modRm >> 3) & 7));
	}
	else
	{
		// Destination is memory
		state->instr->operands[0].operandType = X86_MEM;

		// R/M field == 4 indicates presence of SIB byte
		if ((modRm & 0x38) == 0x20)
		{
			uint8_t sib;
			if (!state->fetch(state->ctxt, 1, &sib))
				return false;

			state->instr->operands[0].scale = (sib >> 6);
			state->instr->operands[0].components[0] = (X86OperandType)(X86_EAX + ((sib >> 3) & 7));
			state->instr->operands[0].components[1] = (X86OperandType)(X86_EAX + (sib & 7));

			if (state->instr->operands[0].components[0] == X86_ESP)
				state->instr->operands[0].components[0] = X86_NONE;
			if ((mod == 0) && (state->instr->operands[0].components[1] == X86_EBP))
				state->instr->operands[0].components[1] = X86_NONE;
		}

		// The mod bits tell how many bytes in the displacement
		if (mod)
		{
			uint16_t disp;
			if (!state->fetch(state->ctxt, mod, (uint8_t*)&disp))
				return false;
			state->instr->operands[0].immediate = (int64_t)disp;
		}
	}

	return true;
}


static bool DecodeModRm16(X86DecoderState* state)
{
	uint8_t modRm;

	if (!state->fetch(state->ctxt, 1, &modRm))
		return false;

	return true;
}


static bool DecodeModRm32(X86DecoderState* state)
{
	uint8_t modRm;

	if (!state->fetch(state->ctxt, 1, &modRm))
		return false;

	return true;
}


static bool DecodeModRm64(X86DecoderState* state)
{
	uint8_t modRm;

	if (!state->fetch(state->ctxt, 1, &modRm))
		return false;

	return true;
}


static bool DecodeImmediate8(X86DecoderState* state)
{
	uint8_t imm;

	if (!state->fetch(state->ctxt, 1, &imm))
		return false;

	state->instr->operands[0].operandType = X86_AL;
	state->instr->operands[0].size = 1;

	state->instr->operands[1].operandType = X86_IMMEDIATE;
	state->instr->operands[1].immediate = (int64_t)imm;

	return true;
}


static bool DecodeImmediate16(X86DecoderState* state)
{
	uint16_t imm;

	if (!state->fetch(state->ctxt, 2, (uint8_t*)&imm))
		return false;

	state->instr->operands[0].operandType = X86_AX;
	state->instr->operands[0].size = 2;

	state->instr->operands[1].operandType = X86_IMMEDIATE;
	state->instr->operands[1].immediate = (int64_t)imm;

	return true;
}


static bool DecodeImmediate32(X86DecoderState* state)
{
	uint32_t imm;

	if (!state->fetch(state->ctxt, 4, (uint8_t*)&imm))
		return false;

	state->instr->operands[0].operandType = X86_EAX;
	state->instr->operands[0].size = 4;

	state->instr->operands[1].operandType = X86_IMMEDIATE;
	state->instr->operands[1].immediate = (int64_t)imm;

	return true;
}


static bool DecodeImmediate64(X86DecoderState* state)
{
	uint32_t imm;

	if (!state->fetch(state->ctxt, 4, (uint8_t*)&imm))
		return false;

	state->instr->operands[0].operandType = X86_RAX;
	state->instr->operands[0].size = 8;

	state->instr->operands[1].operandType = X86_IMMEDIATE;
	state->instr->operands[1].immediate = (int64_t)imm;

	return true;
}


static const DecodeOperandsFunc primaryOpcodeArithmeticOperandDecoder[3][6] =
{
	// X86_16BIT
	{
		DecodeModRm8, DecodeModRm16, DecodeModRm8,
		DecodeModRm16, DecodeImmediate8, DecodeImmediate16,
	},

	// X86_32BIT
	{
		DecodeModRm8, DecodeModRm32, DecodeModRm8, DecodeModRm32,
		DecodeImmediate8, DecodeImmediate32
	},

	// X86_64BIT
	{
		DecodeModRm8, DecodeModRm32, DecodeModRm8, DecodeModRm32,
		DecodeImmediate8, DecodeImmediate32
	},
};

// See Table A-1 Primary Opcode Map (One-byte Opcodes) AMD 24594_APM_v3.pdf
bool DecodePrimaryOpcodeMap(X86DecoderState* state)
{
	uint8_t op;
	uint8_t row;
	uint8_t col;

	// Grab a byte from the machine
	if (!state->fetch(state->ctxt, 1, &op))
		return false;

	row  = ((op >> 4) & 0xf);
	col = (op & 0xf);

	// Simple Arithmetic Instructions
	if ((row < 3) && ((col & (~0x8)) < 6))
	{
		const uint8_t reverseOperands = (col & 4);

		state->instr->op = primaryOpCodeTableArithmetic[row];
		state->instr->operandCount = 2;

		if (!primaryOpcodeArithmeticOperandDecoder[state->operandSize][col](state))
			return false;

		if (reverseOperands)
		{
			X86Operand temp;
			temp = state->instr->operands[1];
			state->instr->operands[1] = state->instr->operands[0];
			state->instr->operands[0] = temp;
		}
	}
	else
	{
	}

	return false;
}