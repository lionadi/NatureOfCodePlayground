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

			virtual void init();
			virtual void init(const Walker &value);
			virtual void init(const mRECT &areaSize, const VECTOR2D &walkerStartPosition);

		public:
			Walker();
			Walker(const mRECT &areaSize);
			Walker(const Walker &value);
			Walker(const mRECT &areaSize, const VECTOR2D &walkerStartPosition);
			~Walker();

			void SetTarget(const VECTOR2D &target);
			const VECTOR2D GetCurentPosition() const;
			void SetPosition(const VECTOR2D &position);
			void SetProbalitiyFactor(Float probalitityFactor);

			Walker& operator=(const Walker& value);

		};

		class PWalker : virtual public PObjectBaseBasic
		{
		private:
			virtual void init();
			virtual void init(const mRECT &areaSize);
			virtual void init(const PWalker &value);
		public:
			Walker WalkerObject;
			PWalker();
			PWalker(const PWalker &value);
			PWalker(const mRECT &areaSize);
			virtual ~PWalker();
			virtual void Render();

			

			virtual void SetRandomNumberMode(RandomNumberMode randomNumberMode);
			virtual void RenderWalkerByPosition(const VECTOR2D &position);
			virtual void SetWalkerTarget(const VECTOR2D &target);
			virtual void StepWalker();

			PWalker& operator=(const PWalker& value);

			

			//virtual void StepWalkerByTarget(const VECTOR2D &target) = 0;
		};

		

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif