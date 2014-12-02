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

		const std::function < VECTOR2D(const VECTOR2D&, float)> FrictionCalculations::SimplifiedDragForceCalculations = [](const VECTOR2D& velocity, float coefficientDrag)
		{
			float speed = velocity.Magnitude();
			float dragMagnitude = coefficientDrag * speed * speed;

			VECTOR2D drag = velocity.Clone();
			drag *= -1;
			drag *= dragMagnitude;
			return(drag);
		};
	};
};