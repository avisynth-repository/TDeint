/*
**                TDeinterlace v1.1 for Avisynth 2.5.x
**
**   TDeinterlace is a bi-directionally motion adaptive deinterlacer.
**   It also uses a couple modified forms of ela interpolation which 
**   help to reduce "jaggy" edges in places where interpolation must 
**   be used. TDeinterlace currently supports YV12 and YUY2 colorspaces.
**   
**   Copyright (C) 2004-2007 Kevin Stone
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this program; if not, write to the Free Software
**   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "memset_simd.h"

void fmemset_16_SSE2(unsigned char* p, __m128 val, int sizec)
{
	_asm 
	{
		mov edi,p
		xor eax,eax
		mov ecx,sizec
		movdqa xmm0,val
		align 16
lx64:
		sub ecx,64
		cmp ecx,eax
		jl lx16pre
		movntdq [edi],xmm0
		movntdq [edi+16],xmm0
		movntdq [edi+32],xmm0
		movntdq [edi+48],xmm0
		lea edi,[edi+64]
		jmp lx64
lx16pre:
		add ecx,64
		align 16
lx16:
		sub ecx,16
		cmp ecx,eax
		jl lxend
		movntdq [edi],xmm0
		lea edi,[edi+16]
		jmp lx16
lxend:
		sfence
	}
}

void fmemset_16_iSSE(unsigned char* p, __int64 val, int sizec)
{
	_asm 
	{
		mov edi,p
		xor eax,eax
		mov ecx,sizec
		movq mm0,val
		align 16
lx64:
		sub ecx,64
		cmp ecx,eax
		jl lx16pre
		movntq [edi],mm0
		movntq [edi+8],mm0
		movntq [edi+16],mm0
		movntq [edi+24],mm0
		movntq [edi+32],mm0
		movntq [edi+40],mm0
		movntq [edi+48],mm0
		movntq [edi+56],mm0
		lea edi,[edi+64]
		jmp lx64
lx16pre:
		add ecx,64
		align 16
lx16:
		sub ecx,16
		cmp ecx,eax
		jl lxend
		movntq [edi],mm0
		movntq [edi+8],mm0
		lea edi,[edi+16]
		jmp lx16
lxend:
		sfence
		emms
	}
}

void fmemset_16_MMX(unsigned char* p, __int64 val, int sizec)
{
	_asm 
	{
		mov edi,p
		xor eax,eax
		mov ecx,sizec
		movq mm0,val
		align 16
lx64:
		sub ecx,64
		cmp ecx,eax
		jl lx16pre
		movq [edi],mm0
		movq [edi+8],mm0
		movq [edi+16],mm0
		movq [edi+24],mm0
		movq [edi+32],mm0
		movq [edi+40],mm0
		movq [edi+48],mm0
		movq [edi+56],mm0
		lea edi,[edi+64]
		jmp lx64
lx16pre:
		add ecx,64
		align 16
lx16:
		sub ecx,16
		cmp ecx,eax
		jl lxend
		movq [edi],mm0
		movq [edi+8],mm0
		lea edi,[edi+16]
		jmp lx16
lxend:
		emms
	}
}

void fmemset_8_iSSE(unsigned char* p, __int64 val, int sizec)
{
	_asm 
	{
		mov edi,p
		xor eax,eax
		mov ecx,sizec
		movq mm0,val
		align 16
lx64UV:
		sub ecx,64
		cmp ecx,eax
		jl lx32UVpre
		movntq [edi],mm0
		movntq [edi+8],mm0
		movntq [edi+16],mm0
		movntq [edi+24],mm0
		movntq [edi+32],mm0
		movntq [edi+40],mm0
		movntq [edi+48],mm0
		movntq [edi+56],mm0
		lea edi,[edi+64]
		jmp lx64UV
lx32UVpre:
		add ecx,64
		align 16
lx32UV:
		sub ecx,32
		cmp ecx,eax
		jl lx8UVpre
		movntq [edi],mm0
		movntq [edi+8],mm0
		movntq [edi+16],mm0
		movntq [edi+24],mm0
		lea edi,[edi+32]
		jmp lx32UV
lx8UVpre:
		add ecx,32
		align 16
lx8UV:
		sub ecx,8
		cmp ecx,eax
		jl lxUVend
		movntq [edi],mm0
		lea edi,[edi+8]
		jmp lx8UV
lxUVend:
		sfence
		emms
	}
}

void fmemset_8_MMX(unsigned char* p, __int64 val, int sizec)
{
	_asm 
	{
		mov edi,p
		xor eax,eax
		mov ecx,sizec
		movq mm0,val
		align 16
lx64UV:
		sub ecx,64
		cmp ecx,eax
		jl lx32UVpre
		movq [edi],mm0
		movq [edi+8],mm0
		movq [edi+16],mm0
		movq [edi+24],mm0
		movq [edi+32],mm0
		movq [edi+40],mm0
		movq [edi+48],mm0
		movq [edi+56],mm0
		lea edi,[edi+64]
		jmp lx64UV
lx32UVpre:
		add ecx,64
		align 16
lx32UV:
		sub ecx,32
		cmp ecx,eax
		jl lx8UVpre
		movq [edi],mm0
		movq [edi+8],mm0
		movq [edi+16],mm0
		movq [edi+24],mm0
		lea edi,[edi+32]
		jmp lx32UV
lx8UVpre:
		add ecx,32
		align 16
lx8UV:
		sub ecx,8
		cmp ecx,eax
		jl lxUVend
		movq [edi],mm0
		lea edi,[edi+8]
		jmp lx8UV
lxUVend:
		emms
	}
}

void fmemset(long cpu, unsigned char *p, int sizec, int val, int opt)
{
	if (opt != 4)
	{
		if (opt == 0) cpu &= ~0x2C;
		else if (opt == 1) { cpu &= ~0x28; cpu |= 0x04; }
		else if (opt == 2) { cpu &= ~0x20; cpu |= 0x0C; }
		else if (opt == 3) cpu |= 0x2C;
	}
	if ((cpu&CPUF_SSE2) && !(sizec&15))
	{
		__int64 v[2];
		v[0] = (val<<8)+val;
		v[0] += (v[0]<<48)+(v[0]<<32)+(v[0]<<16);
		v[1] = v[0];
		__m128 v128;
		__asm
		{
			movups xmm0,xmmword ptr[v]
			movaps v128,xmm0
		}
		fmemset_16_SSE2(p, v128, sizec);
	}
	else if ((cpu&CPUF_INTEGER_SSE) && !(sizec&7))
	{
		__int64 v = (val<<8)+val;
		v += (v<<48)+(v<<32)+(v<<16);
		if (sizec&15) fmemset_8_iSSE(p, v, sizec);
		else fmemset_16_iSSE(p, v, sizec);
	}
	else if ((cpu&CPUF_MMX) && !(sizec&7))
	{
		__int64 v = (val<<8)+val;
		v += (v<<48)+(v<<32)+(v<<16);
		if (sizec&15) fmemset_8_MMX(p, v, sizec);
		else fmemset_16_MMX(p, v, sizec);
	}
	else memset(p,val,sizec);
}