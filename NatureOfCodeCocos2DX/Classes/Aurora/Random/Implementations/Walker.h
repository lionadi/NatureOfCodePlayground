#ifndef NatureOfCodeCocos2DX_Walker_h
#define NatureOfCodeCocos2DX_Walker_h

#include "..\BaseClasses\ObjectBase.h"
#include "..\..\Math\MathOperations.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Random {

		class Walker : virtual public RandomBaseComplete
		{

		private:
			VECTOR2D position;
			VECTOR2D target;
			VECTOR3D perlinNoiseTime_PositionX;
			VECTOR3D perlinNoiseTime_PositionY;
			Float probalitityFactor;

			void MoveWalkerTowardsTarget();
			
			void Constrain();

			void UniformCalculations();

			void GaussianCalculations();

			void PerlinNoiseCalculations();

			void NormalCalculations();

		public:
			Walker();
			Walker(const mRECT &areaSize);
			Walker(const mRECT &areaSize, const VECTOR2D &walkerStartPosition);
			~Walker();

			void SetTarget(VECTOR2D target);
			VECTOR2D GetCurentPosition();
			void SetPosition(const VECTOR2D &position);
			virtual void SetProbalitiyFactor(Float probalitityFactor);

		};

		class PWalker : virtual public PObjectBaseBasic
		{
		
		public:
			Walker WalkerObject;
			PWalker();
			PWalker(const mRECT &areaSize);
			virtual ~PWalker();
			void Render();

			

			virtual void SetRandomNumberMode(RandomNumberMode randomNumberMode);
			virtual void RenderWalkerByPosition(const VECTOR2D &position) = 0;
			virtual void SetWalkerTarget(const VECTOR2D &target);
			virtual void StepWalker() = 0;
			virtual void StepWalkerByTarget(const VECTOR2D &target) = 0;
		};

		

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif