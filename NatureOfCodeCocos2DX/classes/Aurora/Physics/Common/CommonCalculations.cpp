#include "CommonCalculations.h"

namespace Aurora {
	namespace Physics {
		
		

		const std::function<Aurora::Math::VECTOR2D(const Aurora::Math::VECTOR2D&, float)> CommonCalculations::NormalEarthGravityCalculations = [](const VECTOR2D &gravity, float mass)
		{
			return VECTOR2D(gravity.X, gravity.Y * mass);
		};

		const std::function < Aurora::Math::VECTOR2D(float, const Aurora::Math::VECTOR2D&, float, const Aurora::Math::VECTOR2D&, float, float, float)> CommonCalculations::GravitationalAttractionCalculations = [](float objectGraviationalAttractionConstant, const Aurora::Math::VECTOR2D& attractor, float attractorMass, const Aurora::Math::VECTOR2D& toBeAttracted, float toBeAttractedMass, float distanceMinValue, float distanceMaxValue)
		{
			VECTOR2D attractionForce = attractor.Clone() - toBeAttracted;
			float distance = attractionForce.Magnitude();
			if (distance < distanceMinValue)
				distance = distanceMinValue;
			else if (distance > distanceMaxValue)
				distance = distanceMaxValue;

			attractionForce.Normalize();
			float strength = (objectGraviationalAttractionConstant * attractorMass * toBeAttractedMass) / (distance * distance);
			attractionForce *= strength;

			return attractionForce;
		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora