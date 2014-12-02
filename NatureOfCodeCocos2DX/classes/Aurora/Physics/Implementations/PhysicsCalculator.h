#ifndef NatureOfCodeCocos2DX_BasePhysicsCalculator_h
#define NatureOfCodeCocos2DX_BasePhysicsCalculator_h


#include "../Common/FrictionCalculations.h"
#include "Force.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {
		// Use Singleton?;Factory + Builder?
		class PhysicsCalculator : public ICalculationsBase
		{
			protected:
			static std::shared_ptr<PhysicsCalculator> instance;
			virtual void init() override;
			std::vector<VECTOR2D> constantForces;
			std::map<PhysicsCalculationMode, std::shared_ptr<PhysicsCalculator>> physicsCalculatorInstances;
			
		public:
			PhysicsCalculator() = default;
			virtual ~PhysicsCalculator() = default;

			template<typename ConstantForce>
			void AddConstantForceToCalculator(ConstantForce &&constantForce);
			
			virtual void PerformCalculationsOnForce(ForceAlias &value);

			

			virtual void DoCalculations() override;

			static std::shared_ptr<PhysicsCalculator> GetInstance();

			std::shared_ptr<PhysicsCalculator> GetPhysicsCalculatorOption(PhysicsCalculationMode calculationMode);
			void CreateInstanceOfPhysicsCalculatorOption(PhysicsCalculationMode calculationMode);
		};

		class NormalPhysicsCalculator : public PhysicsCalculator
		{
		private:
			virtual void init() override;
		public:

			NormalPhysicsCalculator() = default;
			virtual ~NormalPhysicsCalculator() = default;

			virtual void PerformCalculationsOnForce(ForceAlias &value) override;

			

			virtual void DoCalculations() override;

		};
	};
};

#endif