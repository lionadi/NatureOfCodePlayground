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
		//-------------------------------------------------------------------------
		// START = Random Base Interfaces
		//-----------------------------------------------------------------------
        enum RandomNumberMode
        {
            Normal, Uniform, Gaussian, Perlin
        };
        
        class PRandomBase
        {
            protected:
                RandomNumberMode RandomNumberModeValue;
            public:
				PRandomBase();
				virtual ~PRandomBase();
                virtual void SetRandomNumberMode( RandomNumberMode randomNumberMode ) = 0;
        };
        
        
        class PRandomBaseBasic : virtual public PRandomBase
        {
            protected:
                Float Width;
                Float Height;
            public:
				PRandomBaseBasic();
				virtual ~PRandomBaseBasic();
                virtual void SetConstrainsRange( Float width, Float height) = 0;
                virtual void DoCalculations() = 0;
                virtual void Constrain() = 0;
        };
        
		class PRandomBaseNormal : virtual public PRandomBaseBasic
        {
            public:
				PRandomBaseNormal();
				virtual ~PRandomBaseNormal();
                virtual void NormalCalculations() = 0;
        };
        
        class PRandomBaseUniform : virtual public PRandomBaseBasic
        {
            public:
				PRandomBaseUniform();
				virtual ~PRandomBaseUniform();
                virtual void UniformCalculations() = 0;
        };
        
        class PRandomBaseGaussian : virtual public PRandomBaseBasic
        {
            public:
				PRandomBaseGaussian();
				virtual ~PRandomBaseGaussian();
                virtual void GaussianCalculations() = 0;
        };
        
        class PRandomBasePerlinNoise : virtual public PRandomBaseBasic
        {
            //TODO: IMPLEMENT AND USE PERLIN NOISE
            //var PerlinNoiseCalculator : PerlinNoise { get set };
            public:
				PRandomBasePerlinNoise();
				virtual ~PRandomBasePerlinNoise();
                virtual void PerlinNoiseCalculations() = 0;
        };
        
        class PRandomBaseComplete : virtual public PRandomBaseUniform, virtual public PRandomBaseGaussian, virtual public PRandomBasePerlinNoise, virtual public PRandomBaseNormal
        {
		public:
			PRandomBaseComplete();
            virtual ~PRandomBaseComplete();
        };

		//-------------------------------------------------------------------------
		// END = Random Base Interfaces
		//-----------------------------------------------------------------------
        
        class RandomBase : virtual public PRandomBaseBasic
        {
        public:
            RandomBase();
			virtual ~RandomBase();
            
            void SetRandomNumberMode(RandomNumberMode randomNumberMode);

            void SetConstrainsRange( Float width, Float height);
            
            void Constrain();
            
            void DoCalculations();
        };

		class RandomBaseComplete : virtual public RandomBase, virtual public PRandomBaseComplete
		{
		private:
			// TODO: PERLIN NOISE
			//var PerlinNoiseCalculator : PerlinNoise = PerlinNoise(seed: 10);
		public:
			RandomBaseComplete();
			virtual ~RandomBaseComplete();
			void DoCalculations();
			void Constrain();
			void NormalCalculations();
			void UniformCalculations();
			void GaussianCalculations();
			void PerlinNoiseCalculations();
		};

		class RandomBasePerlinNoise : virtual public RandomBase, virtual public PRandomBasePerlinNoise
		{
		public:
			// TODO: PERLIN NOISE
			//var PerlinNoiseCalculator : PerlinNoise = PerlinNoise(seed: 10);
			RandomBasePerlinNoise();
			virtual ~RandomBasePerlinNoise();
			void DoCalculations();
			void PerlinNoiseCalculations();
		};

		class RandomBaseGaussian : virtual public RandomBase, virtual public PRandomBaseGaussian
		{
		public:
			RandomBaseGaussian();
			virtual ~RandomBaseGaussian();
			void DoCalculations();
			void GaussianCalculations();
		};

		class RandomBaseUniform : virtual public RandomBase, virtual public PRandomBaseUniform
		{
		public:
			RandomBaseUniform();
			virtual ~RandomBaseUniform();
			void DoCalculations();
			void UniformCalculations();
		};

		class RandomBaseNormal : virtual public RandomBase, virtual public PRandomBaseNormal
		{
		public:
			RandomBaseNormal();
			virtual ~RandomBaseNormal();
			void DoCalculations();
			void NormalCalculations();
		};
        
    }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif
