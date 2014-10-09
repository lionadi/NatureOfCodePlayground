//
//  RandomBase.h
//  NatureOfCodeCocos2DX
//
//  Created by Adrian Simionescu on 08/10/14.
//
//

#ifndef NatureOfCodeCocos2DX_RandomBase_h
#define NatureOfCodeCocos2DX_RandomBase_h

#include "..\Globals\GlobalDatatypes.h"

using namespace Aurora::DataTypes;

namespace Aurora {
    namespace Random {
     
        enum RandomNumberMode
        {
            Normal, Uniform, Gaussian, Perlin
        };
        
        class PRandomBase
        {
            protected:
                RandomNumberMode RandomNumberModeValue;
            public:
                virtual void SetRandomNumberMode( RandomNumberMode randomNumberMode ) = 0;
        };
        
        
        class PRandomBaseBasic : public PRandomBase
        {
            protected:
                Float Width;
                Float Height;
            public:
                virtual void SetConstrainsRange( Float width, Float height) = 0;
                virtual void DoCalculations() = 0;
                virtual void Constrain() = 0;
                virtual void Normal() = 0;
        };
        
        
        class PRandomBaseUniform : PRandomBaseBasic
        {
            public:
                virtual void UniformCalculations() = 0;
        };
        
        class PRandomBaseGaussian : PRandomBaseBasic
        {
            public:
                virtual void GaussianCalculations() = 0;
        };
        
        class PRandomBasePerlinNoise : PRandomBaseBasic
        {
            //TODO: IMPLEMENT AND USE PERLIN NOISE
            //var PerlinNoiseCalculator : PerlinNoise { get set };
            public:
                virtual void PerlinNoiseCalculations() = 0;
        };
        
        class PRandomBaseComplete : PRandomBaseUniform, PRandomBaseGaussian, PRandomBasePerlinNoise
        {
            
        };
        
        class RandomBase : public PRandomBaseBasic
        {
        public:
            RandomBase();
            
            void SetRandomNumberMode(RandomNumberMode randomNumberMode);

            void SetConstrainsRange( Float width, Float height);
            
            void Constrain();
            
            void DoCalculations();
            
            void Normal();
        };

		class RandomBaseComplete : public RandomBase, public PRandomBaseComplete
		{
		public:
			RandomBaseComplete();
			// TODO: PERLIN NOISE
			//var PerlinNoiseCalculator : PerlinNoise = PerlinNoise(seed: 10);
    /*
			void DoCalculations()
    {
        
        switch(self.RandomNumberModeValue)
            {
        case .Uniform:
            self.UniformCalculations();
            
        case .Gaussian:
            self.GaussianCalculations();
        case .Perlin:
            self.PerlinNoiseCalculations();
        case .Normal:
            self.Normal();
        default:
            self.UniformCalculations();
        }
        
        self.Constrain();
    }
    
    override func Constrain()
    {
        super.Constrain();
    }
    
    override func Normal()
    {
        
    }
    
    func UniformCalculations()
    {
        
    }
    
    func GaussianCalculations()
    {
        
    }
    
    func PerlinNoiseCalculations()
    {
    }*/
		};
        
    }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif
