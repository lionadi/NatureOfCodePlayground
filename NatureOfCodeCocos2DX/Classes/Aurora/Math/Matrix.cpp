//#include "stdafx.h"
#include "Matrix.h"
/*!
Namespace: Aurora

This namespace is the main package for the engine. It holds all the main classes, namespaces, operations etc... that defines the functionality of this
project/engine.
*/
namespace Aurora
{
	/*!
	Namespace: Math

	This namespace holds needed math operations for the engine.
	*/
	namespace Math
	{
// MATRIX2X2 -------------------------------------------------------------------------------------------
		MATRIX2X2::MATRIX2X2()
		{
			this->M11 = 0; this->M12 = 0;
			this->M21 = 0; this->M22 = 0;
		}

		MATRIX2X2::MATRIX2X2(Float m00, Float m01, Float m10, Float m11)
		{
			this->M11 = m00;		this->M12 = m01;
			this->M21 = m10;		this->M22 = m11;
		}

		MATRIX2X2::MATRIX2X2(const MATRIX2X2 &mat)
		{
			this->M11 = mat.M11;	this->M12 = mat.M12;
			this->M21 = mat.M21;	this->M22 = mat.M22;
		}

		MATRIX2X2::~MATRIX2X2()
		{

		}

		MATRIX2X2 MATRIX2X2::operator+(const Float			&value)
		{
			/*MATRIX2X2 mat;
			mat.M11 = this->M11 + value;		mat.M12 = this->M12 + value;
			mat.M21 = this->M21 + value;		mat.M22 = this->M22 + value;
			return(mat);*/
			return(MATRIX2X2(this->M11 + value, this->M12 + value, this->M21 + value, this->M22 + value));
		}

		MATRIX2X2 MATRIX2X2::operator+(const MATRIX2X2		&value)
		{
			/*MATRIX2X2 mat;
			mat.M11 = this->M11 + value.M11;	mat.M12 = this->M12 + value.M12;
			mat.M21 = this->M21 + value.M21;	mat.M22 = this->M22 + value.M22;
			return(mat);*/
			return(MATRIX2X2(this->M11 + value.M11, this->M12 + value.M12, this->M21 + value.M21, this->M22 + value.M22));
		}

		MATRIX2X2 MATRIX2X2::operator-(const Float			&value)
		{
			/*MATRIX2X2 mat;
			mat.M11 = this->M11 - value;		mat.M12 = this->M12 - value;
			mat.M21 = this->M21 - value;		mat.M22 = this->M22 - value;
			return(mat);*/
			return(MATRIX2X2(this->M11 - value, this->M12 - value, this->M21 - value, this->M22 - value));
		}

		MATRIX2X2 MATRIX2X2::operator-(const MATRIX2X2		&value)
		{
			/*MATRIX2X2 mat;
			mat.M11 = this->M11 - value.M11;	mat.M12 = this->M12 - value.M12;
			mat.M21 = this->M21 - value.M21;	mat.M22 = this->M22 - value.M22;
			return(mat);*/
			return(MATRIX2X2(this->M11 - value.M11, this->M12 - value.M12, this->M21 - value.M21, this->M22 - value.M22));
		}

		MATRIX2X2 &MATRIX2X2::operator=(const MATRIX2X2		&value)
		{
			if(this == &value) { return(*this); }
			this->M11 = value.M11;				this->M12 = value.M12;
			this->M21 = value.M21;				this->M22 = value.M22;
			return(*this);
		}

		MATRIX2X2 &MATRIX2X2::operator+=(const Float		&value)
		{
			this->M11 += value;					this->M12 += value;
			this->M21 += value;					this->M22 += value;
			return(*this);
		}

		MATRIX2X2 &MATRIX2X2::operator+=(const MATRIX2X2	&value)
		{
			if(this == &value) { return(*this); }
			this->M11 += value.M11;				this->M12 += value.M12;
			this->M21 += value.M21;				this->M22 += value.M22;
			return(*this);
		}

		MATRIX2X2 &MATRIX2X2::operator-=(const Float		&value)
		{
			this->M11 -= value;					this->M12 -= value;
			this->M21 -= value;					this->M22 -= value;
			return(*this);
		}

		MATRIX2X2 &MATRIX2X2::operator-=(const MATRIX2X2	&value)
		{
			if(this == &value) { return(*this); }
			this->M11 -= value.M11;				this->M12 -= value.M12;
			this->M21 -= value.M21;				this->M22 -= value.M22;
			return(*this);
		}

		MATRIX2X2 MATRIX2X2::operator*(const Float			&value)
		{
			/*MATRIX2X2 mat;
			mat.M11 = this->M11 * value;		mat.M12 = this->M12 * value;
			mat.M21 = this->M21 * value;		mat.M22 = this->M22 * value;
			return(mat);*/
			return(MATRIX2X2(this->M11 * value, this->M12 * value, this->M21 * value, this->M22 * value));
		}

		MATRIX2X2 MATRIX2X2::operator*(const MATRIX2X2		&value)
		{
			/*MATRIX2X2 mat;
			mat.M11 = this->M11 * value.M11 + this->M12 * value.M21;		mat.M12 = this->M11 * value.M12 + this->M12 * value.M22;
			mat.M21 = this->M21 * value.M11 + this->M22 * value.M21;		mat.M22 = this->M21 * value.M12 + this->M22 * value.M22;
			return(mat);*/
			return(MATRIX2X2(	this->M11 * value.M11 + this->M12 * value.M21,
								this->M11 * value.M12 + this->M12 * value.M22,
								this->M21 * value.M11 + this->M22 * value.M21,
								this->M21 * value.M12 + this->M22 * value.M22));
		}

		MATRIX2X2 &MATRIX2X2::operator*=(const Float			&value)
		{
			this->M11 *= value;	this->M12 *= value;
			this->M21 *= value; this->M22 *= value;
			return(*this);
		}

		MATRIX2X2 &MATRIX2X2::operator*=(const MATRIX2X2		&value)
		{
			MATRIX2X2 mat = *this;
			this->M11 = mat.M11 * value.M11 + mat.M12 * value.M21;		this->M12 = mat.M11 * value.M12 + mat.M12 * value.M22;
			this->M21 = mat.M21 * value.M11 + mat.M22 * value.M21;		this->M22 = mat.M21 * value.M12 + mat.M22 * value.M22;
			return(*this);
		}

// MATRIX3X3 ------------------------------------------------------------------------------------------------------------------------------
		MATRIX3X3::MATRIX3X3()
		{
			this->M11 = 0;			this->M12 = 0;			this->M13 = 0;
			this->M21 = 0;			this->M22 = 0;			this->M23 = 0;
			this->M31 = 0;			this->M32 = 0;			this->M33 = 0;
		}

		MATRIX3X3::MATRIX3X3(Float m00, Float m01, Float m02, Float m10, Float m11, Float m12, Float m20, Float m21, Float m22)
		{
			this->M11 = m00;		this->M12 = m01;		this->M13 = m02;
			this->M21 = m10;		this->M22 = m11;		this->M23 = m12;
			this->M31 = m20;		this->M32 = m21;		this->M33 = m22;
		}

		MATRIX3X3::MATRIX3X3(const MATRIX3X3 &mat)
		{
			this->M11 = mat.M11;	this->M12 = mat.M12;	this->M13 = mat.M13;
			this->M21 = mat.M21;	this->M22 = mat.M22;	this->M23 = mat.M23;
			this->M31 = mat.M31;	this->M32 = mat.M32;	this->M33 = mat.M33;
		}

		MATRIX3X3::~MATRIX3X3()
		{

		}

		/*
			m00		m01		m02
			m10		m11		m12
			m20		m21		m22
		*/
		MATRIX3X3 MATRIX3X3::operator+(const Float			&value)
		{
			return(MATRIX3X3(	this->M11 + value,	// m00
								this->M12 + value,	// m01
								this->M13 + value,	// m02
								this->M21 + value,	// m10
								this->M22 + value,	// m11
								this->M23 + value,	// m12
								this->M31 + value,	// m20
								this->M32 + value,	// m21
								this->M33 + value	// m22
								));
		}

		MATRIX3X3 MATRIX3X3::operator+(const MATRIX3X3		&value)
		{
			return(MATRIX3X3(	this->M11 + value.M11,	// m00
								this->M12 + value.M12,	// m01
								this->M13 + value.M13,	// m02
								this->M21 + value.M21,	// m10
								this->M22 + value.M22,	// m11
								this->M23 + value.M23,	// m12
								this->M31 + value.M31,	// m20
								this->M32 + value.M32,	// m21
								this->M33 + value.M33	// m22
								));
		}

		MATRIX3X3 MATRIX3X3::operator-(const Float			&value)
		{
			return(MATRIX3X3(	this->M11 - value,	// m00
								this->M12 - value,	// m01
								this->M13 - value,	// m02
								this->M21 - value,	// m10
								this->M22 - value,	// m11
								this->M23 - value,	// m12
								this->M31 - value,	// m20
								this->M32 - value,	// m21
								this->M33 - value	// m22
								));
		}

		MATRIX3X3 MATRIX3X3::operator-(const MATRIX3X3		&value)
		{
			return(MATRIX3X3(	this->M11 - value.M11,	// m00
								this->M12 - value.M12,	// m01
								this->M13 - value.M13,	// m02
								this->M21 - value.M21,	// m10
								this->M22 - value.M22,	// m11
								this->M23 - value.M22,	// m12
								this->M31 - value.M31,	// m20
								this->M32 - value.M32,	// m21
								this->M33 - value.M33	// m22
								));
		}

		MATRIX3X3 &MATRIX3X3::operator=(const MATRIX3X3		&value)
		{
			if(this == &value) { return(*this); }
			this->M11 = value.M11;				this->M12 = value.M12;			this->M13 = value.M13;
			this->M21 = value.M21;				this->M22 = value.M22;			this->M23 = value.M23;
			this->M31 = value.M31;				this->M32 = value.M32;			this->M33 = value.M33;
			return(*this);
		}

		MATRIX3X3 &MATRIX3X3::operator+=(const Float		&value)
		{
			this->M11 += value;					this->M12 += value;				this->M13 += value;
			this->M21 += value;					this->M22 += value;				this->M23 += value;
			this->M31 += value;					this->M32 += value;				this->M33 += value;
			return(*this);
		}

		MATRIX3X3 &MATRIX3X3::operator+=(const MATRIX3X3	&value)
		{
			if(this == &value) { return(*this); }
			this->M11 += value.M11;				this->M12 += value.M12;			this->M13 += value.M13;
			this->M21 += value.M21;				this->M22 += value.M22;			this->M23 += value.M23;
			this->M31 += value.M31;				this->M32 += value.M32;			this->M33 += value.M33;
			return(*this);
		}

		MATRIX3X3 &MATRIX3X3::operator-=(const Float		&value)
		{
			this->M11 -= value;					this->M12 -= value;				this->M13 -= value;
			this->M21 -= value;					this->M22 -= value;				this->M23 -= value;
			this->M31 -= value;					this->M32 -= value;				this->M33 -= value;
			return(*this);
		}

		MATRIX3X3 &MATRIX3X3::operator-=(const MATRIX3X3	&value)
		{
			if(this == &value) { return(*this); }
			this->M11 -= value.M11;				this->M12 -= value.M12;			this->M13 -= value.M13;
			this->M21 -= value.M21;				this->M22 -= value.M22;			this->M23 -= value.M23;
			this->M31 -= value.M31;				this->M32 -= value.M32;			this->M33 -= value.M33;
			return(*this);
		}

		MATRIX3X3 MATRIX3X3::operator*(const Float			&value)
		{
			return(MATRIX3X3(	this->M11 * value,	// m00
								this->M12 * value,	// m01
								this->M13 * value,	// m02
								this->M21 * value,	// m10
								this->M22 * value,	// m11
								this->M23 * value,	// m12
								this->M31 * value,	// m20
								this->M32 * value,	// m21
								this->M33 * value	// m22
								));
		}

		MATRIX3X3 MATRIX3X3::operator*(const MATRIX3X3		&value)
		{
			/*MATRIX3X3 mat;
			mat.M11 = this->M11 * value.M11 + this->M12 * value.M21 + this->M13 * value.M31;
			mat.M12 = this->M11 * value.M12 + this->M12 * value.M22 + this->M13 * value.M32;
			mat.M13 = this->M11 * value.M13 + this->M12 * value.M23 + this->M13 * value.M33;

			mat.M21 = this->M21 * value.M11 + this->M22 * value.M21 + this->M23 * value.M31;
			mat.M22 = this->M21 * value.M12 + this->M22 * value.M22 + this->M23 * value.M32;
			mat.M23 = this->M21 * value.M13 + this->M22 * value.M23 + this->M23 * value.M33;

			mat.M31 = this->M31 * value.M11 + this->M32 * value.M21 + this->M33 * value.M31;
			mat.M32 = this->M31 * value.M12 + this->M32 * value.M22 + this->M33 * value.M32;
			mat.M33 = this->M31 * value.M13 + this->M32 * value.M23 + this->M33 * value.M33;*/
			return(MATRIX3X3(	this->M11 * value.M11 + this->M12 * value.M21 + this->M13 * value.M31,		// m00
								this->M11 * value.M12 + this->M12 * value.M22 + this->M13 * value.M32,		// m01
								this->M11 * value.M13 + this->M12 * value.M23 + this->M13 * value.M33,		// m02
								this->M21 * value.M11 + this->M22 * value.M21 + this->M23 * value.M31,		// m10
								this->M21 * value.M12 + this->M22 * value.M22 + this->M23 * value.M32,		// m11
								this->M21 * value.M13 + this->M22 * value.M23 + this->M23 * value.M33,		// m12
								this->M31 * value.M11 + this->M32 * value.M21 + this->M33 * value.M31,		// m20
								this->M31 * value.M12 + this->M32 * value.M22 + this->M33 * value.M32,		// m21
								this->M31 * value.M13 + this->M32 * value.M23 + this->M33 * value.M33));	// m22




		}

		MATRIX3X3 &MATRIX3X3::operator*=(const Float			&value)
		{
			this->M11 *= value;	this->M12 *= value; this->M13 *= value;
			this->M21 *= value; this->M22 *= value; this->M23 *= value;
			this->M31 *= value; this->M32 *= value; this->M33 *= value;
			return(*this);
		}

		MATRIX3X3 &MATRIX3X3::operator*=(const MATRIX3X3		&value)
		{
			MATRIX3X3 mat = *this;
			this->M11 = mat.M11 * value.M11 + mat.M12 * value.M21 + mat.M13 * value.M31;
			this->M12 = mat.M11 * value.M12 + mat.M12 * value.M22 + mat.M13 * value.M32;
			this->M13 = mat.M11 * value.M13 + mat.M12 * value.M23 + mat.M13 * value.M33;

			this->M21 = mat.M21 * value.M11 + mat.M22 * value.M21 + mat.M23 * value.M31;
			this->M22 = mat.M21 * value.M12 + mat.M22 * value.M22 + mat.M23 * value.M32;
			this->M23 = mat.M21 * value.M13 + mat.M22 * value.M23 + mat.M23 * value.M33;

			this->M31 = mat.M31 * value.M11 + mat.M32 * value.M21 + mat.M33 * value.M31;
			this->M32 = mat.M31 * value.M12 + mat.M32 * value.M22 + mat.M33 * value.M32;
			this->M33 = mat.M31 * value.M13 + mat.M32 * value.M23 + mat.M33 * value.M33; 
			return(*this);
		}


		MATRIX4X4::MATRIX4X4()
		{
			this->M11 = 0;			this->M12 = 0;			this->M13 = 0;		this->M14 = 0;
			this->M21 = 0;			this->M22 = 0;			this->M23 = 0;		this->M24 = 0;
			this->M31 = 0;			this->M32 = 0;			this->M33 = 0;		this->M34 = 0;
			this->M41 = 0;			this->M42 = 0;			this->M43 = 0;		this->M44 = 0;
		}

		MATRIX4X4::MATRIX4X4(Float m00, Float m01, Float m02, Float m03, Float m10, Float m11, Float m12, Float m13, Float m20, Float m21, Float m22, Float m23, Float m30, Float m31, Float m32, Float m33)
		{
			this->M11 = m00;		this->M12 = m01;		this->M13 = m02;	this->M14 = m03;
			this->M21 = m10;		this->M22 = m11;		this->M23 = m12;	this->M24 = m13;
			this->M31 = m20;		this->M32 = m21;		this->M33 = m22;	this->M34 = m23;
			this->M41 = m30;		this->M42 = m31;		this->M43 = m32;	this->M44 = m33;
		}

		MATRIX4X4::MATRIX4X4(const MATRIX4X4 &mat)
		{
			this->M11 = mat.M11;	this->M12 = mat.M12;	this->M13 = mat.M13;	this->M14 = mat.M14;
			this->M21 = mat.M21;	this->M22 = mat.M22;	this->M23 = mat.M23;	this->M24 = mat.M24;
			this->M31 = mat.M31;	this->M32 = mat.M32;	this->M33 = mat.M33;	this->M34 = mat.M34;
			this->M41 = mat.M41;	this->M42 = mat.M42;	this->M43 = mat.M43;	this->M44 = mat.M44;
		}

		MATRIX4X4::~MATRIX4X4()
		{

		}

		/*
		m00		m01		m02		m03
		m10		m11		m12		m13
		m20		m21		m22		m23
		m30		m31		m32		m33
		*/
		MATRIX4X4 MATRIX4X4::operator+(const Float			&value)
		{
			return(MATRIX4X4(	this->M11 + value,	// m00
								this->M12 + value,	// m01
								this->M13 + value,	// m02
								this->M14 + value,	// m03
								this->M21 + value,	// m10
								this->M22 + value,	// m11
								this->M23 + value,	// m12
								this->M24 + value,	// m13
								this->M31 + value,	// m20
								this->M32 + value,	// m21
								this->M33 + value,	// m22
								this->M34 + value,	// m23
								this->M41 + value,	// m30
								this->M42 + value,	// m31
								this->M43 + value,	// m32
								this->M44 + value	// m33
								));
		}

		MATRIX4X4 MATRIX4X4::operator+(const MATRIX4X4		&value)
		{
			return(MATRIX4X4(	this->M11 + value.M11,	// m00
								this->M12 + value.M12,	// m01
								this->M13 + value.M13,	// m02
								this->M14 + value.M14,	// m03
								this->M21 + value.M21,	// m10
								this->M22 + value.M22,	// m11
								this->M23 + value.M23,	// m12
								this->M24 + value.M24,	// m13
								this->M31 + value.M31,	// m20
								this->M32 + value.M32,	// m21
								this->M33 + value.M33,	// m22
								this->M34 + value.M34,	// m23
								this->M41 + value.M41,	// m30
								this->M42 + value.M42,	// m31
								this->M43 + value.M43,	// m32
								this->M44 + value.M44	// m33
								));
		}

		MATRIX4X4 MATRIX4X4::operator-(const Float			&value)
		{
			return(MATRIX4X4(	this->M11 - value,	// m00
								this->M12 - value,	// m01
								this->M13 - value,	// m02
								this->M14 - value,	// m03
								this->M21 - value,	// m10
								this->M22 - value,	// m11
								this->M23 - value,	// m12
								this->M24 - value,	// m13
								this->M31 - value,	// m20
								this->M32 - value,	// m21
								this->M33 - value,	// m22
								this->M34 - value,	// m23
								this->M41 - value,	// m30
								this->M42 - value,	// m31
								this->M43 - value,	// m32
								this->M44 - value	// m33
								));
		}

