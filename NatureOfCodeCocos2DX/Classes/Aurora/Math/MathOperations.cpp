#include "MathOperations.h"
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

		Float Fast2DDistance(Float x, Float y)
		{
			// first compute the absolute value of x,y
			x = abs(x);
			y = abs(y);

			// compute the minimum of x,y
			Int32 mn = (Int32)MIN(x,y);

			// return the distance
			return(x+y-(mn>>1)-(mn>>2)+(mn>>4));
		} // END OF FUNCTION

		Float Fast3DDistance(Float fx, Float fy, Float fz)
		{
			// this function computes the distance from the origin to x,y,z

			int temp;  // used for swaping
			int x,y,z; // used for algorithm

			// make sure values are all positive
			x = static_cast<Int32>(fabs(fx) * 1024);
			y = static_cast<Int32>(fabs(fy) * 1024);
			z = static_cast<Int32>(fabs(fz) * 1024);

			// sort values
			if (y < x) SWAP(x,y,temp)

				if (z < y) SWAP(y,z,temp)

					if (y < x) SWAP(x,y,temp)

						int dist = (z + 11 * (y >> 5) + (x >> 2) );

			// compute distance with 8% error
			return((float)(dist >> 10));
		} // END OF FUNCTION

		Float FastCos(Float theta, lSINCOSTABLES &table)
		{
			theta = fmodf(theta,360);
			if (theta < 0) theta+=360.0;

			int theta_int    = (int)theta;
			float theta_frac = theta - theta_int;

			return(table.CosTable[theta_int] + theta_frac*(table.CosTable[theta_int+1] - table.CosTable[theta_int]));
		} // END OF FUNCTION

		Float FastSin(Float theta, lSINCOSTABLES &table)
		{
			theta = fmodf(theta,360);
			if (theta < 0) theta+=360.0;

			int theta_int    = (int)theta;
			float theta_frac = theta - theta_int;

			return(table.SinTable[theta_int] + theta_frac*(table.SinTable[theta_int+1] - table.SinTable[theta_int]));
		} // END OF FUNCTION

		void ZeroMatrix(MATRIX2X2 *mat)
		{
			mat->M11 = 0;		mat->M12 = 0;
			mat->M21 = 0;		mat->M22 = 0;
		}

		void ZeroMatrix(MATRIX3X3 *mat)
		{
			mat->M11 = 0;		mat->M12 = 0;		mat->M13 = 0;
			mat->M21 = 0;		mat->M22 = 0;		mat->M23 = 0;
			mat->M31 = 0;		mat->M32 = 0;		mat->M33 = 0;
		}

		void ZeroMatrix(MATRIX4X4 *mat)
		{
			mat->M11 = 0;		mat->M12 = 0;		mat->M13 = 0;		mat->M14 = 0;
			mat->M21 = 0;		mat->M22 = 0;		mat->M23 = 0;		mat->M24 = 0;
			mat->M31 = 0;		mat->M32 = 0;		mat->M33 = 0;		mat->M34 = 0;
			mat->M41 = 0;		mat->M42 = 0;		mat->M43 = 0;		mat->M44 = 0;
		}

		void IdentityMatrix(MATRIX2X2 *mat)
		{
			mat->M11 = 1;		mat->M12 = 0;
			mat->M21 = 0;		mat->M22 = 1;
		}

		void IdentityMatrix(MATRIX3X3 *mat)
		{
			mat->M11 = 1;		mat->M12 = 0;		mat->M13 = 0;
			mat->M21 = 0;		mat->M22 = 1;		mat->M23 = 0;
			mat->M31 = 0;		mat->M32 = 0;		mat->M33 = 1;
		}

		void IdentityMatrix(MATRIX4X4 *mat)
		{
			mat->M11 = 1;		mat->M12 = 0;		mat->M13 = 0;		mat->M14 = 0;
			mat->M21 = 0;		mat->M22 = 1;		mat->M23 = 0;		mat->M24 = 0;
			mat->M31 = 0;		mat->M32 = 0;		mat->M33 = 1;		mat->M34 = 0;
			mat->M41 = 0;		mat->M42 = 0;		mat->M43 = 0;		mat->M44 = 1;
		}

		void CopyMatrix(MATRIX2X2 *destination, MATRIX2X2 &source)
		{
			destination->M11 = source.M11;		destination->M12 = source.M12;
			destination->M21 = source.M21;		destination->M22 = source.M22;
		}

		void CopyMatrix(MATRIX3X3 *destination, MATRIX3X3 &source)
		{
			destination->M11 = source.M11;		destination->M12 = source.M12;		destination->M13 = source.M13;
			destination->M21 = source.M21;		destination->M22 = source.M22;		destination->M23 = source.M23;
			destination->M31 = source.M31;		destination->M32 = source.M32;		destination->M33 = source.M33;
		}

		void CopyMatrix(MATRIX4X4 *destination, MATRIX4X4 &source)
		{
			destination->M11 = source.M11;		destination->M12 = source.M12;		destination->M13 = source.M13;		destination->M14 = source.M14;
			destination->M21 = source.M21;		destination->M22 = source.M22;		destination->M23 = source.M23;		destination->M24 = source.M24;
			destination->M31 = source.M31;		destination->M32 = source.M32;		destination->M33 = source.M33;		destination->M34 = source.M34;
			destination->M41 = source.M41;		destination->M42 = source.M42;		destination->M43 = source.M43;		destination->M44 = source.M44;
		}

		void TransposeMatrix(MATRIX3X3 *mat)
		{
			MATRIX3X3 temp;
			temp.M11 = mat->M11;	temp.M12 = mat->M12;	temp.M13 = mat->M13;
			temp.M21 = mat->M21;	temp.M22 = mat->M22;	temp.M23 = mat->M23;
			temp.M31 = mat->M31;	temp.M32 = mat->M32;	temp.M33 = mat->M33;

			/* m11 */				mat->M12 = temp.M21;	mat->M13 = temp.M31;
			mat->M21 = temp.M12;	/* m22 */				mat->M23 = temp.M32;
			mat->M31 = temp.M13;	mat->M32 = temp.M23;	/* m33 */
		}

		void TransposeMatrix(MATRIX4X4 *mat)
		{
			MATRIX4X4 temp;
			temp.M11 = mat->M11;	temp.M12 = mat->M12;	temp.M13 = mat->M13;	temp.M14 = mat->M14;
			temp.M21 = mat->M21;	temp.M22 = mat->M22;	temp.M23 = mat->M23;	temp.M24 = mat->M24;
			temp.M31 = mat->M31;	temp.M32 = mat->M32;	temp.M33 = mat->M33;	temp.M34 = mat->M34;
			temp.M41 = mat->M41;	temp.M42 = mat->M42;	temp.M43 = mat->M43;	temp.M44 = mat->M44;

			/* m11 */				mat->M12 = temp.M21;	mat->M13 = temp.M31;	mat->M14 = temp.M41;
			mat->M21 = temp.M12;	/* m22 */				mat->M23 = temp.M32;	mat->M24 = temp.M42;
			mat->M31 = temp.M13;	mat->M32 = temp.M23;	/* m33 */				mat->M34 = temp.M43;
			mat->M41 = temp.M14;	mat->M42 = temp.M24;	mat->M43 = temp.M34;	/* m44 */
		}

		void TransposeMatrix(MATRIX3X3 *destination, MATRIX3X3 &source)
		{
			destination->M11 = source.M11;		destination->M12 = source.M21;		destination->M13 = source.M31;
			destination->M21 = source.M12;		destination->M22 = source.M22;		destination->M23 = source.M32;
			destination->M31 = source.M13;		destination->M32 = source.M23;		destination->M33 = source.M33;
		}

		void TransposeMatrix(MATRIX4X4 *destination, MATRIX4X4 &source)
		{
			destination->M11 = source.M11;		destination->M12 = source.M21;		destination->M13 = source.M31;	destination->M14 = source.M41;
			destination->M21 = source.M12;		destination->M22 = source.M22;		destination->M23 = source.M32;	destination->M24 = source.M42;
			destination->M31 = source.M13;		destination->M32 = source.M23;		destination->M33 = source.M33;	destination->M34 = source.M43;
			destination->M41 = source.M14;		destination->M42 = source.M24;		destination->M43 = source.M34;	destination->M44 = source.M44;
		}

		void VERTEX2DToPOLAR2D(mPOLAR2D *polar, VERTEX2D &point)
		{
			// convert rectangular to polar
			polar->r     = sqrtf((point.X * point.X) + (point.Y * point.Y));
			polar->theta = atanf(point.Y/point.X);
		}

		void POLAR2DToVERTEX2D(VERTEX2D *point, mPOLAR2D &polar)
		{
			// convert polar to rectangular
			point->X = polar.r*cosf(polar.theta);
			point->Y = polar.r*sinf(polar.theta);
		}

		void POLAR2DToFloatXY(Float *x, Float *y, mPOLAR2D &polar)
		{
			*x = polar.r*cosf(polar.theta);
			*y = polar.r*sinf(polar.theta);
		}

		void VERTEX2DToPolarRTh(Float *r, Float *theta, VERTEX2D &point)
		{
			// convert rectangular to polar
			*r     = sqrtf((point.X * point.X) + (point.Y * point.Y));
			*theta = atanf(point.Y/point.X);
		}

		void CYLINDRICAL3DToVERTEX3D(VERTEX3D *point, mCYLINDRICAL3D &cyl)
		{
			// convert cylindrical to rectangular
			point->X = cyl.r*cosf(cyl.theta);
			point->Y = cyl.r*sinf(cyl.theta);
			point->Z = cyl.z;
		}

		void CYLINDRICAL3DToFloatXYZ(Float *X, Float *Y, Float *Z, mCYLINDRICAL3D &cyl)
		{
			// convert cylindrical to rectangular
			*X = cyl.r*cosf(cyl.theta);
			*Y = cyl.r*sinf(cyl.theta);
			*Z = cyl.z;
		}

		void VERTEX3DToCYLINDRICAL3D(mCYLINDRICAL3D *cyl, VERTEX3D &point)
		{
			// convert rectangular to cylindrical
			cyl->r     = sqrtf((point.X * point.X) + (point.Y * point.Y));
			cyl->theta = atanf(point.Y/point.Y);
			cyl->z     = point.Z;
		}
		
		void VERTEX3DToCylindricalRThZ(float *r, float *theta, float *z, VERTEX3D &point)
		{
			*r     = sqrtf((point.X * point.X) + (point.Y * point.Y));
			*theta = atanf(point.Y/point.Y);
			*z     = point.Z;
		}

		void SPHERICAL3DToVERTEX3D(VERTEX3D *point, mSPHERICAL3D &sph)
		{
			// convert spherical to rectangular
			float r;

			// pre-compute r, and z
			r			= sph.p*sinf(sph.phi);
			point->Z	= sph.p*cosf(sph.phi);

			// use r to simplify computation of x,y
			point->X	= r*cosf(sph.theta);
			point->Y	= r*sinf(sph.theta);
		}
		
		void SPHERICAL3DToFloatXYZ(float *x, float *y, float *z, mSPHERICAL3D &sph)
		{
			// convert spherical to rectangular
			float r;

			// pre-compute r, and z
			r			= sph.p*sinf(sph.phi);
			*z	= sph.p*cosf(sph.phi);

			// use r to simplify computation of x,y
			*x	= r*cosf(sph.theta);
			*y	= r*sinf(sph.theta);
		}

		void VERTEX3DToSPHERICAL3D(mSPHERICAL3D *sph, VERTEX3D &point)
		{
			// convert rectangular to spherical
			sph->p = sqrtf((point.X*point.X)+(point.Y*point.Y)+(point.Z*point.Z));

			sph->theta = atanf(point.Y/point.X);

			// we need r to compute phi
			float r = sph->p*sinf(sph->phi);

			sph->phi   = asinf(r/sph->p);
		}

		void VERTEX3DToSphericalPThPh(float *p, float *theta, float *phi, VERTEX3D &point)
		{
			// convert rectangular to spherical
			*p     = sqrtf((point.X*point.X)+(point.Y*point.Y)+(point.Z*point.Z));
			*theta = atanf(point.Y/point.X);

			// we need r to compute phi
			float r = sqrtf((point.X*point.X) + (point.Y*point.Y));
			*phi    = asinf(r / (*p));
		}

		void DivVECTOR4DByW(VECTOR4D *source)
		{
			source->X /= source->W;
			source->Y /= source->W;
			source->Z /= source->W;
		}

		void DivVECTOR4DByW_VECTOR3D(VECTOR3D *destination, VECTOR4D &source)
		{
			destination->X = source.X / source.W;
			destination->Y = source.Y / source.W;
			destination->Z = source.Z / source.W;
		}

		float VectorDotProduct(const VECTOR2D &v1, const VECTOR2D &v2)
		{
			return( (v1.X * v2.X) + (v1.Y * v2.Y));
		}

		float VectorDotProduct(const VECTOR3D &v1, const VECTOR3D &v2)
		{
			return( (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z));
		}

		float VectorDotProduct(const VECTOR4D &v1, const VECTOR4D &v2)
		{
			return( (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z));
		}

		void NormalizeVector(VECTOR2D *vect)
		{
			float length = sqrtf((vect->X * vect->X) + (vect->Y * vect->Y));
			if (length < EPSILON_E5) 
				return;

			float length_inv = 1/length;
			vect->X = vect->X * length_inv;
			vect->Y = vect->Y * length_inv;
		}

		void NormalizeVector(VECTOR3D *vect)
		{
			float length = sqrtf((vect->X * vect->X) + (vect->Y * vect->Y) + (vect->Z * vect->Z));
			if (length < EPSILON_E5) 
				return;

			float length_inv = 1/length;
			vect->X = vect->X * length_inv;
			vect->Y = vect->Y * length_inv;
			vect->Z = vect->Z * length_inv;
		}

		void NormalizeVector(VECTOR4D *vect)
		{
			float length = sqrtf((vect->X * vect->X) + (vect->Y * vect->Y) + (vect->Z * vect->Z));
			if (length < EPSILON_E5) 
				return;

			float length_inv = 1/length;
			vect->X = vect->X * length_inv;
			vect->Y = vect->Y * length_inv;
			vect->Z = vect->Z * length_inv;
			vect->W = 1.0f;;
		}

		void NormalizeVector(VECTOR2D *destination, const VECTOR2D &source)
		{
			destination->ZeroVector();
			float length = sqrtf((source.X * source.X) + (source.Y * source.Y));
			if (length < EPSILON_E5) 
				return;

			float length_inv = 1/length;
			destination->X = source.X * length_inv;
			destination->Y = source.Y * length_inv;
		}

		void NormalizeVector(VECTOR3D *destination, const VECTOR3D &source)
		{
			destination->ZeroVector();
			float length = sqrtf((source.X * source.X) + (source.Y * source.Y) + (source.Z * source.Z));
			if (length < EPSILON_E5) 
				return;

			float length_inv = 1/length;
			destination->X = source.X * length_inv;
			destination->Y = source.Y * length_inv;
			destination->Z = source.Z * length_inv;
		}

		void NormalizeVector(VECTOR4D *destination, const VECTOR4D &source)
		{
			destination->ZeroVector();
			float length = sqrtf((source.X * source.X) + (source.Y * source.Y) + (source.Z * source.Z));
			if (length < EPSILON_E5) 
				return;

			float length_inv = 1/length;
			destination->X = source.X * length_inv;
			destination->Y = source.Y * length_inv;
			destination->Z = source.Z * length_inv;
			destination->W = 1.0f;
		}

		float VectorLength(const VECTOR2D &vect)
		{
			return(sqrtf( (vect.X * vect.X) + (vect.Y * vect.Y) ));
		}

		float VectorLength(const VECTOR3D &vect)
		{
			return(sqrtf( (vect.X * vect.X) + (vect.Y * vect.Y) + (vect.Z * vect.Z)));
		}

		float VectorLength(const VECTOR4D &vect)
		{
			return(sqrtf( (vect.X * vect.X) + (vect.Y * vect.Y) + (vect.Z * vect.Z)));
		}

		float VectorLengthOptim_1(const VECTOR2D &vect)
		{
			return(Fast2DDistance(vect.X, vect.Y));
		}

		float VectorLengthOptim_1(const VECTOR3D &vect)
		{
			return(Fast3DDistance(vect.X, vect.Y, vect.Z));
		}

		float VectorLengthOptim_1(const VECTOR4D &vect)
		{
			return(Fast3DDistance(vect.X, vect.Y, vect.Z));
		}

		void BuildVectorByVectors(VECTOR2D *destination, const VECTOR2D &init, const VECTOR2D &term)
		{
			destination->X = term.X - init.X;
			destination->Y = term.Y - init.Y;
		}

		void BuildVectorByVectors(VECTOR3D *destination, const VECTOR3D &init, const VECTOR3D &term)
		{
			destination->X = term.X - init.X;
			destination->Y = term.Y - init.Y;
			destination->Z = term.Z - init.Z;
		}

		void BuildVectorByVectors(VECTOR4D *destination, const VECTOR4D &init, const VECTOR4D &term)
		{
			destination->X = term.X - init.X;
			destination->Y = term.Y - init.Y;
			destination->Z = term.Z - init.Z;
			destination->W = 1.0f;
		}

		Float VectorCosTh(const VECTOR2D &vect1, const VECTOR2D &vect2)
		{
			return(VectorDotProduct(vect1,vect2)/(VectorLength(vect1)*VectorLength(vect2)));
		}

		Float VectorCosTh(const VECTOR3D &vect1, const VECTOR3D &vect2)
		{
			return(VectorDotProduct(vect1,vect2)/(VectorLength(vect1)*VectorLength(vect2)));
		}

		Float VectorCosTh(const VECTOR4D &vect1, const VECTOR4D &vect2)
		{
			return(VectorDotProduct(vect1,vect2)/(VectorLength(vect1)*VectorLength(vect2)));
		}

		void VectorCross(VECTOR3D *destination, const VECTOR3D &vect1, const VECTOR3D &vect2)
		{
			destination->X =  ( (vect1.Y * vect2.Z) - (vect1.Z * vect2.Y) );
			destination->Y = -( (vect1.X * vect2.Z) - (vect1.Z * vect2.X) );
			destination->Z =  ( (vect1.X * vect2.Y) - (vect1.Y * vect2.X) ); 
		}

		void VectorCross(VECTOR4D *destination, const VECTOR4D &vect1, const VECTOR4D &vect2)
		{
			destination->X =  ( (vect1.Y * vect2.Z) - (vect1.Z * vect2.Y) );
			destination->Y = -( (vect1.X * vect2.Z) - (vect1.Z * vect2.X) );
			destination->Z =  ( (vect1.X * vect2.Y) - (vect1.Y * vect2.X) ); 
			destination->W = 1.0f;
		}

		VECTOR3D VectorCross(const VECTOR3D &vect1, const VECTOR3D &vect2)
		{
			VECTOR3D destination;
			destination.X =  ( (vect1.Y * vect2.Z) - (vect1.Z * vect2.Y) );
			destination.Y = -( (vect1.X * vect2.Z) - (vect1.Z * vect2.X) );
			destination.Z =  ( (vect1.X * vect2.Y) - (vect1.Y * vect2.X) ); 
			
			return(destination);
		}

		VECTOR4D VectorCross(const VECTOR4D &vect1, const VECTOR4D &vect2)
		{
			VECTOR4D destination;
			destination.X =  ( (vect1.Y * vect2.Z) - (vect1.Z * vect2.Y) );
			destination.Y = -( (vect1.X * vect2.Z) - (vect1.Z * vect2.X) );
			destination.Z =  ( (vect1.X * vect2.Y) - (vect1.Y * vect2.X) ); 
			destination.W = 1.0f;

			return(destination);
		}
		
		bool InverseMatrix(MATRIX2X2 *destination, const MATRIX2X2 &source)
		{
			float det = (source.M11 * source.M22) - (source.M12 * source.M21);
			if(fabs(det) < EPSILON_E5)
			{ return(false); }

			float det_inv = float(1.0/det);
			destination->M11 =	source.M22*det_inv;
			destination->M12 = -source.M12*det_inv;
			destination->M21 = -source.M21*det_inv;
			destination->M22 =	source.M11*det_inv;

			return(true);
		}

		bool InverseMatrix(MATRIX3X3 *destination, const MATRIX3X3 &source)
		{
			// first compute the determinate to see if there is 
			// an inverse
			float det = source.M11*(source.M22*source.M33 - source.M32*source.M23) - 
						source.M12*(source.M21*source.M33 - source.M31*source.M23) + 
						source.M13*(source.M21*source.M32 - source.M31*source.M22);

			if (fabs(det) < EPSILON_E5)
				return(0);

			// compute inverse to save divides
			float det_inv = float(1.0/det);

			// compute inverse using m-1 = adjoint(m)/det(m)
			destination->M11 =  det_inv*(source.M22*source.M33 - source.M32*source.M23);
			destination->M21 = -det_inv*(source.M21*source.M33 - source.M31*source.M23);
			destination->M31 =  det_inv*(source.M21*source.M32 - source.M31*source.M22);

			destination->M12 = -det_inv*(source.M12*source.M33 - source.M32*source.M13);
			destination->M22 =  det_inv*(source.M11*source.M33 - source.M31*source.M13);
			destination->M32 = -det_inv*(source.M11*source.M32 - source.M31*source.M12);

			destination->M13 =  det_inv*(source.M12*source.M23 - source.M22*source.M13);
			destination->M23 = -det_inv*(source.M11*source.M23 - source.M21*source.M13);
			destination->M33 =  det_inv*(source.M11*source.M22 - source.M21*source.M12);

			return(true);
		}

		bool InverseMatrix(MATRIX4X4 *destination, const MATRIX4X4 &source)
		{
			// first compute the determinate to see if there is 
			// an inverse
			float det = source.M11*(source.M22*source.M33 - source.M32*source.M23) - 
						source.M12*(source.M21*source.M33 - source.M31*source.M23) + 
						source.M13*(source.M21*source.M32 - source.M31*source.M22);

			if (fabs(det) < EPSILON_E5)
				return(0);

			// compute inverse to save divides
			float det_inv = float(1.0/det);

			destination->M11 =  det_inv * ( source.M22 * source.M33 - source.M23 * source.M32 );
			destination->M12 = -det_inv * ( source.M12 * source.M33 - source.M13 * source.M32 );
			destination->M13 =  det_inv * ( source.M12 * source.M23 - source.M13 * source.M22 );
			destination->M14 = 0.0f; // always 0

			destination->M21 = -det_inv * ( source.M21 * source.M33 - source.M23 * source.M31 );
			destination->M22 =  det_inv * ( source.M11 * source.M33 - source.M13 * source.M31 );
			destination->M23 = -det_inv * ( source.M11 * source.M23 - source.M13 * source.M21 );
			destination->M24 = 0.0f; // always 0

			destination->M31 =  det_inv * ( source.M21 * source.M31 - source.M22 * source.M31 );
			destination->M32 = -det_inv * ( source.M11 * source.M31 - source.M21 * source.M31 );
			destination->M33 =  det_inv * ( source.M11 * source.M22 - source.M21 * source.M21 );
			destination->M34 = 0.0f; // always 0

			destination->M41 = -( source.M41 * destination->M11 + source.M42 * destination->M21 + source.M43 * destination->M31 );
			destination->M42 = -( source.M41 * destination->M21 + source.M42 * destination->M22 + source.M43 * destination->M32 );
			destination->M43 = -( source.M41 * destination->M31 + source.M42 * destination->M23 + source.M43 * destination->M33 );
			destination->M44 = 1.0f; // always 0

			return(true);
		}

		Float MatrixDeterminant(const MATRIX2X2 &mat)
		{
			return((mat.M11 * mat.M22) - (mat.M12 * mat.M21));
		}

		Float MatrixDeterminant(const MATRIX3X3 &mat)
		{
			return(	mat.M11*(mat.M22*mat.M33 - mat.M32*mat.M23) - 
					mat.M12*(mat.M21*mat.M33 - mat.M31*mat.M23) + 
					mat.M13*(mat.M21*mat.M32 - mat.M31*mat.M22));
		}

		void QUATConjugate(mQUATERNION4D *destination, const mQUATERNION4D &source)
		{
			destination->q0 = source.q0;
			destination->qV.X = -source.qV.X;
			destination->qV.Y = -source.qV.Y;
			destination->qV.Z = -source.qV.Z;
		}

		Float QUATNorm(const mQUATERNION4D &value)
		{
			return(sqrt(value.q0*value.q0 + value.qV.X * value.qV.X + value.qV.Y * value.qV.Y + value.qV.Z * value.qV.Z));
		}

		Float QUATNorm2(const mQUATERNION4D &value)
		{
			return((value.q0*value.q0 + value.qV.X * value.qV.X + value.qV.Y * value.qV.Y + value.qV.Z * value.qV.Z));
		}

		void QUATNormalize(mQUATERNION4D *destination, const mQUATERNION4D &source)
		{
			// this functions normalizes the sent quaternion and 
			// returns it

			// compute 1/length
			float qlength_inv = float(1.0/(sqrtf(source.q0*source.q0 + source.qV.X*source.qV.X + source.qV.Y*source.qV.Y + source.qV.Z*source.qV.Z)));

			// now normalize
			destination->q0=source.q0*qlength_inv;
			destination->qV.X=source.qV.X*qlength_inv;
			destination->qV.Y=source.qV.Y*qlength_inv;
			destination->qV.Z=source.qV.Z*qlength_inv;
		}

		void QUATNormalize(mQUATERNION4D *source)
		{
			// this functions normalizes the sent quaternion and 
			// returns it

			// compute 1/length
			float qlength_inv = float(1.0/(sqrtf(source->q0*source->q0 + source->qV.X*source->qV.X + source->qV.Y*source->qV.Y + source->qV.Z*source->qV.Z)));

			// now normalize
			source->q0*=qlength_inv;
			source->qV.X*=qlength_inv;
			source->qV.Y*=qlength_inv;
			source->qV.Z*=qlength_inv;
		}

		void QUATUnitInverse(mQUATERNION4D *destination, const mQUATERNION4D &source)
		{
			destination->q0 = source.q0;
			destination->qV.X = -source.qV.X;
			destination->qV.Y = -source.qV.Y;
			destination->qV.Z = -source.qV.Z;
		}

		void QUATUnitInverse(mQUATERNION4D *destination)
		{
			destination->qV.X = -destination->qV.X;
			destination->qV.Y = -destination->qV.Y;
			destination->qV.Z = -destination->qV.Z;
		}

		void QUATInverse(mQUATERNION4D *destination, const mQUATERNION4D &source)
		{
			float norm2_inv = float(1.0/(source.q0*source.q0 + source.qV.X*source.qV.X + source.qV.Y*source.qV.Y + source.qV.Z*source.qV.Z));

			destination->q0		=  source.q0*norm2_inv;
			destination->qV.X	= -source.qV.X*norm2_inv;
			destination->qV.Y	= -source.qV.Y*norm2_inv;
			destination->qV.Z	= -source.qV.Z*norm2_inv;
		}

		void QUATInverse(mQUATERNION4D *destination)
		{
			float norm2_inv = float(1.0/(destination->q0*destination->q0 + destination->qV.X*destination->qV.X + destination->qV.Y*destination->qV.Y + destination->qV.Z*destination->qV.Z));

			destination->q0		=  destination->q0*norm2_inv;
			destination->qV.X	= -destination->qV.X*norm2_inv;
			destination->qV.Y	= -destination->qV.Y*norm2_inv;
			destination->qV.Z	= -destination->qV.Z*norm2_inv;
		}

		void QUATMul(mQUATERNION4D *destination, const mQUATERNION4D &source1, const mQUATERNION4D &source2)
		{
			// this function multiplies two quaternions

			// this is the brute force method
			//qprod->w = q1->w*q2->w - q1->x*q2->x - q1->y*q2->y - q1->z*q2->z;
			//qprod->x = q1->w*q2->x + q1->x*q2->w + q1->y*q2->z - q1->z*q2->y;
			//qprod->y = q1->w*q2->y - q1->x*q2->z + q1->y*q2->w - q1->z*q2->x;
			//qprod->z = q1->w*q2->z + q1->x*q2->y - q1->y*q2->x + q1->z*q2->w;

			// this method was arrived at basically by trying to factor the above
			// expression to reduce the # of multiplies

			float prd_0 = (source1.qV.Z		- source1.qV.Y) * (source2.qV.Y		- source2.qV.Z);
			float prd_1 = (source1.q0		+ source1.qV.X) * (source2.q0		+ source2.qV.X);
			float prd_2 = (source1.q0		- source1.qV.X) * (source2.qV.Y		+ source2.qV.Z);
			float prd_3 = (source1.qV.Y		+ source1.qV.Z) * (source2.q0		- source2.qV.X);
			float prd_4 = (source1.qV.Z		- source1.qV.X) * (source2.qV.X		- source2.qV.Y);
			float prd_5 = (source1.qV.Z		+ source1.qV.X) * (source2.qV.X		+ source2.qV.Y);
			float prd_6 = (source1.q0		+ source1.qV.Y) * (source2.q0		- source2.qV.Z);
			float prd_7 = (source1.q0		- source1.qV.Y) * (source2.q0		+ source2.qV.Z);

			float prd_8 = prd_5 + prd_6 + prd_7;
			float prd_9 = float(0.5 * (prd_4 + prd_8));

			// and finally build up the result with the temporary products

			destination->q0		= prd_0 + prd_9 - prd_5;
			destination->qV.X	= prd_1 + prd_9 - prd_8;
			destination->qV.Y	= prd_2 + prd_9 - prd_7;
			destination->qV.Z	= prd_3 + prd_9 - prd_6;
		}

		void QUAT_TripleProduct(mQUATERNION4D *destination, const mQUATERNION4D &source1, const mQUATERNION4D &source2, const mQUATERNION4D &source3)
		{
			mQUATERNION4D qtemp;
			QUATMul(&qtemp, source1, source2);
			QUATMul(destination, qtemp, source3);
		}

		void VECTOR3D_ThetaToQUAT(mQUATERNION4D *destination, const VECTOR3D &vect, Float theta)
		{
			float theta_div_2 = float((0.5)*theta);
			float sinf_theta = sinf(theta_div_2);
			destination->qV.X = sinf_theta * vect.X;
			destination->qV.Y = sinf_theta * vect.Y;
			destination->qV.Z = sinf_theta * vect.Z;
			destination->q0 = cosf( theta_div_2 );
		}

		void VECTOR4D_ThetaToQUAT(mQUATERNION4D *destination, const VECTOR4D &vect, Float theta)
		{
			float theta_div_2 = float((0.5)*theta);
			float sinf_theta = sinf(theta_div_2);
			destination->qV.X = sinf_theta * vect.X;
			destination->qV.Y = sinf_theta * vect.Y;
			destination->qV.Z = sinf_theta * vect.Z;
			destination->q0 = cosf( theta_div_2 );
		}

		void EulerZYX_ToQUAT(mQUATERNION4D *destination, float theta_z, float theta_y, float theta_x)
		{
			float cos_z_2 = float(0.5*cosf(theta_z));
			float cos_y_2 = float(0.5*cosf(theta_y));
			float cos_x_2 = float(0.5*cosf(theta_x));

			float sin_z_2 = float(0.5*sinf(theta_z));
			float sin_y_2 = float(0.5*sinf(theta_y));
			float sin_x_2 = float(0.5*sinf(theta_x));

			// and now compute quaternion
			destination->q0   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
			destination->qV.X = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
			destination->qV.Y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
			destination->qV.Z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
		}

		void QUAT_ToVECTOR3DTheta(VECTOR3D *vect, const mQUATERNION4D &quat, float *theta)
		{
			*theta = acosf(quat.q0);
			float sinf_theta_inv = float(1.0/sinf(*theta));
			vect->X    = quat.qV.X*sinf_theta_inv;
			vect->Y    = quat.qV.Y*sinf_theta_inv;
			vect->Z    = quat.qV.Z*sinf_theta_inv;

			// multiply by 2
			*theta*=2;
		}

		void ComputeParmLine2D(VERTEX2D *point, const mPARAMETRICLINE2D &line, float t)
		{
			point->X = line.point1.X + line.v.X*t;
			point->Y = line.point1.Y + line.v.Y*t;
		}

		void ComputeParmLine3D(VERTEX3D *point, const mPARAMETRICLINE3D &line, float t)
		{
			point->X = line.point1.X + line.v.X*t;
			point->Y = line.point1.Y + line.v.Y*t;
			point->Z = line.point1.Z + line.v.Z*t;
		}

		MATRIX4X4 BuildModelToWorldTransformationMatrix(const VECTOR4D &worldPosition)
		{
			return(MATRIX4X4(	1,					0,					0,					0,
								0,					1,					0,					0,
								0,					0,					1,					0,
								worldPosition.X,	worldPosition.Y,	worldPosition.Z,	1));
		}

	}; // END OF NAMESPACE
}; // END OF NAMESPACE