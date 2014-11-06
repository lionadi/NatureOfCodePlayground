#ifndef NatureOfCodeCocos2DX_Walker_h
#define NatureOfCodeCocos2DX_Walker_h

#include "..\BaseClasses\ObjectBase.h"
#include "..\..\Math\MathOperations.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Random {

		class Walker : public RandomBaseComplete
		{

		private:
			VECTOR2D position;
			VECTOR2D target;
			VECTOR3D perlinNoiseTime_PositionX;
			VECTOR3D perlinNoiseTime_PositionY;
			Float probalitityFactor;

			void MoveWalkerTowardsTarget();
			
			void Constrain() override;

			void UniformCalculations() override;

			void GaussianCalculations() override;

			void PerlinNoiseCalculations() override;

			void NormalCalculations() override;

			virtual void init() override;
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

		class IWalker : public IObjectBaseBasic
		{
		private:
			virtual void init() override;
			virtual void init(const mRECT &areaSize);
			virtual void init(const IWalker &value);
		public:
			Walker WalkerObject;
			IWalker();
			IWalker(const IWalker &value);
			IWalker(const mRECT &areaSize);
			virtual ~IWalker();
			virtual void Render() override;

			

			//virtual void SetRandomNumberMode(RandomNumberMode randomNumberMode);
			virtual void RenderWalkerByPosition(const VECTOR2D &position);
			virtual void SetWalkerTarget(const VECTOR2D &target);
			virtual void StepWalker();

			IWalker& operator=(const IWalker& value);

			

			//virtual void StepWalkerByTarget(const VECTOR2D &target) = 0;
		};

		

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif