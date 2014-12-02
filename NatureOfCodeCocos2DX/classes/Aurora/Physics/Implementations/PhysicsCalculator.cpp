#include "PhysicsCalculator.h"

namespace Aurora {
	namespace Physics {

		std::shared_ptr<PhysicsCalculator> PhysicsCalculator::instance = nullptr;

		void PhysicsCalculator::PerformCalculationsOnForce(ForceAlias &value)
		{

		}

		void PhysicsCalculator::init()
		{

		}

		void PhysicsCalculator::DoCalculations()
		{

		}


		template<typename ConstantForce>
		void Aurora::Physics::PhysicsCalculator::AddConstantForceToCalculator(ConstantForce &&constantForce)
		{
			this->constantForces.push_back(std::forward<VECTOR2D>(constantForce));
		}


		std::shared_ptr<PhysicsCalculator> PhysicsCalculator::GetInstance()
		{
			if (instance == nullptr)
			{
				instance = std::make_shared<PhysicsCalculator>();
			}
			/**/
			return instance;
		}

		void PhysicsCalculator::CreateInstanceOfPhysicsCalculatorOption(PhysicsCalculationMode calculationMode)
		{
			//this->_callbacks.emplace(name, std::make_shared<Callback>());
			std::string enumName = "";
			switch (calculationMode)
			{
			case Aurora::Physics::PhysicsCalculationMode::Base:
				this->physicsCalculatorInstances.emplace(calculationMode, std::make_shared<PhysicsCalculator>());
				enumName = "Base";
				break;
			case Aurora::Physics::PhysicsCalculationMode::Normal:
				this->physicsCalculatorInstances.emplace(calculationMode, std::make_shared<NormalPhysicsCalculator>());
				enumName = "Normal";
				break;
			default:
				if (this->physicsCalculatorInstances.find(calculationMode) != this->physicsCalculatorInstances.end()) {
					CCLOG("The Physics calculator instance already exists: %s", enumName);
				} 
				break;
			}
		}

		std::shared_ptr<PhysicsCalculator> PhysicsCalculator::GetPhysicsCalculatorOption(PhysicsCalculationMode calculationMode)
		{
			std::shared_ptr<PhysicsCalculator> calculator = nullptr;
			
			if (this->physicsCalculatorInstances.find(calculationMode) == this->physicsCalculatorInstances.end())
			{
				this->CreateInstanceOfPhysicsCalculatorOption(calculationMode);	
			}
			
			return this->physicsCalculatorInstances.at(calculationMode);
		}

		void NormalPhysicsCalculator::PerformCalculationsOnForce(ForceAlias &value)
		{
			PhysicsCalculator::PerformCalculationsOnForce(value);
			VECTOR2D gravityForce = CommonCalculations::NormalEarthGravityCalculations(PhysicsConstants::EarthGravity, value->Mass());
			VECTOR2D frictionForce = FrictionCalculations::NormalFrictionCalculations(value->Velocity(), PhysicsConstants::NormalSurfaceFrictionCoefficient, value->Normal());
			/*VECTOR2D gravityForce = cc->Calculations->call(PhysicsConstants::Callbacks_NormalEarthGravityCalculations_FunctionName, VECTOR2D::GetZeroVector(), PhysicsConstants::EarthGravity, this->moverPhysic->Mass());
			VECTOR2D friction = VECTOR2D::GetZeroVector();
			VECTOR2D gravityForce2 = cc->Calculations->call(PhysicsConstants::Callbacks_NormalEarthGravityCalculations_FunctionName, VECTOR2D::GetZeroVector(), friction, this->moverPhysic->Mass());*/
			//VECTOR2D gravityForce2 = cc->Calculations->call(PhysicsConstants::Callbacks_NormalEarthGravityCalculations_FunctionName, PhysicsConstants::EarthGravity, this->moverPhysic->Mass());

			// TO BE REMOVED TEST PURPOSES: Adds gravity simulation, NOTICE the mass multiplication to simulate gravity
			value->ApplyForce(frictionForce);
			value->ApplyForce(VECTOR2D(0.01f, 0));
			value->ApplyForce(gravityForce);
		}

		void NormalPhysicsCalculator::init()
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		void NormalPhysicsCalculator::DoCalculations()
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

	};
};