		MATRIX4X4 MATRIX4X4::operator-(const MATRIX4X4		&value)
		{
			return(MATRIX4X4(	this->M11 - value.M11,	// m00
								this->M12 - value.M12,	// m01
								this->M13 - value.M13,	// m02
								this->M14 - value.M14,	// m03
								this->M21 - value.M21,	// m10
								this->M22 - value.M22,	// m11
								this->M23 - value.M23,	// m12
								this->M24 - value.M24,	// m13
								this->M31 - value.M31,	// m20
								this->M32 - value.M32,	// m21
								this->M33 - value.M33,	// m22
								this->M34 - value.M34,	// m23
								this->M41 - value.M41,	// m30
								this->M42 - value.M42,	// m31
								this->M43 - value.M43,	// m32
								this->M44 - value.M44	// m33
								));
		}

		MATRIX4X4 &MATRIX4X4::operator=(const MATRIX4X4		&value)
		{
			if(this == &value) { return(*this); }
			this->M11 = value.M11;	this->M12 = value.M12;	this->M13 = value.M13;	this->M14 = value.M14;
			this->M21 = value.M21;	this->M22 = value.M22;	this->M23 = value.M23;	this->M24 = value.M24;
			this->M31 = value.M31;	this->M32 = value.M32;	this->M33 = value.M33;	this->M34 = value.M34;
			this->M41 = value.M41;	this->M42 = value.M42;	this->M43 = value.M43;	this->M44 = value.M44;
			return(*this);
		}

		MATRIX4X4 &MATRIX4X4::operator+=(const Float		&value)
		{
			this->M11 += value;	this->M12 += value;	this->M13 += value;	this->M14 += value;
			this->M21 += value;	this->M22 += value;	this->M23 += value;	this->M24 += value;
			this->M31 += value;	this->M32 += value;	this->M33 += value;	this->M34 += value;
			this->M41 += value;	this->M42 += value;	this->M43 += value;	this->M44 += value;
			return(*this);
		}

		MATRIX4X4 &MATRIX4X4::operator+=(const MATRIX4X4	&value)
		{
			if(this == &value) { return(*this); }
			this->M11 += value.M11;	this->M12 += value.M12;	this->M13 += value.M13;	this->M14 += value.M14;
			this->M21 += value.M21;	this->M22 += value.M22;	this->M23 += value.M23;	this->M24 += value.M24;
			this->M31 += value.M31;	this->M32 += value.M32;	this->M33 += value.M33;	this->M34 += value.M34;
			this->M41 += value.M41;	this->M42 += value.M42;	this->M43 += value.M43;	this->M44 += value.M44;
			return(*this);
		}

		MATRIX4X4 &MATRIX4X4::operator-=(const Float		&value)
		{
			this->M11 -= value;	this->M12 -= value;	this->M13 -= value;	this->M14 -= value;
			this->M21 -= value;	this->M22 -= value;	this->M23 -= value;	this->M24 -= value;
			this->M31 -= value;	this->M32 -= value;	this->M33 -= value;	this->M34 -= value;
			this->M41 -= value;	this->M42 -= value;	this->M43 -= value;	this->M44 -= value;
			return(*this);
		}

		MATRIX4X4 &MATRIX4X4::operator-=(const MATRIX4X4	&value)
		{
			if(this == &value) { return(*this); }
			this->M11 -= value.M11;	this->M12 -= value.M12;	this->M13 -= value.M13;	this->M14 -= value.M14;
			this->M21 -= value.M21;	this->M22 -= value.M22;	this->M23 -= value.M23;	this->M24 -= value.M24;
			this->M31 -= value.M31;	this->M32 -= value.M32;	this->M33 -= value.M33;	this->M34 -= value.M34;
			this->M41 -= value.M41;	this->M42 -= value.M42;	this->M43 -= value.M43;	this->M44 -= value.M44;
			return(*this);
		}

		MATRIX4X4 MATRIX4X4::operator*(const Float			&value)
		{
			return(MATRIX4X4(	this->M11 * value,	// m00
								this->M12 * value,	// m01
								this->M13 * value,	// m02
								this->M14 * value,	// m03
								this->M21 * value,	// m10
								this->M22 * value,	// m11
								this->M23 * value,	// m12
								this->M24 * value,	// m13
								this->M31 * value,	// m20
								this->M32 * value,	// m21
								this->M33 * value,	// m22
								this->M34 * value,	// m23
								this->M41 * value,	// m30
								this->M42 * value,	// m31
								this->M43 * value,	// m32
								this->M44 * value	// m33
								));
		}

		MATRIX4X4 MATRIX4X4::operator*(const MATRIX4X4		&value)
		{
			/*MATRIX4X4 mat;
			mat.M11 = this->M11 * value.M11 + this->M12 * value.M21 + this->M13 * value.M31 + this->M14 * value.M41;
			mat.M12 = this->M11 * value.M12 + this->M12 * value.M22 + this->M13 * value.M32 + this->M14 * value.M42;
			mat.M13 = this->M11 * value.M13 + this->M12 * value.M23 + this->M13 * value.M33 + this->M14 * value.M43;
			mat.M14 = this->M11 * value.M14 + this->M12 * value.M24 + this->M13 * value.M34 + this->M14 * value.M44;

			mat.M21 = this->M21 * value.M11 + this->M22 * value.M21 + this->M23 * value.M31 + this->M24 * value.M41;
			mat.M22 = this->M21 * value.M12 + this->M22 * value.M22 + this->M23 * value.M32 + this->M24 * value.M42;
			mat.M23 = this->M21 * value.M13 + this->M22 * value.M23 + this->M23 * value.M33 + this->M24 * value.M43;
			mat.M24 = this->M21 * value.M14 + this->M22 * value.M24 + this->M23 * value.M34 + this->M24 * value.M44;

			mat.M31 = this->M31 * value.M11 + this->M32 * value.M21 + this->M33 * value.M31 + this->M34 * value.M41;
			mat.M32 = this->M31 * value.M12 + this->M32 * value.M22 + this->M33 * value.M32 + this->M34 * value.M42;
			mat.M33 = this->M31 * value.M13 + this->M32 * value.M23 + this->M33 * value.M33 + this->M34 * value.M43;
			mat.M34 = this->M31 * value.M14 + this->M32 * value.M24 + this->M33 * value.M34 + this->M34 * value.M44;

			mat.M41 = this->M41 * value.M11 + this->M42 * value.M21 + this->M43 * value.M31 + this->M44 * value.M41;
			mat.M42 = this->M41 * value.M12 + this->M42 * value.M22 + this->M43 * value.M32 + this->M44 * value.M42;
			mat.M43 = this->M41 * value.M13 + this->M42 * value.M23 + this->M43 * value.M33 + this->M44 * value.M43;
			mat.M44 = this->M41 * value.M14 + this->M42 * value.M24 + this->M43 * value.M34 + this->M44 * value.M44;*/
			return(MATRIX4X4(	this->M11 * value.M11 + this->M12 * value.M21 + this->M13 * value.M31 + this->M14 * value.M41,
								this->M11 * value.M12 + this->M12 * value.M22 + this->M13 * value.M32 + this->M14 * value.M42,
								this->M11 * value.M13 + this->M12 * value.M23 + this->M13 * value.M33 + this->M14 * value.M43,
								this->M11 * value.M14 + this->M12 * value.M24 + this->M13 * value.M34 + this->M14 * value.M44,
								this->M21 * value.M11 + this->M22 * value.M21 + this->M23 * value.M31 + this->M24 * value.M41,
								this->M21 * value.M12 + this->M22 * value.M22 + this->M23 * value.M32 + this->M24 * value.M42,
								this->M21 * value.M13 + this->M22 * value.M23 + this->M23 * value.M33 + this->M24 * value.M43,
								this->M21 * value.M14 + this->M22 * value.M24 + this->M23 * value.M34 + this->M24 * value.M44,
								this->M31 * value.M11 + this->M32 * value.M21 + this->M33 * value.M31 + this->M34 * value.M41,
								this->M31 * value.M12 + this->M32 * value.M22 + this->M33 * value.M32 + this->M34 * value.M42,
								this->M31 * value.M13 + this->M32 * value.M23 + this->M33 * value.M33 + this->M34 * value.M43,
								this->M31 * value.M14 + this->M32 * value.M24 + this->M33 * value.M34 + this->M34 * value.M44,
								this->M41 * value.M11 + this->M42 * value.M21 + this->M43 * value.M31 + this->M44 * value.M41,
								this->M41 * value.M12 + this->M42 * value.M22 + this->M43 * value.M32 + this->M44 * value.M42,
								this->M41 * value.M13 + this->M42 * value.M23 + this->M43 * value.M33 + this->M44 * value.M43,
								this->M41 * value.M14 + this->M42 * value.M24 + this->M43 * value.M34 + this->M44 * value.M44
								));
		}

