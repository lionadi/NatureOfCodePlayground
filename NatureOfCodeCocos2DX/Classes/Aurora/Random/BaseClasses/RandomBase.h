//
//  RandomBase.h
//  NatureOfCodeCocos2DX
//
//  Created by Adrian Simionescu on 08/10/14.
//
//

#ifndef NatureOfCodeCocos2DX_RandomBase_h
#define NatureOfCodeCocos2DX_RandomBase_h


// TODO: REMOVE THE Virtual inheritance
#include "..\CommonTools.h"
#include "..\..\Math\MathOperations.h"

using namespace Aurora::Math;

namespace Aurora {
    namespace Random {
		//-------------------------------------------------------------------------
		// START = Random Base Interfaces
		//-----------------------------------------------------------------------
        enum class RandomNumberMode
        {
            Normal, Uniform, Gaussian, Perlin
        };
        
        class IRandomBase
        {
            private:
				RandomNumberMode RandomNumberModeValue;
			protected:
				virtual void init() = 0;
            public:
				
				IRandomBase();
				virtual ~IRandomBase();
                void SetRandomNumberMode( RandomNumberMode randomNumberMode );
				RandomNumberMode GetRandomNumberMode() const;
				
        };
        
        
        class IRandomBaseBasic : public IRandomBase
        {
			protected:
                mRECT areaSize;
            public:
				IRandomBaseBasic();
				virtual ~IRandomBaseBasic();
                void SetConstrainsRange(const mRECT &areaSize);
				const mRECT GetConstrainsRange() const;
                virtual void DoCalculations() = 0;
                virtual void Constrain() = 0;
        };
        
		class IRandomBaseNormal //: virtual public IRandomBaseBasic
        {
            public:
				IRandomBaseNormal();
				virtual ~IRandomBaseNormal();
                virtual void NormalCalculations() = 0;
        };
        
        class IRandomBaseUniform //: virtual public IRandomBaseBasic
        {
            public:
				IRandomBaseUniform();
				virtual ~IRandomBaseUniform();
                virtual void UniformCalculations() = 0;
        };
        
        class IRandomBaseGaussian //: virtual public IRandomBaseBasic
        {
            public:
				IRandomBaseGaussian();
				virtual ~IRandomBaseGaussian();
                virtual void GaussianCalculations() = 0;
        };
        
        class IRandomBasePerlinNoise //: virtual public IRandomBaseBasic
        {
            //TODO: IMPLEMENT AND USE PERLIN NOISE
            //var PerlinNoiseCalculator : PerlinNoise { get set };
			protected:
			module::Perlin PerlinNoiseCalculator;
            public:
				
				IRandomBasePerlinNoise();
				virtual ~IRandomBasePerlinNoise();
                virtual void PerlinNoiseCalculations() = 0;
        };
        
        class IRandomBaseComplete : virtual public IRandomBaseUniform, virtual public IRandomBaseGaussian, virtual public IRandomBasePerlinNoise, virtual public IRandomBaseNormal
        {
		public:
			IRandomBaseComplete();
            virtual ~IRandomBaseComplete();
        };

		//-------------------------------------------------------------------------
		// END = Random Base Interfaces
		//-----------------------------------------------------------------------
        
        class RandomBase : public IRandomBaseBasic
        {
		private:
			protected:
			virtual void init();
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
        public:
            RandomBase();
			RandomBase(const RandomBase &value);
			virtual ~RandomBase();
            
            void Constrain() override;
            
            void DoCalculations() override;

			RandomBase& operator=(const RandomBase& value);
		};

		class RandomBaseComplete : public IRandomBaseComplete, public RandomBase
		{
			private:
				
		protected:
				module::Perlin PerlinNoiseCalculator;
				virtual void init() override;
				virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseComplete();
			RandomBaseComplete(const RandomBaseComplete &value);
			virtual ~RandomBaseComplete();
			

			void DoCalculations() override;
			void Constrain() override;
			void NormalCalculations() override;
			void UniformCalculations() override;
			void GaussianCalculations() override;
			void PerlinNoiseCalculations() override;

			RandomBaseComplete& operator=(const RandomBaseComplete& value);

			
		};

		class RandomBasePerlinNoise : public IRandomBasePerlinNoise, public RandomBase
		{

		private:
			
		protected:
			module::Perlin PerlinNoiseCalculator;
			virtual void init() override;
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			
			
			RandomBasePerlinNoise();
			RandomBasePerlinNoise(const RandomBasePerlinNoise &value);
			virtual ~RandomBasePerlinNoise();
			void DoCalculations() override;
			void PerlinNoiseCalculations() override;

			RandomBasePerlinNoise& operator=(const RandomBasePerlinNoise& value);
		};

		class RandomBaseGaussian : public IRandomBaseGaussian, public RandomBase
		{
		private:

		protected:
			virtual void init() override;
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseGaussian();
			RandomBaseGaussian(const RandomBaseGaussian &value);
			virtual ~RandomBaseGaussian();
			void DoCalculations() override;
			void GaussianCalculations() override;

			RandomBaseGaussian& operator=(const RandomBaseGaussian& value);
		};

		class RandomBaseUniform : public IRandomBaseUniform, public RandomBase
		{
		private:

		protected:
			virtual void init() override;
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseUniform();
			RandomBaseUniform(const RandomBaseUniform &value);
			virtual ~RandomBaseUniform();
			void DoCalculations() override;
			void UniformCalculations() override;

			RandomBaseUniform& operator=(const RandomBaseUniform& value);
		};

		class RandomBaseNormal : public IRandomBaseNormal, public RandomBase
		{
		private:
		protected:
			virtual void init() override;
			virtual void init(const mRECT &areaSize, RandomNumberMode randomNumberMode);
		public:
			RandomBaseNormal();
			RandomBaseNormal(const RandomBaseNormal &value);
			virtual ~RandomBaseNormal();
			void DoCalculations() override;
			void NormalCalculations() override;

			RandomBaseNormal& operator=(const RandomBaseNormal& value);
		};
        
    }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif
