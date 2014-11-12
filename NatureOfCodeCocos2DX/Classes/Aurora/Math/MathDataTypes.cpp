//#include "stdafx.h"
#include "MathDataTypes.h"

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
		mQUATERNION4D::mQUATERNION4D()
		{
			this->q0 = 0;
		}

		mQUATERNION4D::mQUATERNION4D(Float q0, VECTOR3D qv)
		{
			this->q0 = q0;
			this->qV = qv;
		}

		mQUATERNION4D::mQUATERNION4D(const mQUATERNION4D &value)
		{
			this->q0 = value.q0;
			this->qV = value.qV;
		}

		mQUATERNION4D::~mQUATERNION4D()
		{
			
		}

		mQUATERNION4D &mQUATERNION4D::operator=(const mQUATERNION4D		&value)
		{
			if(this == &value) { return(*this); }
			this->q0 = value.q0;
			this->qV = value.qV;
			return(*this);
		}

		mQUATERNION4D mQUATERNION4D::operator+(const mQUATERNION4D		&value)
		{
			return(mQUATERNION4D(this->q0 + value.q0, VECTOR3D(this->qV.X + value.qV.X, this->qV.Y + value.qV.Y, this->qV.Z + value.qV.Z)));
		}

		mQUATERNION4D mQUATERNION4D::operator-(const mQUATERNION4D		&value)
		{
			return(mQUATERNION4D(this->q0 - value.q0, VECTOR3D(this->qV.X - value.qV.X, this->qV.Y - value.qV.Y, this->qV.Z - value.qV.Z)));
		}

		mQUATERNION4D &mQUATERNION4D::operator+=(const mQUATERNION4D		&value)
		{
			if(this == &value) { return(*this); }
			this->q0 += value.q0;
			this->qV += value.qV;
			return(*this);
		}

		mQUATERNION4D &mQUATERNION4D::operator-=(const mQUATERNION4D		&value)
		{
			if(this == &value) { return(*this); }
			this->q0 -= value.q0;
			this->qV -= value.qV;
			return(*this);
		}

		mQUATERNION4D mQUATERNION4D::operator*(const Float		&value)
		{
			return(mQUATERNION4D(this->q0 * value, VECTOR3D(this->qV.X * value, this->qV.Y * value, this->qV.Z * value)));
		}

		mQUATERNION4D &mQUATERNION4D::operator*=(const mQUATERNION4D		&value)
		{
			if(this == &value) { return(*this); }
			this->q0 *= value.q0;
			this->qV.X *= value.qV.X;
			this->qV.Y *= value.qV.Y;
			this->qV.Z *= value.qV.Z;
			return(*this);
		}

		void mQUATERNION4D::ZeroQuarternion()
		{
			this->q0 = 0.0f;
			this->qV.ZeroVector();
		}

		mPARAMETRICLINE2D::mPARAMETRICLINE2D(VERTEX2D &init, VERTEX2D &term)
		{
			this->point1 = init;
			this->point2 = term;
			this->v = term - init;
		}

		mPARAMETRICLINE2D::~mPARAMETRICLINE2D()
		{

		}

		mPARAMETRICLINE3D::mPARAMETRICLINE3D(VERTEX3D &init, VERTEX3D &term)
		{
			this->point1 = init;
			this->point2 = term;
			this->v = term - init;
		}

		mPLANE3D::mPLANE3D(const VECTOR3D &point, const VECTOR3D &normal, bool Normalize)
		{
			this->point = point;
			if(!Normalize)
			{ this->normal = normal; } else {
                //NormalizeVector(&this->normal, normal);
            }
		}

		mPLANE3D::~mPLANE3D()
		{

		}


		mRECT::mRECT(int width, int height)
		{
			this->Width = width;
			this->Height = height;
		}

		mRECT::mRECT() : Width(0), Height(0)
		{
			this->Width = 0;
			this->Height = 0;
		}

		mRECT::mRECT(mRECT &&value) : Width(value.Width), Height(value.Height)
		{

		}

		mRECT::mRECT(const mRECT &value) : Width(value.Width), Height(value.Height)
		{

		}

		mRECT::~mRECT()
		{

		}

		bool mRECT::operator==(const mRECT &value)
		{
			bool isEqual = false;

			if(this->Width == value.Width && this->Height == value.Height)
				isEqual = true;

			return(isEqual);
		}

		bool mRECT::operator!=(const mRECT &value)
		{
			bool isEqual = false;

			if(this->Width != value.Width && this->Height != value.Height)
				isEqual = true;

			return(isEqual);
		}

		bool mRECT::IsZero() const
		{
			bool isZero = false;

			if(this->Width == 0 && this->Height == 0)
				isZero = true;

			return(isZero);
		}

		mRECT & mRECT::operator=(mRECT && value)
		{
			this->Width = value.Width;
			this->Height = value.Height;
			return(*this);
		}

		mRECT & mRECT::operator=(const mRECT & value)
		{
			this->Width = value.Width;
			this->Height = value.Height;
			return(*this);
		}

	} // END OF NAMESPACE
} // END OF NAMESPACE