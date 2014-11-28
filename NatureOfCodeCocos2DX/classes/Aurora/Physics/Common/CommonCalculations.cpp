#include "CommonCalculations.h"

namespace Aurora {
	namespace Physics {
		
		

		const std::function<Aurora::Math::VECTOR2D(const Aurora::Math::VECTOR2D&, float)> CommonCalculations::NormalEarthGravityCalculations = [](const VECTOR2D &gravity, float mass)
		{
			return VECTOR2D(gravity.X, gravity.Y * mass);
		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora