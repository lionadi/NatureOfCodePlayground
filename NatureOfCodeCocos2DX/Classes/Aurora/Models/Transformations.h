#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include "..\Math\MathOperations.h"
#include "..\Models\ModelDefines.h"

using namespace Aurora::DataTypes;
using namespace Aurora::Model;


/*!
Namespace: Liana

This namespace is the main package for the engine. It holds all the main classes, namespaces, operations etc... that defines the functionality of this
project/engine.
*/
namespace Aurora
{
	/*!
	Namespace: Math

	This namespace holds needed math operations for the engine.
	*/
	namespace Model
	{
			/*!
			\brief This enumeration holds all of the transformation methods needed for object/models transformation operations.
			*/
			enum mTRANSFORMATIONS
			{
				NONE,
				TRANSFORM_LOCALONLY,
				TRANSFORM_TRANSONLY,
				TRANSFORM_LOCALTOTRANS
			};
			/*!
			  \brief Use this function to transform an object by a specified matrix.
			  \param *object Object to transform
			  \param *transformationMatrix The transformation matrix
			  \param transformationMethod The method of transformation
			 */
			extern void TransformObjectRenderList(mOBJECT4D *object, const MATRIX4X4 *transformationMatrix, mTRANSFORMATIONS transformationMethod);
			/*!
			  \brief Use this function to transform an model by a specified matrix.
			  \param *model The model to be transformed
			  \param *transformationMatrix The transformation matrix
			  \param transformationMethod The method of transformation
			  \param TransformBasis Use this boolean to determine if the function should also transform the model object orientation.
			 */
			extern void TransformModelRenderLists(mMODEL4D *model, const MATRIX4X4 *transformationMatrix, mTRANSFORMATIONS transformationMethod, bool  TransformBasis);
			/*!
			  \brief Transform an object by using it's own world position data
			  \param *object The object to be transformed
			  \param transformationMethod The method how to transform the object
			 */
			extern void TransformObjectToWorld(mOBJECT4D *object, mTRANSFORMATIONS transformationMethod = TRANSFORM_LOCALTOTRANS);
			/*!
			  \brief Transforms an object to world coordinates by a given world position
			  \param *object The object to be transformed
			  \param worldPosition The world position data for the transformation
			  \param transformationMethod The method how to transform the object
			 */
			extern void TransformObjectToWorld(mOBJECT4D *object, const VECTOR4D *worldPosition, mTRANSFORMATIONS transformationMethod = TRANSFORM_LOCALTOTRANS);

			/*!
			  \brief Transform an object using a given world position transformation matrix
			  \param *object The object to be transformed
			  \param *worldPosition The world position transformation matrix
			  \param transformationMethod The method how to transform the object
			 */
			extern void TransformObjectToWorld(mOBJECT4D *object, const MATRIX4X4 *worldPosition, mTRANSFORMATIONS transformationMethod = TRANSFORM_LOCALTOTRANS);
			
			/*!
			  \brief Transform the model to world position by model object world position values
			  \param *model The model to be transformed
			  \param transformationMethod The method how to transform the model
			 */
			extern void TransformModelToWorld(mMODEL4D *model, mTRANSFORMATIONS transformationMethod = TRANSFORM_LOCALTOTRANS);
			
			/*!
			  \brief Transform the model to world position by the given world position parameter
			  \param *model The model to be transformed
			  \param *worldPosition The transformation data
			  \param transformationMethod The method how to transform the model
			 */
			extern void TransformModelToWorld(mMODEL4D *model, const VECTOR4D *worldPosition, mTRANSFORMATIONS transformationMethod = TRANSFORM_LOCALTOTRANS);

			/*!
			  \brief Transform the model to world position by the given world position parameter
			  \param *model The model to be transformed
			  \param *worldPosition The transformation data
			  \param transformationMethod The method how to transform the model
			 */
			extern void TransformModelToWorld(mMODEL4D *model, const MATRIX4X4 *worldPosition, mTRANSFORMATIONS transformationMethod = TRANSFORM_LOCALTOTRANS);

	} // END OF NAMESPACE MATH
}// END OF NAMESPACE AURORA

#endif