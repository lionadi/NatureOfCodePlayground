#include "PhysicsCalculator.h"

namespace Aurora {
	namespace Physics {

		std::shared_ptr<PhysicsCalculator> PhysicsCalculator::instance = nullptr;

		void PhysicsCalculator::PerformCalculationsOnForce(Force &&value)
		{

		}

		void PhysicsCalculator::PerformCalculationsOnForce(const Force &value)
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


		std::shared_ptr<PhysicsCalculator> PhysicsCalculator::GetInstance(PhysicsCalculationMode calculationMode)
		{
			if (instance == nullptr)
			{
				switch (calculationMode)
				{
				case Aurora::Physics::PhysicsCalculationMode::Base:
					instance = std::make_shared<PhysicsCalculator>();
					break;
				case Aurora::Physics::PhysicsCalculationMode::Normal:
					instance = std::make_shared<NormalPhysicsCalculator>();
					break;
				default:
					instance = std::make_shared<PhysicsCalculator>();
					break;
				}
			}

			return instance;
		}


		void NormalPhysicsCalculator::PerformCalculationsOnForce(Force &&value)
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		void NormalPhysicsCalculator::PerformCalculationsOnForce(const Force &value)
		{
			throw std::logic_error("The method or operation is not implemented.");
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