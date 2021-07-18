// libgeom.cpp : スタティック ライブラリ用の関数を定義します。
//
#include "pch.h"
#include <intrin.h>
#include "../include/libgeom.h"

#define UNIT 4

// 4つのfloat が num個の配列をsrcからdstにコピー
void copy_vector4_array(float* dst, const float* src, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	for (int i = 0; i < num * UNIT; i += UNIT)
	{
		//__m128 … SSE/AVXの変数型、128 bitのレジスタを自由に切って使う（float型(32bit)4個分）
		//src のデータをレジスタ pd に 128bit（32bit * 4個）ロードする
		__m128 pd = _mm_load_ps(src + i);

		//レジスタ pd のデータをメモリのdstに128bit（32bit * 4個）ストアする
		_mm_store_ps(dst + i, pd);
	}

#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = ps[0];
		pd[1] = ps[1];
		pd[2] = ps[2];
		pd[3] = ps[3];

		pd += UNIT;
		ps += UNIT;
	}
#endif
}

// 4つのfloat が num個の配列 src0, src1を足してdstに出力
void add_vector4_array(float* dst, const float* src0, const float* src1, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	for (int i = 0; i < num * UNIT; i += UNIT)
	{
		//src0,src1 のデータをレジスタ ps0,ps1 に 128bit（32bit * 4個）ロードする
		__m128 ps0 = _mm_load_ps(src0 + i);
		__m128 ps1 = _mm_load_ps(src1 + i);

		//ps0 と ps0 のデータを同時に4個足し算し，pd に結果を書きこむ
		__m128 pd = _mm_add_ps(ps0, ps1);

		//レジスタ pd のデータをメモリのdstに128bit（32bit * 4個）ストアする
		_mm_store_ps(dst + i, pd);
	}

#else
	float* pd = dst;
	const float* ps0 = src0;
	const float* ps1 = src1;

	for (int i = 0; i < num; i++) {
		pd[0] = ps0[0] + ps1[0];
		pd[1] = ps0[1] + ps1[1];
		pd[2] = ps0[2] + ps1[2];
		pd[3] = ps0[3] + ps1[3];

		pd += UNIT;
		ps0 += UNIT;
		ps1 += UNIT;
	}
#endif
}

// 4つのfloat に num個の配列 src にmatrix[4][4] の行列を掛けてdstに出力
void apply_matrix_vector4_array(float* dst, const float* src, const float* matrix, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = matrix[UNIT *0+0]*ps[0] + matrix[UNIT *0+1]*ps[1] + matrix[UNIT *0+2]*ps[2] + matrix[UNIT *0+3]*ps[3];
		pd[1] = matrix[UNIT *1+0]*ps[0] + matrix[UNIT *1+1]*ps[1] + matrix[UNIT *1+2]*ps[2] + matrix[UNIT *1+3]*ps[3];
		pd[2] = matrix[UNIT *2+0]*ps[0] + matrix[UNIT *2+1]*ps[1] + matrix[UNIT *2+2]*ps[2] + matrix[UNIT *2+3]*ps[3];
		pd[3] = matrix[UNIT *3+0]*ps[0] + matrix[UNIT *3+1]*ps[1] + matrix[UNIT *3+2]*ps[2] + matrix[UNIT *3+3]*ps[3];

		pd += UNIT;
		ps += UNIT;
	}
#endif
}
