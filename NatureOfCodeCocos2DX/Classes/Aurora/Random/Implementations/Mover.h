#ifndef NatureOfCodeCocos2DX_Mover_h
#define NatureOfCodeCocos2DX_Mover_h

#include "..\BaseClasses\ObjectBase.h"

namespace Aurora {
	namespace Random {

		class Mover : virtual public RandomBaseComplete
		{

		private:
			VECTOR2D position;
			VECTOR2D velocity;
			VECTOR2D acceleration;
			VECTOR2D target;

			Float maximiunVelocity;
			Float minimumVelocity;
			
			Float probalitityFactor;

			
			void Constrain();

			void UniformCalculations();

			void GaussianCalculations();

			void PerlinNoiseCalculations();

			void NormalCalculations();

		public:
			Mover(const mRECT &areaSize);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize);
			Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize);
			~Mover();

			void SetTarget(const VECTOR2D &target);
			void SetVelocityRange(const Float &maximumVelocity, const Float &minimumVelocity);
			VECTOR2D GetCurentPosition();

			void Accelerate();
			void Decellerate();

		};

		class PMover : virtual public PObjectBaseBasic
		{

		public:
			Mover MoverObject;
			PMover(const mRECT &areaSize);
			virtual ~PMover();
			void Render();

		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif