#ifndef NatureOfCodeCocos2DX_Mover_h
#define NatureOfCodeCocos2DX_Mover_h

#include "..\BaseClasses\ObjectBase.h"

namespace Aurora {
	namespace Random {

		class Mover : virtual public RandomBaseComplete
		{

		private:
			mutable VECTOR2D position;
			mutable VECTOR2D velocity;
			mutable VECTOR2D acceleration;
			VECTOR2D target;

			Float maximiunVelocity;
			Float minimumVelocity;
			
			Float probalitityFactor;

			
			void Constrain();

			void UniformCalculations();

			void GaussianCalculations();

			void PerlinNoiseCalculations();

			void NormalCalculations();

			virtual void init();
			virtual void init(const Mover &value);
			virtual void init(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize);

		public:
			Mover();
			Mover(const mRECT &areaSize);
			Mover(const Mover &value);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize);
			~Mover();

			void SetTarget(const VECTOR2D &target);
			void SetVelocityRange(const Float &maximumVelocity, const Float &minimumVelocity);
			const VECTOR2D GetCurentPosition() const;

			void Accelerate() const;
			void Decellerate() const;

			Mover& operator=(const Mover& value);

			

		};

		class PMover : virtual public PObjectBaseBasic
		{
		private:
			virtual void init();
			virtual void init(const mRECT &areaSize);
			virtual void init(const PMover &value);
		public:
			Mover MoverObject;
			PMover();
			PMover(const mRECT &areaSize);
			PMover(const PMover &value);
			virtual ~PMover();
			virtual void Render();

			PMover& operator=(const PMover& value);

			

		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif