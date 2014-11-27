#ifndef NatureOfCodeCocos2DX_CommonCalculations_h
#define NatureOfCodeCocos2DX_CommonCalculations_h



#include "PhysicsConstants.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {

		/*std::function<VECTOR2D(VECTOR2D, float, float)> FrictionCalculations = [](VECTOR2D velocity, float frictionCoefficient, float normal)
		{
			float frictionMagnitude = frictionCoefficient * normal;
			VECTOR2D friction = velocity.Clone();
			friction *= -1;
			friction.Normalize();
			friction *= frictionMagnitude;
			return friction;
		};*/

		class CommonCalculations : public ICalculationsBase
		{
		private:
			
			static std::shared_ptr<CommonCalculations> instance;
			virtual void init() override
			{
				Calculations = std::make_shared < Global::Callbacks>();

				Calculations->add(PhysicsConstants::Callbacks_NormalEarthGravityCalculations_FunctionName, [](VECTOR2D gravity, float mass)
				{
					return VECTOR2D(gravity.X, gravity.Y * mass);
				});
			}

		public:
			CommonCalculations();
			virtual ~CommonCalculations() = default;
			static std::shared_ptr<CommonCalculations> GetInstance()
			{
				if (instance == nullptr)
				{
					instance = std::make_shared<CommonCalculations>();
				}

				return instance;
			}

		};
	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif