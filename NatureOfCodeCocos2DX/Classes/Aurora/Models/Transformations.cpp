//#include "stdafx.h"
#include "Transformations.h"

namespace Aurora
{
	namespace Model
	{
		void TransformPolygonRenderList(mOBJECT4D *object, const MATRIX4X4 *transformationMatrix, mTRANSFORMATIONS transformationMethod)
		{
			mPOLYGON4D *currentPolygon;
			mPOLYGON4D *transformedPolygon;
			
			switch(transformationMethod)
			{
				case TRANSFORM_LOCALONLY:
				{
					if(object->PolygonList == NULL) { return; }
					for(int poly = 0; poly < object->PolygonAmount; ++poly)
					{
						currentPolygon = &object->PolygonList[poly];
						// is this polygon valid?
          				// transform this polygon if and only if it's not clipped, not culled,
          				// active, and visible, note however the concept of "backface" is 
          				// irrelevant in a wire frame engine though
						if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
						{
							for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
							{
								currentPolygon->VertexList->VertexData[x] *= *transformationMatrix;
							}
						}
					} // END OF FOR
				} break;

				case TRANSFORM_TRANSONLY:
				{
					if(object->TransformedPolygonList == NULL) { return; }
					for(int poly = 0; poly < object->PolygonAmount; ++poly)
					{
						transformedPolygon = &object->TransformedPolygonList[poly];
						// is this polygon valid?
          				// transform this polygon if and only if it's not clipped, not culled,
          				// active, and visible, note however the concept of "backface" is 
          				// irrelevant in a wire frame engine though
						if(transformedPolygon->PolygonStates == POLY_ACTIVE || transformedPolygon->PolygonStates != POLY_CLIPPED || transformedPolygon->PolygonStates != POLY_BACKFACE)
						{
							for(int x = 0; x < transformedPolygon->VertexList->vertexAmount; ++x)
							{
								transformedPolygon->VertexList->VertexData[x] *= *transformationMatrix;
							}
						}
					} // END OF FOR
				} break;

				case TRANSFORM_LOCALTOTRANS:
				{
					if(object->PolygonList == NULL) { return; }
					object->AllocateMemoryToTransformedPolygonList();
					for(int poly = 0; poly < object->PolygonAmount; ++poly)
					{
						currentPolygon = &object->PolygonList[poly];
						transformedPolygon = &object->TransformedPolygonList[poly];
						// is this polygon valid?
          				// transform this polygon if and only if it's not clipped, not culled,
          				// active, and visible, note however the concept of "backface" is 
          				// irrelevant in a wire frame engine though
						if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
						{
							for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
							{
								transformedPolygon->VertexList->VertexData[x] = currentPolygon->VertexList->VertexData[x] * *transformationMatrix;
							}
						}
					} // END OF FOR
				} break;

				default: { } break;
			} // END OF SWITCH
		} // END OF FUNCTION

		void TransformModelRenderLists(mMODEL4D *model, const MATRIX4X4 *transformationMatrix, mTRANSFORMATIONS transformationMethod, bool  TransformBasis)
		{
			for(int objectCount = 0; objectCount < model->ObjectsAmount; ++objectCount)
			{
				TransformPolygonRenderList(&model->ObjectList[objectCount], transformationMatrix, transformationMethod);
				// finally, test if transform should be applied to orientation basis
				// hopefully this is a rotation, otherwise the basis will get corrupted
				if(TransformBasis)
				{
					model->ObjectList[objectCount].ux *= *transformationMatrix;
					model->ObjectList[objectCount].uy *= *transformationMatrix;
					model->ObjectList[objectCount].uz *= *transformationMatrix;
				}// END OF IF
			} // END OF FOR
		} // END OF FUNCTION

