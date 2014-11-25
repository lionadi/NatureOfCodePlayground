#ifndef NatureOfCodeCocos2DX_Mover_h
#define NatureOfCodeCocos2DX_Mover_h

#include "..\BaseClasses\ObjectBase.h"
#include "..\..\Physics\PhysicsOperations.h"



namespace Aurora {
	namespace Random {

		class Mover : public RandomBaseComplete
		{

		private:
			/*mutable VECTOR2D position;
			mutable VECTOR2D velocity;
			mutable VECTOR2D acceleration;*/
			std::shared_ptr<Physics::Force> moverPhysic;
			mutable VECTOR2D target;
			mutable VECTOR3D perlinNoiseTime_PositionX;
			mutable VECTOR3D perlinNoiseTime_PositionY;

			/*Float maximiunVelocity;
			Float minimumVelocity;*/
			
			Float probalitityFactor;

			void MoveTowardsTarget();
			
			void Constrain() final;

			void UniformCalculations() final;

			void GaussianCalculations() final;

			void PerlinNoiseCalculations() final;

			void NormalCalculations();

			virtual void init() override;
			virtual void init(const Mover &value);
			virtual void init(const Mover &&value);
			virtual void init(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize, const float &mass);

		public:
			Mover();
			Mover(const mRECT &areaSize);
			Mover(const Mover &value);
			Mover& operator=(const Mover& value);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize, const float &mass);
			~Mover();
			Mover(Mover &&value);
			Mover & operator=(Mover && value);
			void DoCalculations() override;

			void SetTarget(const VECTOR2D &target);
			void SetPosition(const VECTOR2D &position);
			void SetVelocityRange(const Float moverMaximumVelocity, const Float moverMinimumVelocity);
			const VECTOR2D GetCurentPosition() const;
			const VECTOR2D GetCurentTarget() const;

			const float GetMoverMass() const;

			
			void Accelerate();
			void Decellerate();
			

			bool MoveAutomatically = true;

			

		};

		class IMover : public IObjectBaseBasic
		{
		public:
			IMover() = default;
			virtual ~IMover() = default;
			virtual void Render() override;

			//virtual void SetMoverTarget(const VECTOR2D &target);

			virtual void MoveMover();
		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif