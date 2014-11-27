#ifndef PhysicsConstants_H
#define PhysicsConstants_H

#include "../BaseClasses/PhysicsBase.h"
#include <string>

namespace Aurora
{
	
	namespace Physics
	{
		class PhysicsConstants
		{
		public:
			const static  VECTOR2D EarthGravity;
			const static float NormalSurfaceFrictionCoefficient;
			const static std::string Callbacks_NormalFrictionCalculations_FunctionName;
			const static std::string Callbacks_NormalEarthGravityCalculations_FunctionName;
		};

	};

};

#endif