//
//  RandomBase.cpp
//  NatureOfCodeCocos2DX
//
//  Created by Adrian Simionescu on 08/10/14.
//
//

#include "RandomBase.h"


namespace Aurora {
    namespace Random {

        RandomBase::RandomBase()
        {
            this->RandomNumberModeValue = RandomNumberMode::Normal;
        }
        
        void RandomBase::SetConstrainsRange(Float width, Float height)
        {
			this->Width = width;
			this->Height = height;
        }
        
        void RandomBase::Constrain()
        {
			
        }
        
        void RandomBase::DoCalculations()
        {
			this->Constrain();
        }
        
        void RandomBase::Normal()
        {
            
        }
        
        void RandomBase::SetRandomNumberMode(Aurora::Random::RandomNumberMode randomNumberMode)
        {
			this->RandomNumberModeValue = randomNumberMode;
        }

		RandomBaseComplete::RandomBaseComplete() : RandomBase()
		{

		}
        
    }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora