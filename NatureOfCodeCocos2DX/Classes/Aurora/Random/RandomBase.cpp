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
		//-------------------------------------------------------------------------
		// START = Random Base Interfaces
		//-------------------------------------------------------------------------
		PRandomBase::PRandomBase()
		{

		}
		
		PRandomBase::~PRandomBase()
		{

		}

		PRandomBaseBasic::PRandomBaseBasic() : PRandomBase()
		{

		}

		PRandomBaseBasic::~PRandomBaseBasic()
		{
			PRandomBase::~PRandomBase();
		}

		PRandomBaseNormal::PRandomBaseNormal() : PRandomBaseBasic()
		{

		}

		PRandomBaseNormal::~PRandomBaseNormal()
		{
			PRandomBaseBasic::~PRandomBaseBasic();
		}

		PRandomBaseUniform::PRandomBaseUniform() : PRandomBaseBasic()
		{

		}

		PRandomBaseUniform::~PRandomBaseUniform()
		{
			PRandomBaseBasic::~PRandomBaseBasic();
		}

		PRandomBaseGaussian::PRandomBaseGaussian() : PRandomBaseBasic()
		{

		}

		PRandomBaseGaussian::~PRandomBaseGaussian()
		{
			PRandomBaseBasic::~PRandomBaseBasic();
		}

		PRandomBasePerlinNoise::PRandomBasePerlinNoise() : PRandomBaseBasic()
		{

		}

		PRandomBasePerlinNoise::~PRandomBasePerlinNoise()
		{
			PRandomBaseBasic::~PRandomBaseBasic();
		}

		PRandomBaseComplete::PRandomBaseComplete() : PRandomBaseUniform(), PRandomBaseGaussian(), PRandomBasePerlinNoise()
		{
			
		}

		PRandomBaseComplete::~PRandomBaseComplete()
		{
			PRandomBaseUniform::~PRandomBaseUniform();
			PRandomBaseGaussian::~PRandomBaseGaussian();
			PRandomBasePerlinNoise::~PRandomBasePerlinNoise();
		}

		//-------------------------------------------------------------------------
		// END = Random Base Interfaces
		//-----------------------------------------------------------------------

        RandomBase::RandomBase() : PRandomBaseBasic()
        {
            this->RandomNumberModeValue = RandomNumberMode::Normal;
        }

		RandomBase::~RandomBase()
		{
			PRandomBaseBasic::~PRandomBaseBasic();
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
        
        void RandomBase::SetRandomNumberMode(Aurora::Random::RandomNumberMode randomNumberMode)
        {
			this->RandomNumberModeValue = randomNumberMode;
        }

		

		RandomBaseComplete::RandomBaseComplete() : RandomBase()
		{

		}

		RandomBaseComplete::~RandomBaseComplete()
		{
			RandomBase::~RandomBase();
			PRandomBaseComplete::~PRandomBaseComplete();
		}

		void RandomBaseComplete::DoCalculations()
		{
			RandomBase::DoCalculations();

			switch(this->RandomNumberModeValue)
            {
			case RandomNumberMode::Normal:
				{
					this->NormalCalculations();
				} break;

			case RandomNumberMode::Uniform:
				{
					this->UniformCalculations();
				} break;


			case RandomNumberMode::Gaussian:
				{
					this->GaussianCalculations();
				} break;

			case RandomNumberMode::Perlin:
				{
					this->PerlinNoiseCalculations();
				} break;

			default:
				{
					this->NormalCalculations();
				} break;
			}
  
        
			this->Constrain();
		}

		void RandomBaseComplete::Constrain()
		{
			RandomBase::Constrain();

		}

		void RandomBaseComplete::NormalCalculations()
		{
			
		}

		void RandomBaseComplete::UniformCalculations()
		{

		}

		void RandomBaseComplete::GaussianCalculations()
		{

		}

		void RandomBaseComplete::PerlinNoiseCalculations()
		{

		}

		RandomBasePerlinNoise::RandomBasePerlinNoise() : RandomBase()
		{

		}

		RandomBasePerlinNoise::~RandomBasePerlinNoise()
		{
			RandomBase::~RandomBase();
			PRandomBasePerlinNoise::~PRandomBasePerlinNoise();
		}

		void RandomBasePerlinNoise::DoCalculations()
		{
			RandomBase::DoCalculations();
			this->PerlinNoiseCalculations();
		}

		void RandomBasePerlinNoise::PerlinNoiseCalculations()
		{

		}

		RandomBaseGaussian::RandomBaseGaussian() : RandomBase()
		{

		}

		RandomBaseGaussian::~RandomBaseGaussian()
		{
			RandomBase::~RandomBase();
			PRandomBaseGaussian::~PRandomBaseGaussian();
		}

		void RandomBaseGaussian::DoCalculations()
		{
			RandomBase::DoCalculations();
			this->GaussianCalculations();
		}

		void RandomBaseGaussian::GaussianCalculations()
		{

		}

		RandomBaseUniform::RandomBaseUniform() : RandomBase()
		{

		}

		RandomBaseUniform::~RandomBaseUniform()
		{
			RandomBase::~RandomBase();
			PRandomBaseUniform::~PRandomBaseUniform();
		}

		void RandomBaseUniform::DoCalculations()
		{
			RandomBase::DoCalculations();
			this->UniformCalculations();
		}

		void RandomBaseUniform::UniformCalculations()
		{

		}

		RandomBaseNormal::RandomBaseNormal() : RandomBase()
		{

		}

		RandomBaseNormal::~RandomBaseNormal()
		{
			RandomBase::~RandomBase();
			PRandomBaseNormal::~PRandomBaseNormal();
		}

		void RandomBaseNormal::DoCalculations()
		{
			RandomBase::DoCalculations();
			this->NormalCalculations();
		}

		void RandomBaseNormal::NormalCalculations()
		{

		}
        
    }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora