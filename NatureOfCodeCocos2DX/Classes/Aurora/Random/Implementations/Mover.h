#ifndef NatureOfCodeCocos2DX_Mover_h
#define NatureOfCodeCocos2DX_Mover_h

#include "..\BaseClasses\ObjectBase.h"

namespace Aurora {
	namespace Random {

		class Mover : public RandomBaseComplete
		{

		private:
			mutable VECTOR2D position;
			mutable VECTOR2D velocity;
			mutable VECTOR2D acceleration;
			VECTOR2D target;

			Float maximiunVelocity;
			Float minimumVelocity;
			
			Float probalitityFactor;

			
			void Constrain() final;

			void UniformCalculations() final;

			void GaussianCalculations() final;

			void PerlinNoiseCalculations() final;

			void NormalCalculations();

			virtual void init() final;
			virtual void init(const Mover &value);
			virtual void init(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize);

		public:
			Mover();
			Mover(const mRECT &areaSize);
			Mover(const Mover &value);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize);
			~Mover();
			Mover(Mover &&value);
			Mover & operator=(Mover && value);

			void SetTarget(const VECTOR2D &target);
			void SetVelocityRange(const Float &maximumVelocity, const Float &minimumVelocity);
			const VECTOR2D GetCurentPosition() const;

			void Accelerate() const;
			void Decellerate() const;

			Mover& operator=(const Mover& value);

			

		};

		class IMover : public IObjectBaseBasic
		{
		private:
			virtual void init() final;
			virtual void init(const mRECT &areaSize);
			virtual void init(const IMover &value);
		public:
			Mover MoverObject;
			IMover();
			IMover(const mRECT &areaSize);
			IMover(const IMover &value);
			IMover(IMover &&value);
			IMover & operator=(IMover && value);
			virtual ~IMover();
			virtual void Render() override;

			IMover& operator=(const IMover& value);

			

		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif