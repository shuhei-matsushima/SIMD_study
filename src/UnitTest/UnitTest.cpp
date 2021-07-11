#include "pch.h"
#include <iostream>
#include <chrono>
#include "CppUnitTest.h"
#include "../include/libgeom.h"

#pragma comment(lib,"libgeom.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TestCopy)
	{
	public:
		
		TEST_METHOD(Copy1)
		{
			__declspec(align(32)) float src[4] = { 0.0f, 1.0f, 2.0f, 3.0f };
			__declspec(align(32)) float dst[4];

			copy_vector4_array(dst, src, 1);

			Assert::AreEqual(dst[0], src[0]);
			Assert::AreEqual(dst[1], src[1]);
			Assert::AreEqual(dst[2], src[2]);
			Assert::AreEqual(dst[3], src[3]);
		}

		TEST_METHOD(Copy10000)
		{
			const int num = 10000;
			__declspec(align(32)) float src[4 * num];
			__declspec(align(32)) float dst[4 * num];

			// ílÇÃê›íË
			for (int i = 0; i < 4 * num; i++) {
				src[i] = (float)std::rand() / (float)RAND_MAX;
 			}

			copy_vector4_array(dst, src, num);

			for (int i = 0; i < 4 * num; i++) {
				Assert::AreEqual(dst[i], src[i]);
			}
		}
	};

	TEST_CLASS(TestAdd)
	{
	public:

		TEST_METHOD(Add1)
		{
			__declspec(align(32)) float src0[4] = { 0.0f, 1.0f, 2.0f, 3.0f };
			__declspec(align(32)) float src1[4] = { 4.0f, 5.0f, 6.0f, 7.0f };
			__declspec(align(32)) float dst[4];
			
			add_vector4_array(dst, src0, src1, 1);

			Assert::AreEqual(dst[0], 4.0f);
			Assert::AreEqual(dst[1], 6.0f);
			Assert::AreEqual(dst[2], 8.0f);
			Assert::AreEqual(dst[3], 10.0f);
		}

		TEST_METHOD(Add10000)
		{
			const int num = 10000;
			__declspec(align(32)) float src0[4 * num];
			__declspec(align(32)) float src1[4 * num];
			__declspec(align(32)) float dst[4 * num];

			// ílÇÃê›íË
			for (int i = 0; i < 4 * num; i++) {
				src0[i] = (float)std::rand() / (float)RAND_MAX;
				src1[i] = (float)std::rand() / (float)RAND_MAX;
			}

			add_vector4_array(dst, src0, src1, num);

			for (int i = 0; i < 4 * num; i++) {
				Assert::AreEqual(dst[i], src0[i] + src1[i]);
			}
		}
	};

	TEST_CLASS(TestApply)
	{
	public:

		TEST_METHOD(Apply1)
		{
			__declspec(align(32)) float src[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
			__declspec(align(32)) float matrix[16] = {
				 1.0f,  2.0f,  3.0f,  4.0f,
				 5.0f,  6.0f,  7.0f,  8.0f,
				 9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f,
			};
			__declspec(align(32)) float dst[4];

			apply_matrix_vector4_array(dst, src, matrix, 1);

			Assert::AreEqual(dst[0], 30.0f);
			Assert::AreEqual(dst[1], 70.0f);
			Assert::AreEqual(dst[2], 110.0f);
			Assert::AreEqual(dst[3], 150.0f);
		}

		TEST_METHOD(Apply10000)
		{
			const int num = 10000;
			__declspec(align(32)) float src[4 * num];
			__declspec(align(32)) float matrix[16] = {
				 1.0f,  2.0f,  3.0f,  4.0f,
				 5.0f,  6.0f,  7.0f,  8.0f,
				 9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f,
			};
			__declspec(align(32)) float dst[4 * num];

			// ílÇÃê›íË
			for (int i = 0; i < 4 * num; i++) {
				src[i] = (float)std::rand() / (float)RAND_MAX;
			}

			apply_matrix_vector4_array(dst, src, matrix, num);

			for (int i = 0; i < num; i++) {
				Assert::AreEqual(dst[4*i+0], matrix[ 0]*src[4*i+0] + matrix[ 1]*src[4*i+1] + matrix[ 2]*src[4*i+2] + matrix[ 3]*src[4*i+3], 0.0001f);
				Assert::AreEqual(dst[4*i+1], matrix[ 4]*src[4*i+0] + matrix[ 5]*src[4*i+1] + matrix[ 6]*src[4*i+2] + matrix[ 7]*src[4*i+3], 0.0001f);
				Assert::AreEqual(dst[4*i+2], matrix[ 8]*src[4*i+0] + matrix[ 9]*src[4*i+1] + matrix[10]*src[4*i+2] + matrix[11]*src[4*i+3], 0.0001f);
				Assert::AreEqual(dst[4*i+3], matrix[12]*src[4*i+0] + matrix[13]*src[4*i+1] + matrix[14]*src[4*i+2] + matrix[15]*src[4*i+3], 0.0001f);
			}
		}
	};
}
