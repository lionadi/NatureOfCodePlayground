#ifndef NatureOfCodeCocos2DX_ObjectBase_h
#define NatureOfCodeCocos2DX_ObjectBase_h


#include "RandomBase.h"



namespace Aurora {
    namespace Random {

		class PObjectBaseBasic : virtual public PRandomBase
        {
            protected:
                
            public:
				PObjectBaseBasic();
				virtual ~PObjectBaseBasic();
                virtual void Render() = 0;

				virtual void SetRandomNumberMode(RandomNumberMode randomNumberMode);

		};

		}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif