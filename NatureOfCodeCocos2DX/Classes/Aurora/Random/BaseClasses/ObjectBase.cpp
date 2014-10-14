#include "ObjectBase.h"

namespace Aurora {
    namespace Random {


		PObjectBaseBasic::PObjectBaseBasic() : PRandomBase()
		{
			this->RandomNumberModeValue = RandomNumberMode::Normal;
		}

		PObjectBaseBasic::~PObjectBaseBasic()
		{
			PRandomBase::~PRandomBase();
		}

		void PObjectBaseBasic::Render()
		{

		}

		void PObjectBaseBasic::SetRandomNumberMode(RandomNumberMode randomNumberMode)
		{
			this->RandomNumberModeValue = randomNumberMode;
		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora