#ifndef FrictionCalculations_H
#define FrictionCalculations_H

#include "CommonCalculations.h"

namespace Aurora
{

	namespace Physics
	{
		class FrictionCalculations : public ICalculationsBase
		{
		private:
			
			static std::shared_ptr<FrictionCalculations> instance;
			virtual void init() override
			{
				Calculations = std::make_shared < Global::Callbacks>();

				Calculations->add(PhysicsConstants::Callbacks_NormalFrictionCalculations_FunctionName, [](VECTOR2D velocity, float frictionCoefficient, float normal)
				{
					float frictionMagnitude = frictionCoefficient * normal;
					VECTOR2D friction = velocity.Clone();
					friction *= -1;
					friction.Normalize();
					friction *= frictionMagnitude;
					return friction;
				});
			}

		public:
			FrictionCalculations() = default;
			virtual ~FrictionCalculations() = default;
			static std::shared_ptr<FrictionCalculations> GetInstance()
			{
				if (instance == nullptr)
					instance = std::make_shared<FrictionCalculations>();

				return instance;
			}
			
		};

	};

};

#endif