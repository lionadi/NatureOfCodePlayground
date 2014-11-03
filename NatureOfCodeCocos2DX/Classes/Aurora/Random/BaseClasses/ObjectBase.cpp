#include "ObjectBase.h"

namespace Aurora {
    namespace Random {


		IObjectBaseBasic::IObjectBaseBasic() : IRandomBase()
		{
			this->init();
		}

		IObjectBaseBasic::~IObjectBaseBasic()
		{
			IRandomBase::~IRandomBase();
		}

		void IObjectBaseBasic::Render()
		{

		}

		IObjectBaseBasic& IObjectBaseBasic::operator=(const IObjectBaseBasic& value)
		{
			if(this == &value) { return(*this); }

			// Do Other initializations
			this->SetRandomNumberMode(value.GetRandomNumberMode());

			return(*this);
		}

		void IObjectBaseBasic::init()
		{
			this->SetRandomNumberMode(RandomNumberMode::Normal);
		}

		void IObjectBaseBasic::init(RandomNumberMode randomNumberMode)
		{
			this->SetRandomNumberMode(randomNumberMode);
		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora