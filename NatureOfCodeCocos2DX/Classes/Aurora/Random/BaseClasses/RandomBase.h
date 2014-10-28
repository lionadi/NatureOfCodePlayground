//
//  RandomBase.h
//  NatureOfCodeCocos2DX
//
//  Created by Adrian Simionescu on 08/10/14.
//
//

#ifndef NatureOfCodeCocos2DX_RandomBase_h
#define NatureOfCodeCocos2DX_RandomBase_h



#include "..\CommonTools.h"
#include "..\..\Math\MathOperations.h"

using namespace Aurora::Math;

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
            private:
				RandomNumberMode RandomNumberModeValue;
			protected:
				virtual void init() = 0;
            public:
				
				PRandomBase();
				virtual ~PRandomBase();
                void SetRandomNumberMode( RandomNumberMode randomNumberMode );
				RandomNumberMode GetRandomNumberMode() const;
				
        };
        
        
        class PRandomBaseBasic : virtual public PRandomBase
        {
			protected:
                mRECT areaSize;
            public:
				PRandomBaseBasic();
				virtual ~PRandomBaseBasic();
                virtual void SetConstrainsRange(const mRECT &areaSize);
				const virtual mRECT GetConstrainsRange() const;
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
			protected:
			module::Perlin PerlinNoiseCalculator;
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
		private:
			protected:
			virtual void init();
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
        public:
            RandomBase();
			RandomBase(const RandomBase &value);
			virtual ~RandomBase();

            void SetConstrainsRange(const mRECT &areaSize);
            
            void Constrain();
            
            void DoCalculations();

			RandomBase& operator=(const RandomBase& value);
		};

		class RandomBaseComplete : virtual public RandomBase, virtual public PRandomBaseComplete
		{
			private:
				
		protected:
				module::Perlin PerlinNoiseCalculator;
				virtual void init();
				virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseComplete();
			RandomBaseComplete(const RandomBaseComplete &value);
			virtual ~RandomBaseComplete();
			

			void DoCalculations();
			void Constrain();
			void NormalCalculations();
			void UniformCalculations();
			void GaussianCalculations();
			void PerlinNoiseCalculations();

			RandomBaseComplete& operator=(const RandomBaseComplete& value);

			
		};

		class RandomBasePerlinNoise : virtual public RandomBase, virtual public PRandomBasePerlinNoise
		{

		private:
			
		protected:
			module::Perlin PerlinNoiseCalculator;
			virtual void init();
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			
			
			RandomBasePerlinNoise();
			RandomBasePerlinNoise(const RandomBasePerlinNoise &value);
			virtual ~RandomBasePerlinNoise();
			void DoCalculations();
			void PerlinNoiseCalculations();

			RandomBasePerlinNoise& operator=(const RandomBasePerlinNoise& value);
		};

		class RandomBaseGaussian : virtual public RandomBase, virtual public PRandomBaseGaussian
		{
		private:

		protected:
			virtual void init();
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseGaussian();
			RandomBaseGaussian(const RandomBaseGaussian &value);
			virtual ~RandomBaseGaussian();
			void DoCalculations();
			void GaussianCalculations();

			RandomBaseGaussian& operator=(const RandomBaseGaussian& value);
		};

		class RandomBaseUniform : virtual public RandomBase, virtual public PRandomBaseUniform
		{
		private:

		protected:
			virtual void init();
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseUniform();
			RandomBaseUniform(const RandomBaseUniform &value);
			virtual ~RandomBaseUniform();
			void DoCalculations();
			void UniformCalculations();

			RandomBaseUniform& operator=(const RandomBaseUniform& value);
		};

		class RandomBaseNormal : virtual public RandomBase, virtual public PRandomBaseNormal
		{
		private:
		protected:
			virtual void init();
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseNormal();
			RandomBaseNormal(const RandomBaseNormal &value);
			virtual ~RandomBaseNormal();
			void DoCalculations();
			void NormalCalculations();

			RandomBaseNormal& operator=(const RandomBaseNormal& value);
		};
        
    }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif
