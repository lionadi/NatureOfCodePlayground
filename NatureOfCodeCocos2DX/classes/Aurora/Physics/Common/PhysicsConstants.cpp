#include "PhysicsConstants.h"


namespace Aurora
{

	namespace Physics
	{
		const VECTOR2D PhysicsConstants::EarthGravity = VECTOR2D{ 0, 0.1f };
		const float PhysicsConstants::NormalSurfaceFrictionCoefficient = 0.01f;
		const std::string PhysicsConstants::Callbacks_NormalFrictionCalculations_FunctionName = "NormalFrictionCalculations";
		const std::string PhysicsConstants::Callbacks_NormalEarthGravityCalculations_FunctionName = "NormalEarthGravityCalculations";
		

	};

};
