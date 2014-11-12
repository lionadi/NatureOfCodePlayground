#ifndef MATHDATATYPES_H
#define MATHDATATYPES_H
#include "Vector.h"
#include "..\Globals\GlobalOperations.h"
#include <math.h>
using namespace Aurora::DataTypes;
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

			#define EPSILON_E3 (float)(1E-3) 
			#define EPSILON_E4 (float)(1E-4) 
			#define EPSILON_E5 (float)(1E-5)
			#define EPSILON_E6 (float)(1E-6)

			class mRECT
			{
			public:
				mRECT();
				mRECT(int width, int height);
				~mRECT();
				mRECT(const mRECT &value);
				mRECT & operator=(const mRECT & value);
				mRECT(mRECT &&value);
				mRECT & operator=(mRECT && value);

				int Width;
				int Height;

				bool operator==(const mRECT		&value);

				bool operator!=(const mRECT		&value);

				bool IsZero() const;
			};

			/*!
				\brief Datatype for a 2D parametric line
			*/
			class mPARAMETRICLINE2D
			{
				public:
					mPARAMETRICLINE2D(VERTEX2D &init, VERTEX2D &term);
					~mPARAMETRICLINE2D();
					VERTEX2D point1;		/*!< Start point of parametric line					*/
					VERTEX2D point2;		/*!< End point of parametric line					*/
					VECTOR2D v;				/*!< Direction vector of line segment |v|=|p0->p1|.	*/
			};

			/*!
				\brief Datatype for a 3D parametric line
			*/
			class mPARAMETRICLINE3D
			{
				public:
					mPARAMETRICLINE3D(VERTEX3D &init, VERTEX3D &term);
					~mPARAMETRICLINE3D();
					VERTEX3D point1;		/*!< Start point of parametric line			*/
					VERTEX3D point2;		/*!< End point of parametric line			*/
					VECTOR3D v;				/*!< Direction vector of line segment		*/
			};

			/*!
				\brief 3D Plane
			*/
			class mPLANE3D
			{
				public:
					mPLANE3D(const VECTOR3D &point, const VECTOR3D &normal, bool Normalize);
					~mPLANE3D();
					VERTEX3D point;			/*!< Point on the plane.									*/
					VECTOR3D normal;		/*!< Normal to the plane. (not necessarily a unit vector)	*/
			};

			/*!
			\brief 2D polar coordinates
			*/
			class mPOLAR2D
			{
				public:
					Float r;				/*!< The radius of the point.	*/
					Float theta;			/*!< The angle in rads.			*/
			};

			/*!
			\brief 3D cylindrical coordinates
			*/
			class mCYLINDRICAL3D
			{
				public:
					Float r;				/*!< The radius of the point.				*/
					Float theta;			/*!< The angle in degrees about the z axis. */
					Float z;				/*!< The z-height of the point.				*/
			};

			/*!
			\brief 3D spherical coordinates
			*/
			class mSPHERICAL3D
			{
				public:
					Float p;				/*!< Rho, the distance to the point from the origin.							*/
					Float theta;			/*!< The angle from the z-axis and the line segment o->p.						*/
					Float phi;				/*!< The angle from the projection if o->p onto the x-y plane and the x-axis.	*/
			};

			typedef int FIXP16;			/*!< fixed point type */
			typedef int *FIXP16_PTR;	/*!< fixed point type */

		/*!
		\brief 4d quaternion
		*/
		class mQUATERNION4D
		{
			public:
				mQUATERNION4D();
				mQUATERNION4D(Float q0, VECTOR3D qv);
				mQUATERNION4D(const mQUATERNION4D &value);
				~mQUATERNION4D();
				mQUATERNION4D &operator=(const mQUATERNION4D		&value);
				mQUATERNION4D operator+(const mQUATERNION4D			&value);
				mQUATERNION4D &operator+=(const mQUATERNION4D		&value);
				mQUATERNION4D operator-(const mQUATERNION4D			&value);
				mQUATERNION4D &operator-=(const mQUATERNION4D		&value);
				mQUATERNION4D operator*(const mQUATERNION4D			&value);
				mQUATERNION4D operator*(const float					&value);
				mQUATERNION4D &operator*=(const float				&value);
				mQUATERNION4D &operator*=(const mQUATERNION4D		&value);
				Float		q0;			/*!< The real part.						*/
				VECTOR3D	qV;			/*!< The imaginary part xi+yj+zk.		*/
				void ZeroQuarternion(void);
		};

	}; // END OF NAMESPACE
}; // END OF NAMESPACE

#endif