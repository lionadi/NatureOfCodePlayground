#ifndef NatureOfCodeCocos2DX_EngineCommonCalculations_h
#define NatureOfCodeCocos2DX_EngineCommonCalculations_h
#include <utility> 
#include <functional>
#include "../../Errors/ErrorOperations.h"

namespace Aurora {
	namespace Engine {
		
		class EngineCommonCalculations
		{
		public:
			static inline float CalculateDeltaTime(const float &currentframe, const float &frameRateOrPeriod)
			{
				if (frameRateOrPeriod == 0)
					throw std::bad_function_call(Aurora::Errors::ErrorMessages::DivisionByZero.c_str());

				return(currentframe / frameRateOrPeriod);
			}
		};

	};
};
#endif