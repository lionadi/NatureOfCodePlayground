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

		VECTOR2D::VECTOR2D()
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
		VECTOR2D VECTOR2D::operator+(const Float &value)
		{
			
			
			return(VECTOR2D(this->X + value,this->Y + value));
		}

		VECTOR2D VECTOR2D::operator+(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			return(VECTOR2D(this->X + value.X, this->Y + value.Y));
		}

		// SUBSTRACTION - OPERATIONS
		//--------------------------------------------------------
		VECTOR2D VECTOR2D::operator-(const Float &value)
		{
			return(VECTOR2D(this->X - value, this->Y - value));
		}

		VECTOR2D VECTOR2D::operator-(const VECTOR2D &value)
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

		VECTOR2D &VECTOR2D::operator-=(const Float &value)
		{
			this->X -= value;
			this->Y -= value;
			return(*this);
		}

		VECTOR2D &VECTOR2D::operator-=(const VECTOR2D &value)
		{
			if(this == &value) { return(*this); }
			this->X -= value.X;
			this->Y -= value.Y;
			return(*this);
		}	
		
		VECTOR2D VECTOR2D::operator*(const Float		&value)
		{
			return(VECTOR2D(this->X * value, this->Y * value));
		}

		
		Float VECTOR2D::operator*(const VECTOR2D		&value)
		{
			return((this->X * value.X) + (this->Y * value.Y));
		}
		
		VECTOR2D &VECTOR2D::operator*=(const Float		&value)
		{
			this->X *= value;
			this->Y *= value;
			return(*this);
		}
        
        VECTOR2D VECTOR2D::operator/(const Float		&value)
        {
            return(VECTOR2D(this->X / value, this->Y / value));
        }
        
        VECTOR2D VECTOR2D::operator*(const MATRIX2X2		&value)
        {
            return(VECTOR2D(	this->X * value.M11 + this->Y * value.M21,
                                this->X * value.M12 + this->Y * value.M22));
        }
        
        VECTOR2D &VECTOR2D::operator*=(const MATRIX2X2		&value)
        {
            this->X = this->X * value.M11 + this->Y * value.M21;
            this->Y = this->X * value.M12 + this->Y * value.M22;

            return(*this);
        }

		void VECTOR2D::ZeroVector()
		{
			this->X = this->Y = 0.0f;
		}
        
        void VECTOR2D::Limit(const Float limit)
        {
            if ( this->X > limit ) {
                this->Y = limit;
            }
            
            if ( this->Y > limit ) {
                this->Y = limit;
            }
        }

// VECTOR3D -----------------------------------------------------------
		VECTOR3D::VECTOR3D()
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
        
        void VECTOR3D::Limit(const Float limit)
        {
            if ( this->X > limit ) {
                this->Y = limit;
            }
            
            if ( this->Y > limit ) {
                this->Y = limit;
            }
            
            if ( this->Z > limit ) {
                this->Z = limit;
            }
        }
        
// VECTOR4D -----------------------------------------------------------
		VECTOR4D::VECTOR4D()
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
        
        void VECTOR4D::Limit(const Float limit)
        {
            if ( this->X > limit ) {
                this->Y = limit;
            }
            
            if ( this->Y > limit ) {
                this->Y = limit;
            }
            
            if ( this->Z > limit ) {
                this->Z = limit;
            }
            
            if ( this->W > limit ) {
                this->W = limit;
            }
        }

	}; // END OF NAMESPACE
}; // ENF OF NAMESPACE