		void TransformObjectToWorld(mOBJECT4D *object, mTRANSFORMATIONS transformationMethod)
		{
			mPOLYGON4D *currentPolygon;
			object->AllocateMemoryToTransformedPolygonList();
			if(transformationMethod == TRANSFORM_LOCALTOTRANS)
			{
				for(int polyCount = 0; polyCount < object->PolygonAmount; ++polyCount)
				{
					currentPolygon = &object->PolygonList[polyCount];
					if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
					{
						for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
						{
							object->TransformedPolygonList[polyCount].VertexList[x].VertexData[x] = currentPolygon->VertexList[x].VertexData[x] + object->WorldPosition;
						}
					}
					
				} // END OF FOR
			} else // ELSE TRANSFORMED ONLY
				{
					for(int polyCount = 0; polyCount < object->PolygonAmount; ++polyCount)
					{
						currentPolygon = &object->TransformedPolygonList[polyCount];
						if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
						{
							for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
							{
								currentPolygon->VertexList[x].VertexData[x] += object->WorldPosition;
							}
						}
						
					} // END OF FOR
				} // END OF ELSE
		} // END OF FUNCTION

		void TransformObjectToWorld(mOBJECT4D *object, const VECTOR4D *worldPosition, mTRANSFORMATIONS transformationMethod)
		{
			mPOLYGON4D *currentPolygon;
			object->AllocateMemoryToTransformedPolygonList();
			if(transformationMethod == TRANSFORM_LOCALTOTRANS)
			{
				for(int polyCount = 0; polyCount < object->PolygonAmount; ++polyCount)
				{
					currentPolygon = &object->PolygonList[polyCount];
					if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
					{
						for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
						{
							object->TransformedPolygonList[polyCount].VertexList[x].VertexData[x] = currentPolygon->VertexList[x].VertexData[x] + *worldPosition;
						}
					}

				} // END OF FOR
			} else // ELSE TRANSFORMED ONLY
			{
				for(int polyCount = 0; polyCount < object->PolygonAmount; ++polyCount)
				{
					currentPolygon = &object->TransformedPolygonList[polyCount];
					if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
					{
						for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
						{
							currentPolygon->VertexList[x].VertexData[x] += *worldPosition;
						}
					}

				} // END OF FOR
			} // END OF ELSE
		} // END OF FUNCTION

		void TransformObjectToWorld(mOBJECT4D *object, const MATRIX4X4 *worldPosition, mTRANSFORMATIONS transformationMethod)
		{
			mPOLYGON4D *currentPolygon;
			object->AllocateMemoryToTransformedPolygonList();
			if(transformationMethod == TRANSFORM_LOCALTOTRANS)
			{
				for(int polyCount = 0; polyCount < object->PolygonAmount; ++polyCount)
				{
					currentPolygon = &object->PolygonList[polyCount];
					if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
					{
						for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
						{
							object->TransformedPolygonList[polyCount].VertexList[x].VertexData[x] = currentPolygon->VertexList[x].VertexData[x] * *worldPosition;
						}
					}
				} // END OF FOR
			} else // ELSE TRANSFORMED ONLY
			{
				for(int polyCount = 0; polyCount < object->PolygonAmount; ++polyCount)
				{
					currentPolygon = &object->TransformedPolygonList[polyCount];
					if(currentPolygon->PolygonStates == POLY_ACTIVE || currentPolygon->PolygonStates != POLY_CLIPPED || currentPolygon->PolygonStates != POLY_BACKFACE)
					{
						for(int x = 0; x < currentPolygon->VertexList->vertexAmount; ++x)
						{
							currentPolygon->VertexList[x].VertexData[x] *= *worldPosition;
						}
					}

				} // END OF FOR
			} // END OF ELSE
		} // END OF FUNCTION

		void TransformModelToWorld(mMODEL4D *model, mTRANSFORMATIONS transformationMethod)
		{
			for(int modelCount = 0; model->ObjectsAmount; ++modelCount)
			{
				TransformObjectToWorld(&model->ObjectList[modelCount], transformationMethod);
			}
		} // END OF FUNCTION

		void TransformModelToWorld(mMODEL4D *model, const VECTOR4D *worldPosition, mTRANSFORMATIONS transformationMethod)
		{
			for(int modelCount = 0; model->ObjectsAmount; ++modelCount)
			{
				TransformObjectToWorld(&model->ObjectList[modelCount], worldPosition, transformationMethod);
			}
		} // END OF FUNCTION

		void TransformModelToWorld(mMODEL4D *model, const MATRIX4X4 *worldPosition, mTRANSFORMATIONS transformationMethod)
		{
			for(int modelCount = 0; model->ObjectsAmount; ++modelCount)
			{
				TransformObjectToWorld(&model->ObjectList[modelCount], worldPosition, transformationMethod);
			}
		}
	};
};