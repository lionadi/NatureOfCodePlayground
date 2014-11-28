#ifndef FrictionCalculations_H
#define FrictionCalculations_H

#include "CommonCalculations.h"

using namespace Aurora::Math;
namespace Aurora
{

	namespace Physics
	{
		class FrictionCalculations 
		{

		public:
			const static std::function<VECTOR2D(const VECTOR2D&, float, float)> NormalFrictionCalculations;
			
			
		};

	};

};

#endif