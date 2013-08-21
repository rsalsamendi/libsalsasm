/*
	Copyright (c) 2013 Ryan Salsamendi

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
#ifndef __SALSASM_H__
#define __SALSASM_H__

#include <stdint.h>

#ifdef _MSC_VER
	#ifndef __cplusplus
		typedef unsigned char bool;
		#define true  1
		#define false 0
	#endif
#else
	#ifndef __cplusplus
		#include <stdbool.h>
	#endif
#endif


typedef enum X86Operation
{
	X86_INVALID = 0,
	X86_AAA, X86_AAD, X86_AAM, X86_AAS, X86_ADC, X86_ADD, X86_ADDPD,
	X86_ADDPS, X86_ADDSD, X86_ADDSS, X86_ADDSUBPD, X86_ADDSUBPS, X86_ADX,
	X86_AMX, X86_AND, X86_ANDNPD, X86_ANDNPS, X86_ANDPD, X86_ANDPS, X86_ARPL,
	X86_BLENDPD, X86_BLENDPS, X86_BLENDVPD, X86_BLENDVPS, X86_BOUND, X86_BSF,
	X86_BSR, X86_BSWAP, X86_BT, X86_BTC, X86_BTR, X86_BTS, X86_CALLN, X86_CALLF,
	X86_CBW, X86_CWDE, X86_CDQE, X86_CLC, X86_CLD, X86_CLFLUSH, X86_CLGI, X86_CLI,
	X86_CLTS, X86_CMC, X86_CMOVB, X86_CMOVNAE, X86_CMOVC, X86_CMOVBE, X86_CMOVNA,
	X86_CMOVL, X86_CMOVNGE, X86_CMOVLE, X86_CMOVNG, X86_CMOVNB, X86_CMOVAE,
	X86_CMOVNC, X86_CMOVNBE, X86_CMOVA, X86_CMOVNL, X86_CMOVGE, X86_CMOVNLE,
	X86_CMOVG, X86_CMOVNO, X86_CMOVNP, X86_CMOVPO, X86_CMOVNS, X86_CMOVNZ, X86_CMOVNE,
	X86_CMOVO, X86_CMOVP, X86_CMOVPE, X86_CMOVS, X86_CMOVZ, X86_CMOVE, X86_CMP,
	X86_CMPPD, X86_CMPPS, X86_CMPS, X86_CMPSB, X86_CMPSW, X86_CMPSD, X86_CMPSQ,
	X86_CMPSS, X86_CMPXCHG, X86_CMPXCHG8B, X86_CMPXCHG16B, X86_COMISD, X86_COMISS,
	X86_CPUID, X86_CRC32, X86_CVTDQ2PD, X86_CVTDQ2PS, X86_CVTPD2DQ, X86_CVTPD2PI,
	X86_CVTPD2PS, X86_CVTPI2PD, X86_CVTPI2PS, X86_CVTPS2DQ, X86_CVTPS2PD, X86_CVTPS2PI,
	X86_CVTSD2SI, X86_CVTSD2SS, X86_CVTSI2SD, X86_CVTSI2SS, X86_CVTSS2SD, X86_CVTSS2SI,
	X86_CVTTPD2DQ, X86_CVTTPD2PI, X86_CVTTPS2DQ, X86_CVTTPS2PI, X86_CVTTSD2SI, X86_CVTTSS2SI,
	X86_CWD, X86_CDQ, X86_CQO, X86_DAA, X86_DAS, X86_DEC, X86_DIV, X86_DIVPD,
	X86_DIVPS, X86_DIVSD, X86_DIVSS, X86_DPPD, X86_DPPS, X86_EMMS, X86_ENTER, X86_EXTRACTPS,
	X86_F2XM1, X86_FABS, X86_FADD, X86_FADDP, X86_FBLD, X86_FBSTP, X86_FCHS, X86_FCLEX,
	X86_FCMOVB, X86_FCMOVBE, X86_FCMOVE, X86_FCMOVNB, X86_FCMOVNBE, X86_FCMOVNE, X86_FCMOVNU,
	X86_FCMOVU, X86_FCOM, X86_FCOM2, X86_FCOMI, X86_FCOMIP, X86_FCOMP, X86_FCOMP3, X86_FCOMP5,
	X86_FCOMPP, X86_FCOS, X86_FDECSTP, X86_FDIV, X86_FDIVP, X86_FDIVR, X86_FDIVRP, X86_FEMMS, X86_FFREE,
	X86_FFREEP, X86_FIADD, X86_FICOM, X86_FICOMP, X86_FIDIV, X86_FIDIVR, X86_FILD, X86_FIMUL,
	X86_FINCSTP, X86_FINIT, X86_FIST, X86_FISTP, X86_FISTTP, X86_FISUB, X86_FISUBR,
	X86_FLD, X86_FLD1, X86_FLDCW, X86_FLDENV, X86_FLDL2E, X86_FLDL2T, X86_FLDLG2, X86_FLDLN2,
	X86_FLDPI, X86_FLDZ, X86_FMUL, X86_FMULP, X86_FNCLEX, X86_FNDISI, X86_FNENI, X86_FNINIT,
	X86_FNOP, X86_FNSAVE, X86_FNSETPM, X86_FNSTCW, X86_FNSTENV, X86_FNSTSW, X86_FPATAN,
	X86_FPREM, X86_FPREM1, X86_FPTAN, X86_FRNDINT, X86_FRSTOR, X86_FSAVE, X86_FSCALE, X86_FSIN,
	X86_FSINCOS, X86_FSQRT, X86_FST, X86_FSTCW, X86_FSTENV, X86_FSTP, X86_FSTP1, X86_FSTP8,
	X86_FSTP9, X86_FSTSW, X86_FSUB, X86_FSUBP, X86_FSUBR, X86_FSUBRP, X86_FTST, X86_FUCOM,
	X86_FUCOMI, X86_FUCOMIP, X86_FUCOMP, X86_FUCOMPP, X86_FWAIT, X86_WAIT, X86_FXAM, X86_FXCH,
	X86_FXCH4, X86_FXCH7, X86_FXRSTOR, X86_FXSAVE, X86_FXTRACT, X86_FYL2X, X86_FYL2XP1, X86_GETSEC,
	X86_HADDPD, X86_HADDPS, X86_HINT_NOP, X86_HLT, X86_HSUBPD, X86_HSUBPS, X86_IDIV, X86_IMUL,
	X86_IN, X86_INC, X86_INS, X86_INSB, X86_INSW, X86_INSD, X86_INSERTPS, X86_INT, X86_INT1, X86_INT3,
	X86_ICEBP, X86_INTO, X86_INVD, X86_INVEPT, X86_INVLPG, X86_INVLPGA, X86_INVVPID, X86_IRET, X86_IRETD,
	X86_IRETQ, X86_JB, X86_JNAE, X86_JC, X86_JBE, X86_JNA, X86_JCXZ, X86_JECXZ, X86_JRCXZ,
	X86_JL, X86_JNGE, X86_JLE, X86_JNG, X86_JMPN, X86_JMPF, X86_JNC, X86_JNB, X86_JAE,
	X86_JA, X86_JNBE, X86_JNL, X86_JGE, X86_JNLE, X86_JG, X86_JNO, X86_JPO, X86_JNP,
	X86_JNS, X86_JNZ, X86_JNE, X86_JO, X86_JP, X86_JPE, X86_JS, X86_JZ, X86_JE, X86_LAHF,
	X86_LAR, X86_LDDQU, X86_LDMXCSR, X86_LDS, X86_LEA, X86_LEAVE, X86_LES, X86_LFENCE,
	X86_LFS, X86_LGDT, X86_LGS, X86_LIDT, X86_LLDT, X86_LMSW, X86_LODS, X86_LODSB,
	X86_LODSW, X86_LODSD, X86_LODSQ, X86_LOOP, X86_LOOPNZ, X86_LOOPNE, X86_LOOPZ, X86_LOOPE,
	X86_LSL, X86_LSS, X86_LTR, X86_MASKMOVDQU, X86_MASKMOVQ, X86_MAXPD, X86_MAXPS,
	X86_MAXSD, X86_MAXSS, X86_MFENCE, X86_MINPD, X86_MINPS, X86_MINSD, X86_MINSS,
	X86_MONITOR, X86_MOV, X86_MOVAPD, X86_MOVAPS, X86_MOVBE, X86_MOVD, X86_MOVQ, X86_MOVDDUP,
	X86_MOVDQ2Q, X86_MOVDQA, X86_MOVDQU, X86_MOVHLPS, X86_MOVHPD, X86_MOVHPS, X86_MOVLHPS,
	X86_MOVLPD, X86_MOVLPS, X86_MOVMSKPD, X86_MOVMSKPS, X86_MOVNTDQ, X86_MOVNTDQA, X86_MOVNTI,
	X86_MOVNTPD, X86_MOVNTPS, X86_MOVNTQ, X86_MOVNTSS, X86_MOVNTSD, X86_MOVQ2DQ, X86_MOVS,
	X86_MOVSB, X86_MOVSW, X86_MOVSQ, X86_MOVSD, X86_MOVSHDUP, X86_MOVSLDUP, X86_MOVSS, X86_MOVSX,
	X86_MOVSXD, X86_MOVUPD, X86_MOVUPS, X86_MOVZX, X86_MPSADBW, X86_MUL, X86_MULPD, X86_MULPS,
	X86_MULSD, X86_MULSS, X86_MWAIT, X86_NEG, X86_NOP, X86_NOT, X86_OR, X86_ORPD,
	X86_ORPS, X86_OUT, X86_OUTS, X86_OUTSB, X86_OUTSW, X86_OUTSD, X86_PABSB,
	X86_PABSD, X86_PABSW, X86_PACKSSDW, X86_PACKSSWB, X86_PACKUSDW,
	X86_PACKUSWB, X86_PADDB, X86_PADDD, X86_PADDQ, X86_PADDSB, X86_PADDSW, X86_PADDUSB,
	X86_PADDUSW, X86_PADDW, X86_PALIGNR, X86_PAND, X86_PANDN, X86_PAUSE, X86_PAVGB,
	X86_PAVGW, X86_PBLENDVB, X86_PBLENDW, X86_PCMPEQB, X86_PCMPEQD, X86_PCMPEQQ,
	X86_PCMPEQW, X86_PCMPESTRI, X86_PCMPESTRM, X86_PCMPGTB, X86_PCMPGTD, X86_PCMPGTQ,
	X86_PCMPGTW, X86_PCMPISTRI, X86_PCMPISTRM, X86_PEXTRB, X86_PEXTRD, X86_PEXTRQ,
	X86_PEXTRW, X86_PFNACC, X86_PFPNACC, X86_PFCMPGE, X86_PFMIN, X86_PFRCP, X86_PFRSQRT, X86_PFMAX,
	X86_PFSQRT, X86_PFSUB, X86_PFADD, X86_PFCMPGT, X86_PFRCPIT1, X86_PFRSQIT1,
	X86_PFSUBR, X86_PFACC, X86_PFCMPEQ, X86_PFMUL, X86_PFRCPIT2, X86_PMULHRW, X86_PSWAPD,
	X86_PAVGUSB, X86_PHADDD, X86_PHADDSW, X86_PHADDW, X86_PHMINPOSUW, X86_PHSUBD, X86_PHSUBSW,
	X86_PHSUBW, X86_PI2FW, X86_PI2FD, X86_PF2IW, X86_PF2ID,
	X86_PINSRB, X86_PINSRD, X86_PINSRQ, X86_PINSRW, X86_PMADDUBSW, X86_PMADDWD,
	X86_PMAXSB, X86_PMAXSD, X86_PMAXSW, X86_PMAXUB, X86_PMAXUD, X86_PMAXUW, X86_PMINSB,
	X86_PMINSD, X86_PMINSW, X86_PMINUB, X86_PMINUD, X86_PMINUW, X86_PMOVMSKB, X86_PMOVSXBD,
	X86_PMOVSXBQ, X86_PMOVSXBW, X86_PMOVSXDQ, X86_PMOVSXWD, X86_PMOVSXWQ, X86_PMOVZXBD,
	X86_PMOVZXBQ, X86_PMOVZXBW, X86_PMOVZXDQ, X86_PMOVZXWD, X86_PMOVZXWQ, X86_PMULDQ,
	X86_PMULHRSW, X86_PMULHUW, X86_PMULHW, X86_PMULLD, X86_PMULLW, X86_PMULUDQ, X86_POP,
	X86_POPA, X86_POPAD, X86_POPCNT, X86_POPF, X86_POPFQ, X86_POPFD, X86_POR,
	X86_PREFETCH, X86_PREFETCHW, X86_PREFETCHNTA, X86_PREFETCHT0, X86_PREFETCHT1,
	X86_PREFETCHT2, X86_PSADBW, X86_PSHUFB, X86_PSHUFD, X86_PSHUFHW, X86_PSHUFLW,
	X86_PSHUFW, X86_PSIGNB, X86_PSIGND, X86_PSIGNW, X86_PSLLD,
	X86_PSLLDQ, X86_PSLLQ, X86_PSLLW, X86_PSRAD, X86_PSRAW, X86_PSRLD, X86_PSRLDQ,
	X86_PSRLQ, X86_PSRLW, X86_PSUBB, X86_PSUBD, X86_PSUBQ, X86_PSUBSB, X86_PSUBSW,
	X86_PSUBUSB, X86_PSUBUSW, X86_PSUBW, X86_PTEST, X86_PUNPCKHBW, X86_PUNPCKHDQ,
	X86_PUNPCKHQDQ, X86_PUNPCKHWD, X86_PUNPCKLBW, X86_PUNPCKLDQ, X86_PUNPCKLQDQ,
	X86_PUNPCKLWD, X86_PUSH, X86_PUSHA, X86_PUSHAD, X86_PUSHF, X86_PUSHFQ, X86_PUSHFD,
	X86_PXOR, X86_RCL, X86_RCPPS, X86_RCR, X86_RDMSR, X86_RDPMC, X86_RDTSC, X86_RDTSCP,
	X86_RETF, X86_RETN, X86_ROL, X86_ROR, X86_ROUNDPD, X86_ROUNDPS, X86_ROUNDSD,
	X86_ROUNDSS, X86_RSM, X86_RSQRTPS, X86_RSQRTSS, X86_SAHF, X86_SAL, X86_SHL,
	X86_SALC, X86_SETALC, X86_SAR, X86_SBB, X86_SCAS, X86_SCASB, X86_SCASW,
	X86_SCASD, X86_SCASQ, X86_SETB, X86_SETNAE, X86_SETC, X86_SETBE, X86_SETNA,
	X86_SETL, X86_SETNGE, X86_SETLE, X86_SETNG, X86_SETNB, X86_SETAE, X86_SETNC,
	X86_SETNBE, X86_SETA, X86_SETNL, X86_SETGE, X86_SETNLE, X86_SETG, X86_SETNO,
	X86_SETNP, X86_SETPO, X86_SETNS, X86_SETNZ, X86_SETNE, X86_SETO, X86_SETP,
	X86_SETPE, X86_SETS, X86_SETZ, X86_SETE, X86_SFENCE, X86_SGDT, X86_SKINIT, X86_SLDT, X86_SHLD, X86_SHR,
	X86_SHRD, X86_SHUFPD, X86_SHUFPS, X86_SIDT, X86_SMSW, X86_SQRTPD, X86_SQRTPS,
	X86_SQRTSD, X86_SQRTSS, X86_STC, X86_STD, X86_STGI, X86_STI, X86_STMXCSR, X86_STOS,
	X86_STOSB, X86_STOSW, X86_STOSD, X86_STOSQ, X86_STR, X86_SUB, X86_SUBPD,
	X86_SUBPS, X86_SUBSD, X86_SUBSS, X86_SWAPGS, X86_SYSCALL, X86_SYSENTER, X86_SYSEXIT,
	X86_SYSRET, X86_TEST, X86_UCOMISD, X86_UCOMISS, X86_UD, X86_UD1, X86_UD2, X86_UNPCKHPD,
	X86_UNPCKHPS, X86_UNPCKLPD, X86_UNPCKLPS, X86_VBLENDPD, X86_VBLENDPS,
	X86_VBLENDVPD, X86_VBLENDVPS, X86_VDPPD, X86_VDPPS, X86_VEXTRACTPS, X86_VINSERTPS,
	X86_VMOVNTDQA, X86_VMPSADBW, X86_VPACKUDSW, X86_VBLENDVB, X86_VPBLENDW,
	X86_VPCMPEQQ, X86_VPEXTRB, X86_VPEXTRD, X86_VPEXTRW, X86_VPHMINPOSUW,
	X86_VPINSRB, X86_VPINSRD, X86_VPINSRQ, X86_VPMAXSB, X86_VPMAXSD,
	X86_VMPAXUD, X86_VPMAXUW, X86_VPMINSB, X86_VPMINSD, X86_VPMINUD, X86_VPMINUW,
	X86_VPMOVSXBD, X86_VPMOVSXBQ, X86_VPMOVSXBW, X86_VPMOVSXWD, X86_VPMOVSXWQ,
	X86_VPMOVSXDQ, X86_VPMOVZXBD, X86_VPMOVZXBQ, X86_VPMOVZXBW, X86_VPMOVZXWD,
	X86_VPMOVZXWQ, X86_VPMOVZXDQ, X86_VPMULDQ, X86_VPMULLD, X86_VPTEST,
	X86_VROUNDPD, X86_VROUNDPS, X86_VROUNDSD, X86_VROUNDSS, X86_VPCMPESTRI,
	X86_VPCMPESTRM, X86_VPCMPGTQ, X86_VPCMPISTRI, X86_VPCMPISTRM, X86_VAESDEC,
	X86_VAESDECLAST, X86_VAESENC, X86_VAESENCLAST, X86_VAESIMC, X86_VAESKEYGENASSIST,
	X86_VPABSB, X86_VPABSD, X86_VPABSW, X86_VPALIGNR, X86_VPAHADD, X86_VPHADDW,
	X86_VPHADDSW, X86_VPHSUBD, X86_VPHSUBW, X86_VPHSUBSW, X86_VPMADDUBSW,
	X86_VPMULHRSW, X86_VPSHUFB, X86_VPSIGNB, X86_VPSIGND, X86_VPSIGNW, X86_VADDSUBPD,
	X86_VADDSUBPS, X86_VHADDPD, X86_VHADDPS, X86_VHSUBPD, X86_VHSUBPS, X86_VLDDQU,
	X86_VMOVDDUP, X86_VMOVHLPS, X86_VMOVSHDUP, X86_VMOVSLDUP, X86_VADDPD, X86_VADDSD,
	X86_VANPD, X86_VANDNPD, X86_VCMPPD, X86_VCMPSD, X86_VCOMISD,
	X86_VCVTDQ2PD, X86_VCVTDQ2PS, X86_VCVTPD2DQ, X86_VCVTPD2PS, X86_VCVTPS2DQ,
	X86_VCVTPS2PD, X86_VCVTSD2SI, X86_VCVTSD2SS, X86_VCVTSI2SD, X86_VCVTSS2SD,
	X86_VCVTTPD2DQ, X86_VCVTTPS2DQ, X86_VCVTTSD2SI, X86_VDIVPD, X86_VDIVSD,
	X86_VMASKMOVDQU, X86_VMAXPD, X86_VMAXSD, X86_VMINPD, X86_VMINSD, X86_VMOVAPD,
	X86_VMOVD, X86_VMOVQ, X86_VMOVDQA, X86_VMOVDQU, X86_VMOVHPD, X86_VMOVLPD,
	X86_VMOVMSKPD, X86_VMOVNTDQ, X86_VMOVNTPD, X86_VMOVSD, X86_VMOVUPD,
	X86_VMULPD, X86_VMULSD, X86_VORPD, X86_VPACKSSWB, X86_VPACKSSDW,
	X86_VPACKUSWB, X86_VPADDB, X86_VPADDW, X86_VPADDD, X86_VPADDQ, X86_VPADDSB,
	X86_VPADDSW, X86_VPADDUSB, X86_VPADDUSW, X86_VPAND, X86_VPANDN, X86_VPAVGB,
	X86_VPAVGW, X86_VPCMPEQB, X86_VPCMPEQW, X86_VPCMPEQD, X86_VPCMPGTB,
	X86_VPCMPGTW, X86_VPCMPGTD, X86_VPEXTSRW, X86_VPMADDWD,
	X86_VPMAXSW, X86_VPMAXUB, X86_VPMINSW, X86_VPMINUB, X86_VPMOVMSKB,
	X86_VPMULHUW, X86_VPMULHW, X86_VPMULLW, X86_VPMULUDQ, X86_VPOR,
	X86_VPSADBW, X86_VPSHUFD, X86_VPSHUFHW, X86_VPSHUFLW, X86_VPSLLDQ,
	X86_VPSLLW, X86_VPSLLD, X86_VPSLLQ, X86_VPSRAW, X86_VPSRAD,
	X86_VPSRLDQ, X86_VPSRLW, X86_VPSRLD, X86_VPSRLQ, X86_VPSUBB,
	X86_VPSUBW, X86_VPSUBD, X86_VPSQUBQ, X86_VPSUBSB, X86_VPSUBSW,
	X86_VPSUBUSB, X86_VPSUBUSW, X86_VPUNPCKHBW, X86_VPUNPCKHWD, X86_VPUNPCKHDQ,
	X86_VPUNPCKHQDQ, X86_VPUNPCKLBW, X86_VPUNPCKLWD, X86_VPUNPCKLDQ, X86_VPUNCKLQDQ,
	X86_VPXOR, X86_VSHUFPD, X86_VSQRTPD, X86_VSQRTSD, X86_VSUBPD, X86_VSUBSD,
	X86_VUCOMISD, X86_VUNPCKHPD, X86_VUNPCKHPS, X86_VUNPCKLPD, X86_VUNPCKLPS,
	X86_VXORPD, X86_VADDPS,  X86_VADDSS, X86_VANDPS, X86_VANDNPS, X86_VCMPPS,
	X86_VCMPSS, X86_VCOMISS, X86_VCVTSI2SS, X86_VCVTSS2SI, X86_VCVTTSS2SI, 
	X86_VDIVPS, X86_VLDMXCSR, X86_VMAXPS, X86_VMAXSS, X86_VMINPS, X86_VMINSS,
	X86_VMOVAPS, X86_VMOVHPS, X86_VMOVLHPS, X86_VMOVLPS, X86_VMOVMSKPS,
	X86_VMOVNTPS, X86_VMOVSS, X86_VMOVUPS, X86_VMULPS, X86_VMULSS, X86_VORPS,
	X86_VRCPPS, X86_VRCPSS, X86_VRSQRTPS, X86_VRSQRTSS, X86_VSQRTPS, X86_VSQRTSS,
	X86_VSTMXCSR, X86_VSUBPS, X86_VSUBSS, X86_VUCOMISS, X86_VXORPS,
	X86_VBROADCAST, X86_VEXTRACTF128, X86_VINSERTF128, X86_VPERMILPD, X86_VPERMILPS,
	X86_VPERM2F128, X86_VTESTPD, X86_VTESTPS, X86_VERR, X86_VERW, X86_VMCALL,
	X86_VMCLEAR, X86_VMLAUNCH, X86_VMPTRLD, X86_VMPTRST, X86_VMREAD, X86_VMFUNC,
	X86_VMRESUME, X86_VMWRITE, X86_VMXOFF, X86_VMXON,
	X86_VMLOAD, X86_VMMCALL, X86_VMRUN, X86_VMSAVE,
	X86_WBINVD, X86_WRMSR, X86_XADD, X86_XCHG, X86_XGETBV, X86_XLAT,
	X86_XLATB, X86_XOR, X86_XORPD, X86_XORPS, X86_XRSTOR, X86_XSAVE, X86_XSAVEOPT, X86_XSETBV,
	X86_OP_LENGTH
} X86Operation;

typedef enum X86OperandType
{
	X86_NONE = 0,
	X86_MEM,
	X86_IMMEDIATE,

	// Segment registers
	X86_CS, X86_SS, X86_DS, X86_ES, X86_FS, X86_GS,

	// Instruction Pointer
	X86_IP, X86_EIP, X86_RIP,

	// Flags
	X86_FLAGS, X86_EFLAGS, X86_RFLAGS,

	// GPRs
	X86_AL, X86_AH, X86_AX, X86_EAX, X86_RAX,
	X86_CL, X86_CH, X86_CX, X86_ECX, X86_RCX,
	X86_DL, X86_DH, X86_DX, X86_EDX, X86_RDX,
	X86_BL, X86_BH, X86_BX, X86_EBX, X86_RBX,
	X86_SPL, X86_SP, X86_ESP, X86_RSP,
	X86_BPL, X86_BP, X86_EBP, X86_RBP,
	X86_SIL, X86_SI, X86_ESI, X86_RSI,
	X86_DIL, X86_DI, X86_EDI, X86_RDI,
	X86_R8B, X86_R8W, X86_R8D, X86_R8,
	X86_R9B, X86_R9W, X86_R9D, X86_R9,
	X86_R10B, X86_R10W, X86_R10D, X86_R10,
	X86_R11B, X86_R11W, X86_R11D, X86_R11,
	X86_R12B, X86_R12W, X86_R12D, X86_R12,
	X86_R13B, X86_R13W, X86_R13D, X86_R13,
	X86_R14B, X86_R14W, X86_R14D, X86_R14,
	X86_R15B, X86_R15W, X86_R15D, X86_R15,

	// FPU, MMX
	X86_FPU_TAG, X86_FPU_STATUS, X86_FPU_CONTROL, X86_FPU_DATA, X86_FPU_IP, X86_FP_OPCODE,
	X86_ST0, X86_ST1, X86_ST2, X86_ST3, X86_ST4, X86_ST5, X86_ST6, X86_ST7,
	X86_MM0, X86_MM1, X86_MM2, X86_MM3, X86_MM4, X86_MM5, X86_MM6, X86_MM7,

	// SSE, AVX, PHI
	X86_MXCSR,
	X86_XMM0, X86_XMM1, X86_XMM2, X86_XMM3, X86_XMM4, X86_XMM5, X86_XMM6, X86_XMM7,
	X86_XMM8, X86_XMM9, X86_XMM10, X86_XMM11, X86_XMM12, X86_XMM13, X86_XMM14, X86_XMM15,
	X86_YMM0, X86_YMM1, X86_YMM2, X86_YMM3, X86_YMM4, X86_YMM5, X86_YMM6, X86_YMM7,
	X86_YMM8, X86_YMM9, X86_YMM10, X86_YMM11, X86_YMM12, X86_YMM13, X86_YMM14, X86_YMM15,
	X86_ZMM0, X86_ZMM1, X86_ZMM2, X86_ZMM3, X86_ZMM4, X86_ZMM5, X86_ZMM6, X86_ZMM7,
	X86_ZMM8, X86_ZMM9, X86_ZMM10, X86_ZMM11, X86_ZMM12, X86_ZMM13, X86_ZMM14, X86_ZMM15,

	// Control Registers
	X86_CR0, X86_CR2, X86_CR3, X86_CR4, X86_CR8,

	// Debug Registers
	X86_DR0, X86_DR1, X86_DR2, X86_DR3, X86_DR4, X86_DR5, X86_DR6, X86_DR7,

	// Descriptor Tables
	X86_IDTR, X86_GDTR, X86_LDTR, X86_TR
} X86OperandType;

typedef struct X86Operand
{
	X86OperandType operandType;
	X86OperandType components[2];
	X86OperandType segment;
	uint8_t size;
	uint8_t scale;
	int64_t immediate;
} X86Operand;

typedef enum X86InstructionPrefixes
{
	// Legacy prefixes

	// Group 1 Prefixes (lock and rep**)
	X86_LOCK,
	X86_REP,
	X86_REPE,
	X86_REPNE,

	// Group 2 Prefixes (segment and branch hints)
	X86_SEG_CS,
	X86_SEG_SS,
	X86_SEG_DS,
	X86_SEG_ES,
	X86_SEG_FS,
	X86_SEG_GS,

	X86_NOT_TAKEN,
	X86_TAKEN,

	// Group 3
	X86_OPERAND_SIZE,

	// Group 4
	X86_ADDRESS_SIZE,

	X86_REX,
	X86_VEX,
	X86_XOP,
} X86InstructionPrefixes;

typedef enum X86InstructionFlags
{
	X86_FLAG_NONE = 0,
	X86_FLAG_LOCK = 1,
	X86_FLAG_REP = 2,
	X86_FLAG_REPNE = 4,
	X86_FLAG_REPE = 8,

	// FIXME: This is a decoder flag really
	X86_FLAG_INSUFFICIENT_LENGTH = 16,
	X86_FLAG_INVALID_64BIT_MODE = 32,

	X86_FLAG_OPERAND_SIZE_OVERRIDE,
	X86_FLAG_ADDR_SIZE_OVERRIDE,

	X86_FLAG_SEGMENT_OVERRIDE_CS,
	X86_FLAG_SEGMENT_OVERRIDE_SS,
	X86_FLAG_SEGMENT_OVERRIDE_DS,
	X86_FLAG_SEGMENT_OVERRIDE_ES,
	X86_FLAG_SEGMENT_OVERRIDE_FS,
	X86_FLAG_SEGMENT_OVERRIDE_GS
} X86InstructionFlags;

typedef struct X86Instruction
{
	X86Operation op;
	X86Operand operands[4];
	uint8_t operandCount;
	uint16_t flags;
	size_t length;
	uint64_t rip;
} X86Instruction;

#define SIGN_EXTEND64(val, bytes) (int64_t)(((int64_t)(val)) | ((int64_t)((((int64_t)val) << ((8 - bytes) << 3)) & 0x8000000000000000ll) >> ((8 - (bytes)) << 3)))

typedef bool (*InstructionFetchCallback)(void* ctxt, size_t len, uint8_t* result);

#ifdef LIBSALSASM_EXPORTS
#ifdef WIN32
	#define LIBSALSASMAPI __declspec(dllexport)
#else
	#define LIBSALSASMAPI __attribute__ ((visibility ("default")))
#endif /* WIN32 */
#else // Import
#ifdef WIN32
	#define LIBSALSASMAPI __declspec(dllimport)
#else
	#define LIBSALSASMAPI
#endif /* WIN32 */
#endif /* LIBSALSASM_EXPORTS */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	LIBSALSASMAPI bool Disassemble16(uint16_t ip, InstructionFetchCallback fetch, void* ctxt, X86Instruction* instr);
	LIBSALSASMAPI bool Disassemble32(uint32_t eip, InstructionFetchCallback fetch, void* ctxt, X86Instruction* instr);
	LIBSALSASMAPI bool Disassemble64(uint64_t rip, InstructionFetchCallback fetch, void* ctxt, X86Instruction* instr);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __SALSASM_H__ */
