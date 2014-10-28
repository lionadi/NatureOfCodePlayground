#include "ObjectBase.h"

namespace Aurora {
    namespace Random {


		PObjectBaseBasic::PObjectBaseBasic() : PRandomBase()
		{
			this->init();
		}

		PObjectBaseBasic::~PObjectBaseBasic()
		{
			PRandomBase::~PRandomBase();
		}

		void PObjectBaseBasic::Render()
		{

		}

		PObjectBaseBasic& PObjectBaseBasic::operator=(const PObjectBaseBasic& value)
		{
			if(this == &value) { return(*this); }

			// Do Other initializations
			this->SetRandomNumberMode(value.GetRandomNumberMode());

			return(*this);
		}

		void PObjectBaseBasic::init()
		{
			this->SetRandomNumberMode(RandomNumberMode::Normal);
		}

		void PObjectBaseBasic::init(RandomNumberMode randomNumberMode)
		{
			this->SetRandomNumberMode(randomNumberMode);
		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora