#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H

#include "Vector.h"
#include "Matrix.h"
#include "MathDataTypes.h"
//#include <Transformations.h>
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
		#define DEG_TO_RAD(ang) ((ang)*PI/180.0)
		#define RAD_TO_DEG(rads) ((rads)*180.0/PI)

		extern "C"
		{
		/*!
			\brief Calculates in a fast way the distance from the origin(0,0) to the given point.
			\param x 
			\param y 
			\return 
		*/
		Float Fast2DDistance(Float x, Float y);
		/*!
			\brief Calculates in a fast way the distance from the origin(0,0,0) to the given point.
			\param fx 
			\param fy 
			\param fz 
			\return 
		*/
		Float Fast3DDistance(Float fx, Float fy, Float fz);
		
		
		/*!
			\brief 
			\param theta 
			\param &table 
			\return 
		*/
		Float FastCos(Float theta, lSINCOSTABLES &table);
		/*!
			\brief 
			\param theta 
			\param &table 
			\return 
		*/
		Float FastSin(Float theta, lSINCOSTABLES &table);

		/*!
			\brief 
			\param *polar 
			\param &point 
		*/
		void VERTEX2DToPOLAR2D(mPOLAR2D *polar, VERTEX2D &point);
		/*!
			\brief 
			\param *point 
			\param &polar 
		*/
		void POLAR2DToVERTEX2D(VERTEX2D *point, mPOLAR2D &polar);
		/*!
			\brief 
			\param *x 
			\param *y 
			\param &polar 
		*/
		void POLAR2DToFloatXY(Float *x, Float *y, mPOLAR2D &polar);
		/*!
			\brief 
			\param *r 
			\param *theta 
			\param &point 
		*/
		void VERTEX2DToPolarRTh(Float *r, Float *theta, VERTEX2D &point);

		/*!
			\brief 
			\param *point 
			\param &cyl 
		*/
		void CYLINDRICAL3DToVERTEX3D(VERTEX3D *point, mCYLINDRICAL3D &cyl);
		/*!
			\brief 
			\param *X 
			\param *Y 
			\param *Z 
			\param &cyl 
		*/
		void CYLINDRICAL3DToFloatXYZ(Float *X, Float *Y, Float *Z, mCYLINDRICAL3D &cyl);
		/*!
			\brief 
			\param *cyl 
			\param &point 
		*/
		void VERTEX3DToCYLINDRICAL3D(mCYLINDRICAL3D *cyl, VERTEX3D &point);
		/*!
			\brief 
			\param *r 
			\param *theta 
			\param *z 
			\param &point 
		*/
		void VERTEX3DToCylindricalRThZ(float *r, float *theta, float *z, VERTEX3D &point);

		/*!
			\brief 
			\param *point 
			\param &sph 
		*/
		void SPHERICAL3DToVERTEX3D(VERTEX3D *point, mSPHERICAL3D &sph);
		/*!
			\brief 
			\param *x 
			\param *y 
			\param *z 
			\param &sph 
		*/
		void SPHERICAL3DToFloatXYZ(float *x, float *y, float *z, mSPHERICAL3D &sph);
		/*!
			\brief 
			\param *sph 
			\param &point 
		*/
		void VERTEX3DToSPHERICAL3D(mSPHERICAL3D *sph, VERTEX3D &point);
		/*!
			\brief 
			\param *p 
			\param *theta 
			\param *phi 
			\param &point 
		*/
		void VERTEX3DToSphericalPThPh(float *p, float *theta, float *phi, VERTEX3D &point);
		
		}; // END OF "C" extern

		/*!
			\brief 
			\param *mat 
		*/
		extern inline void ZeroMatrix(MATRIX2X2 *mat);
		/*!
			\brief 
			\param *mat 
		*/
		extern inline void ZeroMatrix(MATRIX3X3 *mat);
		/*!
			\brief 
			\param *mat 
		*/
		extern inline void ZeroMatrix(MATRIX4X4 *mat);

		/*!
			\brief 
			\param *mat 
		*/
		extern inline void IdentityMatrix(MATRIX2X2 *mat);
		/*!
			\brief 
			\param *mat 
		*/
		extern inline void IdentityMatrix(MATRIX3X3 *mat);
		/*!
			\brief 
			\param *mat 
		*/
		extern inline void IdentityMatrix(MATRIX4X4 *mat);

		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern inline void CopyMatrix(MATRIX2X2 *destination, MATRIX2X2 &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern inline void CopyMatrix(MATRIX3X3 *destination, MATRIX3X3 &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern inline void CopyMatrix(MATRIX4X4 *destination, MATRIX4X4 &source);

		/*!
			\brief 
			\param *mat 
		*/
		extern inline void TransposeMatrix(MATRIX3X3 *mat);
		/*!
			\brief 
			\param *mat 
		*/
		extern inline void TransposeMatrix(MATRIX4X4 *mat);

		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern inline void TransposeMatrix(MATRIX3X3 *destination, MATRIX3X3 &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern inline void TransposeMatrix(MATRIX4X4 *destination, MATRIX4X4 &source);

		//extern inline void MatrixSwapColumn(MATRIX4X4 *destination, MATRIX4X4 &source, int column);
		//extern inline void MatrixSwapColumn(MATRIX4X4 *destination, MATRIX4X4 &source, int column);

		extern inline void DivVECTOR4DByW(VECTOR4D *source);
		/*!
			\brief Divides the VECTOR4D components(x,y,z) by w and inserts the new values into VECTOR3D components(x=x, y=y,z=z)
			\param *destination 
			\param &source 
		*/
		extern inline void DivVECTOR4DByW_VECTOR3D(VECTOR3D *destination, VECTOR4D &source);

		/*! Convert integer and float to fixed point 16.16. */
		#define INT_TO_FIXP16(i) ((i) <<  FIXP16_SHIFT)
		/*! Convert integer and float to fixed point 16.16. */
		#define FLOAT_TO_FIXP16(f) (((float)(f) * (float)FIXP16_MAG+0.5))

		/*! Convert fixed point to float. */
		#define FIXP16_TO_FLOAT(fp) ( ((float)fp)/FIXP16_MAG)

		/*! Extract the whole part and decimal part from a fixed point 16.16. */
		#define FIXP16_WP(fp) ((fp) >> FIXP16_SHIFT)
		/*! Extract the whole part and decimal part from a fixed point 16.16. */
		#define FIXP16_DP(fp) ((fp) && FIXP16_DP_MASK)

	
		/*!
			\brief 
			\param &v1 
			\param &v2 
			\return 
		*/
		extern Float VectorDotProduct(const VECTOR2D &v1, const VECTOR2D &v2);
		/*!
			\brief 
			\param &v1 
			\param &v2 
			\return 
		*/
		extern Float VectorDotProduct(const VECTOR3D &v1, const VECTOR3D &v2);
		/*!
			\brief 
			\param &v1 
			\param &v2 
			\return 
		*/
		extern Float VectorDotProduct(const VECTOR4D &v1, const VECTOR4D &v2);

		/*!
			\brief 
			\param *vect 
		*/
		extern void NormalizeVector(VECTOR2D *vect);
		/*!
			\brief 
			\param *vect 
		*/
		extern void NormalizeVector(VECTOR3D *vect);
		/*!
			\brief 
			\param *vect 
		*/
		extern void NormalizeVector(VECTOR4D *vect);
		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern void NormalizeVector(VECTOR2D *destination, const VECTOR2D &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern void NormalizeVector(VECTOR3D *destination, const VECTOR3D &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern void NormalizeVector(VECTOR4D *destination, const VECTOR4D &source);

		/*!
			\brief 
			\param &vect 
			\return 
		*/
		extern Float VectorLength(const VECTOR2D &vect);
		/*!
			\brief 
			\param &vect 
			\return 
		*/
		extern Float VectorLength(const VECTOR3D &vect);
		/*!
			\brief 
			\param &vect 
			\return 
		*/
		extern Float VectorLength(const VECTOR4D &vect);

		/*!
			\brief 
			\param &vect 
			\return 
		*/
		extern Float VectorLengthOptim_1(const VECTOR2D &vect);
		/*!
			\brief 
			\param &vect 
			\return 
		*/
		extern Float VectorLengthOptim_1(const VECTOR3D &vect);
		/*!
			\brief 
			\param &vect 
			\return 
		*/
		extern Float VectorLengthOptim_1(const VECTOR4D &vect);

		/*!
			\brief Builds a vector out of the subtraction of two vectors.
			\param *destination 
			\param &init 
			\param &term 
		*/
		extern void BuildVectorByVectors(VECTOR2D *destination, const VECTOR2D &init, const VECTOR2D &term);
		/*!
			\brief Builds a vector out of the subtraction of two vectors.
			\param *destination 
			\param &init 
			\param &term 
		*/
		extern void BuildVectorByVectors(VECTOR3D *destination, const VECTOR3D &init, const VECTOR3D &term);
		/*!
			\brief Builds a vector out of the subtraction of two vectors.
			\param *destination 
			\param &init 
			\param &term 
		*/
		extern void BuildVectorByVectors(VECTOR4D *destination, const VECTOR4D &init, const VECTOR4D &term);

		/*!
			\brief This function returns the cosine of the angle between two vectors. Note, we could compute the actual angle, many many times, in further calcs we will want ultimately compute cos of the angle, so why not just leave it!
			\param &vect1 
			\param &vect2 
			\return 
		*/
		extern Float VectorCosTh(const VECTOR2D &vect1, const VECTOR2D &vect2);
		/*!
			\brief 
			\param &vect1 
			\param &vect2 
			\return 
		*/
		extern Float VectorCosTh(const VECTOR3D &vect1, const VECTOR3D &vect2);
		/*!
			\brief 
			\param &vect1 
			\param &vect2 
			\return 
		*/
		extern Float VectorCosTh(const VECTOR4D &vect1, const VECTOR4D &vect2);
		
		/*!
			\brief 
			\param *destination 
			\param &vect1 
			\param &vect2 
		*/
		extern void VectorCross(VECTOR3D *destination, const VECTOR3D &vect1, const VECTOR3D &vect2);
		/*!
			\brief 
			\param *destination 
			\param &vect1 
			\param &vect2 
		*/
		extern void VectorCross(VECTOR4D *destination, const VECTOR4D &vect1, const VECTOR4D &vect2);
		/*!
			\brief 
			\param &vect1 
			\param &vect2 
			\return 
		*/
		extern VECTOR3D VectorCross(const VECTOR3D &vect1, const VECTOR3D &vect2);
		/*!
			\brief 
			\param &vect1 
			\param &vect2 
			\return 
		*/
		extern VECTOR4D VectorCross(const VECTOR4D &vect1, const VECTOR4D &vect2);

		/*!
			\brief 
			\param *destination 
			\param &source 
			\return 
		*/
		extern bool InverseMatrix(MATRIX2X2 *destination, const MATRIX2X2 &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
			\return 
		*/
		extern bool InverseMatrix(MATRIX3X3 *destination, const MATRIX3X3 &source);
		/*!
			\brief 
			\param *destination 
			\param &source 
			\return 
		*/
		extern bool InverseMatrix(MATRIX4X4 *destination, const MATRIX4X4 &source);

		/*!
			\brief 
			\param &mat 
			\return 
		*/
		extern Float MatrixDeterminant(const MATRIX2X2 &mat);
		/*!
			\brief 
			\param &mat 
			\return 
		*/
		extern Float MatrixDeterminant(const MATRIX3X3 &mat);

		/*!
			\brief 
			\param *destination 
			\param &source 
		*/
		extern void QUATConjugate(mQUATERNION4D *destination, const mQUATERNION4D &source);

		/*!
			\brief returns the length or norm of a quaternion
			\param &value 
			\return 
		*/
		extern Float QUATNorm(const mQUATERNION4D &value);
		/*!
			\brief returns the length or norm of a quaternion squared
			\param &value 
			\return 
		*/
		extern Float QUATNorm2(const mQUATERNION4D &value);

		/*!
			\brief this functions normalizes the sent quaternion and returns it
			\param *destination 
			\param &source 
		*/
		extern void QUATNormalize(mQUATERNION4D *destination, const mQUATERNION4D &source);
		/*!
			\brief this functions normalizes the sent quaternion in place
			\param *source 
		*/
		extern void QUATNormalize(mQUATERNION4D *source);
		/*!
			\brief this function computes the inverse of a unit quaternion and returns the result the inverse of a unit quaternion is the conjugate
			\param *destination 
			\param &source 
		*/
		extern void QUATUnitInverse(mQUATERNION4D *destination, const mQUATERNION4D &source);
		/*!
			\brief this function computes the inverse of a unit quaternion and returns the result the inverse of a unit quaternion is the conjugate
			\param *destination 
		*/
		extern void QUATUnitInverse(mQUATERNION4D *destination);
		
		/*!
			\brief this function computes the inverse of a general quaternion and returns result in general, q-1 = *q/|q|2
			\param *destination 
			\param &source 
		*/
		extern void QUATInverse(mQUATERNION4D *destination, const mQUATERNION4D &source);
		/*!
			\brief 
			\param *destination 
		*/
		extern void QUATInverse(mQUATERNION4D *destination);

		/*!
			\brief this function multiplies two quaternions
			\param *destination 
			\param &source1 
			\param &source2 
		*/
		extern void QUATMul(mQUATERNION4D *destination, const mQUATERNION4D &source1, const mQUATERNION4D &source2);

		extern void QUAT_TripleProduct(mQUATERNION4D *destination, const mQUATERNION4D &source1, const mQUATERNION4D &source2, const mQUATERNION4D &source3);

		/*!
			\brief initializes a quaternion based on a 3d direction vector and angle note the direction vector must be a unit vector and the angle is in rads
			\param *destination 
			\param &vect 
			\param theta 
		*/
		extern void VECTOR3D_ThetaToQUAT(mQUATERNION4D *destination, const VECTOR3D &vect, Float theta);

		/*!
			\brief 
			\param *destination 
			\param &vect 
			\param theta 
		*/
		extern void VECTOR4D_ThetaToQUAT(mQUATERNION4D *destination, const VECTOR4D &vect, Float theta);

		/*!
			\brief this function initializes a quaternion based on the zyx multiplication order of the angles that are parallel to the zyx axis respectively, note there are 11 other possibilities this is just one
			\param *destination 
			\param theta_z 
			\param theta_y 
			\param theta_x 
		*/
		extern void EulerZYX_ToQUAT(mQUATERNION4D *destination, float theta_z, float theta_y, float theta_x);

		/**
		 *
		 * \param *vect 
		 * \param &quat 
		 * \param *theta 
		 */
		extern void QUAT_ToVECTOR3DTheta(VECTOR3D *vect, const mQUATERNION4D &quat, float *theta);

		/**
		 *
		 * \param *point 
		 * \param &line 
		 * \param t 
		 */
		extern void ComputeParmLine2D(VERTEX2D *point, const mPARAMETRICLINE2D &line, float t);

		/**
		 *
		 * \param *point 
		 * \param &line 
		 * \param t 
		 */
		extern void ComputeParmLine3D(VERTEX3D *point, const mPARAMETRICLINE3D &line, float t);

		/*!
		  \brief
		  \param &worldPosition 
		  \return 
		 */
		extern MATRIX4X4 BuildModelToWorldTransformationMatrix(const VECTOR4D &worldPosition);
        
	}; // END OF NAMESPACE
}; // END OF NAMESPACE

#endif