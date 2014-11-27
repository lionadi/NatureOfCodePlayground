#include "CommonCalculations.h"

namespace Aurora {
	namespace Physics {
		
		std::shared_ptr<CommonCalculations> CommonCalculations::instance = nullptr;

		CommonCalculations::CommonCalculations()
		{
			this->init();
		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora