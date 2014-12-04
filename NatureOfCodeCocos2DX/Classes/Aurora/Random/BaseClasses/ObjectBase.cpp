#include "ObjectBase.h"

namespace Aurora {
    namespace Random {


		/*IObjectBaseBasic::IObjectBaseBasic() : IRandomBase()
		{
			this->init();
		}

		IObjectBaseBasic::IObjectBaseBasic(IObjectBaseBasic &&value) : IRandomBase(std::move(value))
		{

		}

		IObjectBaseBasic::~IObjectBaseBasic()
		{
			IRandomBase::~IRandomBase();
		}*/

		void IObjectBaseBasic::Render()
		{

		}

		void IObjectBaseBasic::init()
		{
			
		}

		//IObjectBaseBasic& IObjectBaseBasic::operator=(const IObjectBaseBasic& value)
		//{
		//	if(this == &value) { return(*this); }

		//	// Do Other initializations
		//	this->SetRandomNumberMode(value.GetRandomNumberMode());

		//	return(*this);
		//}

		//IObjectBaseBasic & IObjectBaseBasic::operator=(IObjectBaseBasic && value)
		//{
		//	IRandomBase::operator=(std::forward<IRandomBase>(value));
		//	return(*this);
		//}

		//void IObjectBaseBasic::init()
		//{
		//	this->SetRandomNumberMode(RandomNumberMode::Normal);
		//}

		//void IObjectBaseBasic::init(RandomNumberMode randomNumberMode)
		//{
		//	this->SetRandomNumberMode(randomNumberMode);
		//}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora