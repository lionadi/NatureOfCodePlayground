#ifndef NatureOfCodeCocos2DX_Walker_h
#define NatureOfCodeCocos2DX_Walker_h

#include "..\BaseClasses\ObjectBase.h"
#include "..\..\Math\MathOperations.h"
#include "..\..\Physics\PhysicsOperations.h"

using namespace Aurora::Math;
using namespace Aurora::Physics;

namespace Aurora {
	namespace Random {

		class Walker : public RandomBaseComplete, public IPhysicsImplementor
		{

		private:
			VECTOR2D position;
			VECTOR2D target;
			VECTOR3D perlinNoiseTime_PositionX;
			VECTOR3D perlinNoiseTime_PositionY;
			Float probalitityFactor;

			void MoveWalkerTowardsTarget();
			
			void Constrain() final;

			void UniformCalculations() final;

			void GaussianCalculations() final;

			void PerlinNoiseCalculations() final;

			void NormalCalculations() final;

			virtual void init() override;
			virtual void init(const Walker &value);
			virtual void init(const mRECT &areaSize, const VECTOR2D &walkerStartPosition);

		public:
			Walker();
			Walker(const mRECT &areaSize);
			Walker(const Walker &value);
			Walker(const mRECT &areaSize, const VECTOR2D &walkerStartPosition);
			~Walker();
			Walker(Walker &&value);
			Walker & operator=(Walker && value);
			Walker& operator=(const Walker& value);

			void SetTarget(const VECTOR2D &target);
			const VECTOR2D GetCurentPosition() const;
			void SetPosition(const VECTOR2D &position);
			void SetProbalitiyFactor(Float probalitityFactor);

			

		};

		class IWalkerImplementor : public IObjectBaseBasic, public IPhysicsAccessPoint
		{
		private:
			/*virtual void init() override;
			virtual void init(const mRECT &areaSize) = 0;
			virtual void init(const IWalker &value) = 0;*/
		public:
			//std::shared_ptr<Walker> WalkerObject = 0;
			IWalkerImplementor() = default;
			/*IWalker(const IWalker &value);
			IWalker(const mRECT &areaSize);*/
			virtual ~IWalkerImplementor() = default;
			/*IWalker(IWalker &&value);
			IWalker & operator=(IWalker && value);
			IWalker& operator=(const IWalker& value);*/
			virtual void Render() override;

			

			virtual void SetWalkerRandomNumberMode(RandomNumberMode randomNumberMode);
			virtual void RenderWalkerByPosition(const VECTOR2D &position);
			virtual void SetWalkerTarget(const VECTOR2D &target);
			virtual void StepWalker();

			virtual std::shared_ptr<Physics::Force> AccessObjectPhysics() const override;

			

			

			//virtual void StepWalkerByTarget(const VECTOR2D &target) = 0;
		};

		

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif