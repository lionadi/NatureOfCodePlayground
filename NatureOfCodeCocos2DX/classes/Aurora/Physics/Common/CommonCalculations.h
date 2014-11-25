#ifndef NatureOfCodeCocos2DX_CommonCalculations_h
#define NatureOfCodeCocos2DX_CommonCalculations_h


#include "../BaseClasses/ForceBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {
		class CommonCalculations
		{
		protected:
			const static  VECTOR2D EarthGravity;
			const static float NormalSurfaceFrictionCoefficient;
		public:
			static void init();
			//static VECTOR2D CalculateGravityForMass(const Float &mass);
			//static VECTOR2D CalculateGravityForMass(const Float &mass);
			/*Force();
			virtual ~Force();
			Force(const Force &value);
			Force& operator=(const Force& value);
			Force(Force &&value);
			Force & operator=(Force && value);

			virtual void init() override;
			virtual void init(const Force &value);
			virtual void init(Force &&value);*/
		};
	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif