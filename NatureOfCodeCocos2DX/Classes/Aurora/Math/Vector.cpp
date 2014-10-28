//#include "stdafx.h"
#include "Vector.h"
#include "..\Globals\GlobalDatatypes.h"
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

		VECTOR2D::VECTOR2D() : X(0), Y(0)
		{
			this->X = 0;
			this->Y = 0;
		}
		
		VECTOR2D::VECTOR2D(Float x, Float y)
		{
			this->X = x;
			this->Y = y;
		}

		VECTOR2D::VECTOR2D(const VECTOR2D &value)
		{
			this->X = value.X;
			this->Y = value.Y;
		}

		VECTOR2D::~VECTOR2D()
		{
		}
		// ADDITION - OPERATIONS
		//--------------------------------------------------------
		const VECTOR2D VECTOR2D::operator+(const Float &value)
		{
			
			
			return(VECTOR2D(this->X + value,this->Y + value));
		}

		const VECTOR2D VECTOR2D::operator+(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR2D(this->X + value.X, this->Y + value.Y));
		}

		// SUBSTRACTION - OPERATIONS
		//--------------------------------------------------------
		const VECTOR2D VECTOR2D::operator-(const Float &value)
		{
			return(VECTOR2D(this->X - value, this->Y - value));
		}

		const VECTOR2D VECTOR2D::operator-(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR2D(this->X - value.X, this->Y - value.Y));
		}

		// ASSIGNMENT - OPERATIONS
		//--------------------------------------------------------
		VECTOR2D &VECTOR2D::operator=(const Float &value)
		{
			this->X = value;
			this->Y = value;
			return(*this);
		}

		VECTOR2D &VECTOR2D::operator=(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			this->X = value.X;
			this->Y = value.Y;
			return(*this);
		}

		VECTOR2D &VECTOR2D::operator+=(const Float &value)
		{
			this->X += value;
			this->Y += value;
			return(*this);
		}

		VECTOR2D &VECTOR2D::operator+=(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			this->X += value.X;
			this->Y += value.Y;
			return(*this);
		}

		const VECTOR2D &VECTOR2D::operator-=(const Float &value)
		{
			this->X -= value;
			this->Y -= value;
			return(*this);
		}

		const VECTOR2D &VECTOR2D::operator-=(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			this->X -= value.X;
			this->Y -= value.Y;
			return(*this);
		}	
		
		const VECTOR2D VECTOR2D::operator*(const Float		&value)
		{
			return(VECTOR2D(this->X * value, this->Y * value));
		}

		
		const Float VECTOR2D::operator*(const VECTOR2D		&value)
		{
			return((this->X * value.X) + (this->Y * value.Y));
		}
		
		const VECTOR2D &VECTOR2D::operator*=(const Float		&value)
		{
			this->X *= value;
			this->Y *= value;
			return(*this);
		}
        
        const VECTOR2D VECTOR2D::operator/(const Float		&value)
        {
            return(VECTOR2D(this->X / value, this->Y / value));
        }
        
        const VECTOR2D VECTOR2D::operator*(const MATRIX2X2		&value)
        {
            return(VECTOR2D(	this->X * value.M11 + this->Y * value.M21,
                                this->X * value.M12 + this->Y * value.M22));
        }
        
        const VECTOR2D &VECTOR2D::operator*=(const MATRIX2X2		&value)
        {
            this->X = this->X * value.M11 + this->Y * value.M21;
            this->Y = this->X * value.M12 + this->Y * value.M22;

            return(*this);
        }

		void VECTOR2D::ZeroVector()
		{
			this->X = this->Y = 0.0f;
		}
        
        void VECTOR2D::Limit(	const Float &lowerLimit, const Float &upperLimit)
        {
            if ( this->X > upperLimit ) {
                this->Y = upperLimit;
            }
            
            if ( this->Y > upperLimit ) {
                this->Y = upperLimit;
            }

			if ( this->X < lowerLimit ) {
				this->Y = lowerLimit;
			}

			if ( this->Y < lowerLimit ) {
				this->Y = lowerLimit;
			}
        }

		bool VECTOR2D::operator==(const VECTOR2D &value)
		{
			bool isEqual = false;

			if(this->X == value.X && this->Y == value.Y)
				isEqual = true;

			return(isEqual);
		}

		bool VECTOR2D::operator!=(const VECTOR2D &value)
		{
			bool isEqual = false;

			if(this->X != value.X && this->Y != value.Y)
				isEqual = true;

			return(isEqual);
		}

		bool VECTOR2D::IsZero() const
		{
			bool isZero = false;

			if(this->X == 0 && this->Y == 0)
				isZero = true;

			return(isZero);
		}

		VECTOR2D VECTOR2D::GetZeroVector(void)
		{
			return(VECTOR2D(0,0));
		}

// VECTOR3D -----------------------------------------------------------
		VECTOR3D::VECTOR3D()  : X(0), Y(0), Z(0)
		{
			this->X = 0;
			this->Y = 0;
			this->Z = 0;
		}

		VECTOR3D::VECTOR3D(Float x, Float y, Float z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}

		VECTOR3D::VECTOR3D(const VECTOR3D &value)
		{
			this->X = value.X;
			this->Y = value.Y;
			this->Z = value.Z;
		}

		VECTOR3D::~VECTOR3D()
		{
		}

		// ADDITION - OPERATIONS
		//--------------------------------------------------------
		VECTOR3D VECTOR3D::operator+(const Float &value)
		{
			return(VECTOR3D(this->X + value, this->Y + value, this->Z + value));
		}

		VECTOR3D VECTOR3D::operator+(const VECTOR3D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR3D(this->X + value.X, this->Y + value.Y, this->Z + value.Z));
		}

		// SUBSTRACTION - OPERATIONS
		//--------------------------------------------------------
		VECTOR3D VECTOR3D::operator-(const Float &value)
		{
			return(VECTOR3D(this->X - value, this->Y - value, this->Z - value));
		}

		VECTOR3D VECTOR3D::operator-(const VECTOR3D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR3D(this->X - value.X, this->Y - value.Y, this->Z - value.Z));
		}

		// ASSIGNMENT - OPERATIONS
		//--------------------------------------------------------
		VECTOR3D &VECTOR3D::operator=(const Float &value)
		{
			this->X = value;
			this->Y = value;
			this->Z = value;
			return(*this);
		}

		VECTOR3D &VECTOR3D::operator=(const VECTOR3D &value)
		{
			if(this == &value) { return(*this); }
			this->X = value.X;
			this->Y = value.Y;
			this->Z = value.Z;
			return(*this);
		}

		VECTOR3D &VECTOR3D::operator+=(const Float &value)
		{
			this->X += value;
			this->Y += value;
			this->Z += value;
			return(*this);
		}

		VECTOR3D &VECTOR3D::operator+=(const VECTOR3D &value)
		{
			if(this == &value) { return(*this); }
			this->X += value.X;
			this->Y += value.Y;
			this->Z += value.Z;
			return(*this);
		}

		VECTOR3D &VECTOR3D::operator-=(const Float &value)
		{
			this->X -= value;
			this->Y -= value;
			this->Z -= value;
			return(*this);
		}

		VECTOR3D &VECTOR3D::operator-=(const VECTOR3D &value)
		{
			if(this == &value) { return(*this); }
			this->X -= value.X;
			this->Y -= value.Y;
			this->Z -= value.Z;
			return(*this);
		}

		VECTOR3D VECTOR3D::operator*(const Float		&value)
		{
			return(VECTOR3D(this->X * value, this->Y * value, this->Z * value));
		}

		
		Float VECTOR3D::operator*(const VECTOR3D		&value)
		{
			return((this->X * value.X) + (this->Y * value.Y) + (this->Z * value.Z));
		}
		
		VECTOR3D &VECTOR3D::operator*=(const Float		&value)
		{
			this->X *= value;
			this->Y *= value;
			this->Z *= value;
			return(*this);
		}
        
        VECTOR3D VECTOR3D::operator/(const Float		&value)
        {
            return(VECTOR3D(this->X / value, this->Y / value, this->Z / value));
        }
        
        VECTOR3D VECTOR3D::operator*(const MATRIX3X3		&value)
        {
            return(VECTOR3D(	this->X * value.M11 + this->Y * value.M21 + this->Z * value.M31,
                                this->X * value.M12 + this->Y * value.M22 + this->Z * value.M32,
                                this->X * value.M13 + this->Y * value.M23 + this->Z * value.M33));
        }
        
        VECTOR3D &VECTOR3D::operator*=(const MATRIX3X3		&value)
        {
            this->X = this->X * value.M11 + this->Y * value.M21 + this->Z * value.M31;
            this->Y = this->X * value.M12 + this->Y * value.M22 + this->Z * value.M32;
            this->Z = this->X * value.M13 + this->Y * value.M23 + this->Z * value.M33;
            return(*this);
        }

		void VECTOR3D::ZeroVector()
		{
			this->X = this->Y = this->Z = 0.0f;
		}
        
        void VECTOR3D::Limit(	const Float &lowerLimit, const Float &upperLimit)
        {
			if ( this->X > upperLimit ) {
				this->Y = upperLimit;
			}

			if ( this->Y > upperLimit ) {
				this->Y = upperLimit;
			}

			if ( this->Z > upperLimit ) {
				this->Z = upperLimit;
			}

			if ( this->X < lowerLimit ) {
				this->Y = lowerLimit;
			}

			if ( this->Y < lowerLimit ) {
				this->Y = lowerLimit;
			}

			if ( this->Z < lowerLimit ) {
				this->Z = lowerLimit;
			}
        }

		bool VECTOR3D::operator==(const VECTOR3D &value)
		{
			bool isEqual = false;

			if(this->X == value.X && this->Y == value.Y && this->Z == value.Z)
				isEqual = true;

			return(isEqual);
		}

		bool VECTOR3D::operator!=(const VECTOR3D &value)
		{
			bool isEqual = false;

			if(this->X != value.X && this->Y != value.Y && this->Z != value.Z)
				isEqual = true;

			return(isEqual);
		}

		bool VECTOR3D::IsZero() const
		{
			bool isZero = false;

			if(this->X == 0 && this->Y == 0 && this->Z == 0)
				isZero = true;

			return(isZero);
		}

		Aurora::Math::VECTOR3D VECTOR3D::GetZeroVector(void)
		{
			return(VECTOR3D(0,0,0));
		}


// VECTOR4D -----------------------------------------------------------
		VECTOR4D::VECTOR4D()   : X(0), Y(0), Z(0), W(0)
		{
			this->X = 0;
			this->Y = 0;
			this->Z = 0;
			this->W = 0;
		}

		VECTOR4D::VECTOR4D(Float x, Float y, Float z, Float w)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
			this->W = w;
		}

		VECTOR4D::VECTOR4D(const VECTOR4D &value)
		{
			this->X = value.X;
			this->Y = value.Y;
			this->Z = value.Z;
			this->W = value.W;
		}

		VECTOR4D::~VECTOR4D()
		{
		}

		// ADDITION - OPERATIONS
		//--------------------------------------------------------
		VECTOR4D VECTOR4D::operator+(const Float &value)
		{
			return(VECTOR4D(this->X + value, this->Y + value, this->Z + value, this->W + value));
		}

		VECTOR4D VECTOR4D::operator+(const VECTOR4D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR4D(this->X + value.X, this->Y + value.Y, this->Z + value.Z, this->W + value.W));
		}

		// SUBSTRACTION - OPERATIONS
		//--------------------------------------------------------
		VECTOR4D VECTOR4D::operator-(const Float &value)
		{
			return(VECTOR4D(this->X - value, this->Y - value, this->Z - value, this->W - value));
		}

		VECTOR4D VECTOR4D::operator-(const VECTOR4D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR4D(this->X - value.X, this->Y - value.Y, this->Z - value.Z, this->W - value.W));
		}

		// ASSIGNMENT - OPERATIONS
		//--------------------------------------------------------
		VECTOR4D &VECTOR4D::operator=(const Float &value)
		{
			this->X = value;
			this->Y = value;
			this->Z = value;
			this->W = value;
			return(*this);
		}

		VECTOR4D &VECTOR4D::operator=(const VECTOR4D &value)
		{
			if(this == &value) { return(*this); }
			this->X = value.X;
			this->Y = value.Y;
			this->Z = value.Z;
			this->W = value.W;
			return(*this);
		}

		VECTOR4D &VECTOR4D::operator+=(const Float &value)
		{
			this->X += value;
			this->Y += value;
			this->Z += value;
			this->W += value;
			return(*this);
		}

		VECTOR4D &VECTOR4D::operator+=(const VECTOR4D &value)
		{
			if(this == &value) { return(*this); }
			this->X += value.X;
			this->Y += value.Y;
			this->Z += value.Z;
			this->W += value.W;
			return(*this);
		}

		VECTOR4D &VECTOR4D::operator-=(const Float &value)
		{
			this->X -= value;
			this->Y -= value;
			this->Z -= value;
			this->W -= value;
			return(*this);
		}

		VECTOR4D &VECTOR4D::operator-=(const VECTOR4D &value)
		{
			if(this == &value) { return(*this); }
			this->X -= value.X;
			this->Y -= value.Y;
			this->Z -= value.Z;
			this->W -= value.W;
			return(*this);
		}

		VECTOR4D VECTOR4D::operator*(const Float		&value)
		{
			return(VECTOR4D(this->X * value, this->Y * value, this->Z * value, 1));
		}

		
		Float VECTOR4D::operator*(const VECTOR4D		&value)
		{
			return((this->X * value.X) + (this->Y * value.Y) + (this->Z * value.Z));
		}
		
		VECTOR4D &VECTOR4D::operator*=(const Float		&value)
		{
			this->X *= value;
			this->Y *= value;
			this->Z *= value;
			return(*this);
		}
        
        VECTOR4D VECTOR4D::operator/(const Float		&value)
        {
            return(VECTOR4D(this->X / value, this->Y / value, this->Z / value, 1));
        }

		VECTOR4D VECTOR4D::operator*(const MATRIX4X4		&value)
		{
			return(VECTOR4D(	this->X * value.M11 + this->Y * value.M21 + this->Z * value.M31 + this->W * value.M41,
								this->X * value.M12 + this->Y * value.M22 + this->Z * value.M32 + this->W * value.M42,
								this->X * value.M13 + this->Y * value.M23 + this->Z * value.M33 + this->W * value.M43,
								this->X * value.M14 + this->Y * value.M24 + this->Z * value.M34 + this->W * value.M44));
		}

		VECTOR4D &VECTOR4D::operator*=(const MATRIX4X4		&value)
		{
			this->X = this->X * value.M11 + this->Y * value.M21 + this->Z * value.M31 + this->W * value.M41;
			this->Y = this->X * value.M12 + this->Y * value.M22 + this->Z * value.M32 + this->W * value.M42;
			this->Z = this->X * value.M13 + this->Y * value.M23 + this->Z * value.M33 + this->W * value.M43;
			this->W = this->X * value.M14 + this->Y * value.M24 + this->Z * value.M34 + this->W * value.M44;
			return(*this);
		}

		void VECTOR4D::ZeroVector()
		{
			this->X = this->Y = this->Z = this->W = 0.0f;
		}
        
        void VECTOR4D::Limit(	const Float &lowerLimit, const Float &upperLimit)
        {
			if ( this->X > upperLimit ) {
				this->Y = upperLimit;
			}

			if ( this->Y > upperLimit ) {
				this->Y = upperLimit;
			}

			if ( this->Z > upperLimit ) {
				this->Z = upperLimit;
			}

			if ( this->W > upperLimit ) {
				this->W = upperLimit;
			}

			if ( this->X < lowerLimit ) {
				this->Y = lowerLimit;
			}

			if ( this->Y < lowerLimit ) {
				this->Y = lowerLimit;
			}

			if ( this->Z < lowerLimit ) {
				this->Z = lowerLimit;
			}

			if ( this->W < lowerLimit ) {
				this->W = lowerLimit;
			}
        }

		bool VECTOR4D::operator==(const VECTOR4D &value)
		{
			bool isEqual = false;

			if(this->X == value.X && this->Y == value.Y && this->Z == value.Z)
				isEqual = true;

			return(isEqual);
		}

		bool VECTOR4D::operator!=(const VECTOR4D &value)
		{
			bool isEqual = false;

			if(this->X != value.X && this->Y != value.Y && this->Z != value.Z)
				isEqual = true;

			return(isEqual);
		}

		bool VECTOR4D::IsZero() const
		{
			bool isZero = false;

			if(this->X == 0 && this->Y == 0 && this->Z == 0 && this->W == 0)
				isZero = true;

			return(isZero);
		}

		Aurora::Math::VECTOR4D VECTOR4D::GetZeroVector(void)
		{
			return(VECTOR4D(0,0,0,0));
		}

	}; // END OF NAMESPACE
}; // ENF OF NAMESPACE