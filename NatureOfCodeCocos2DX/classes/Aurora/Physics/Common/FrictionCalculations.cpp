#include "FrictionCalculations.h"

namespace Aurora
{

	namespace Physics
	{
		const  std::function<VECTOR2D(const VECTOR2D&, float, float)> FrictionCalculations::NormalFrictionCalculations = [](const VECTOR2D& velocity, float frictionCoefficient, float normal)
		{
			float frictionMagnitude = frictionCoefficient * normal;
			VECTOR2D friction = velocity.Clone();
			friction *= -1;
			friction.Normalize();
			friction *= frictionMagnitude;
			return friction;
		};
	};
};