		MATRIX4X4 &MATRIX4X4::operator*=(const Float			&value)
		{
			this->M11 *= value;	this->M12 *= value;	this->M13 *= value;	this->M14 *= value;
			this->M21 *= value;	this->M22 *= value;	this->M23 *= value;	this->M24 *= value;
			this->M31 *= value;	this->M32 *= value;	this->M33 *= value;	this->M34 *= value;
			this->M41 *= value;	this->M42 *= value;	this->M43 *= value;	this->M44 *= value;
			return(*this);
		}

		MATRIX4X4 &MATRIX4X4::operator*=(const MATRIX4X4		&value)
		{
			MATRIX4X4 mat = *this;
			this->M11 = mat.M11 * value.M11 + mat.M12 * value.M21 + mat.M13 * value.M31 + mat.M14 * value.M41;
			this->M12 = mat.M11 * value.M12 + mat.M12 * value.M22 + mat.M13 * value.M32 + mat.M14 * value.M42;
			this->M13 = mat.M11 * value.M13 + mat.M12 * value.M23 + mat.M13 * value.M33 + mat.M14 * value.M43;
			this->M14 = mat.M11 * value.M14 + mat.M12 * value.M24 + mat.M13 * value.M34 + mat.M14 * value.M44;

			this->M21 = mat.M21 * value.M11 + mat.M22 * value.M21 + mat.M23 * value.M31 + mat.M24 * value.M41;
			this->M22 = mat.M21 * value.M12 + mat.M22 * value.M22 + mat.M23 * value.M32 + mat.M24 * value.M42;
			this->M23 = mat.M21 * value.M13 + mat.M22 * value.M23 + mat.M23 * value.M33 + mat.M24 * value.M43;
			this->M24 = mat.M21 * value.M14 + mat.M22 * value.M24 + mat.M23 * value.M34 + mat.M24 * value.M44;

			this->M31 = mat.M31 * value.M11 + mat.M32 * value.M21 + mat.M33 * value.M31 + mat.M34 * value.M41;
			this->M32 = mat.M31 * value.M12 + mat.M32 * value.M22 + mat.M33 * value.M32 + mat.M34 * value.M42;
			this->M33 = mat.M31 * value.M13 + mat.M32 * value.M23 + mat.M33 * value.M33 + mat.M34 * value.M43;
			this->M34 = mat.M31 * value.M14 + mat.M32 * value.M24 + mat.M33 * value.M34 + mat.M34 * value.M44;

			this->M41 = mat.M41 * value.M11 + mat.M42 * value.M21 + mat.M43 * value.M31 + mat.M44 * value.M41;
			this->M42 = mat.M41 * value.M12 + mat.M42 * value.M22 + mat.M43 * value.M32 + mat.M44 * value.M42;
			this->M43 = mat.M41 * value.M13 + mat.M42 * value.M23 + mat.M43 * value.M33 + mat.M44 * value.M43;
			this->M44 = mat.M41 * value.M14 + mat.M42 * value.M24 + mat.M43 * value.M34 + mat.M44 * value.M44;
			return(*this);
		}
		
	}; // ENF OF NAMESPACE
}; // END OF NAMESPACE