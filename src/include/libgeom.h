#pragma once

// 4つのfloat が num個の配列をsrcからdstにコピー
void copy_vector4_array(float* dst, const float* src, int num);

// 4つのfloat が num個の配列 src0, src1を足してdstに出力
void add_vector4_array(float* dst, const float* src0, const float* src1, int num);

// 4つのfloat に num個の配列 src にmatrix[4][4] の行列を掛けてdstに出力
void apply_matrix_vector4_array(float* dst, const float* src, const float* matrix, int num);
