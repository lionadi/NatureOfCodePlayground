#ifndef NatureOfCodeCocos2DX_BasePhysicsCalculator_h
#define NatureOfCodeCocos2DX_BasePhysicsCalculator_h


#include "../BaseClasses/PhysicsBase.h"
#include "Force.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {
		class PhysicsCalculator : public ICalculationsBase
		{
			protected:
			static std::shared_ptr<PhysicsCalculator> instance;
			virtual void init() override;
			std::vector<VECTOR2D> constantForces;
		public:
			PhysicsCalculator() = default;
			virtual ~PhysicsCalculator() = default;

			template<typename ConstantForce>
			void AddConstantForceToCalculator(ConstantForce &&constantForce);
			
			virtual void PerformCalculationsOnForce(Force &&value);
			virtual void PerformCalculationsOnForce(const Force &value);

			

			virtual void DoCalculations() override;

			static std::shared_ptr<PhysicsCalculator> GetInstance(PhysicsCalculationMode calculationMode);
		};

		class NormalPhysicsCalculator : public PhysicsCalculator
		{
		private:
			virtual void init() override;
		public:

			NormalPhysicsCalculator() = default;
			virtual ~NormalPhysicsCalculator() = default;

			virtual void PerformCalculationsOnForce(Force &&value) override;

			virtual void PerformCalculationsOnForce(const Force &value) override;

			

			virtual void DoCalculations() override;

		};
	};
};

#endif