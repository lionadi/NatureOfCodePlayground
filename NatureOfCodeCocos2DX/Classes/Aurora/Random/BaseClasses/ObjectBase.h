#ifndef NatureOfCodeCocos2DX_ObjectBase_h
#define NatureOfCodeCocos2DX_ObjectBase_h

#include "RandomBase.h"


namespace Aurora {
    namespace Random {

		class IObjectBaseBasic
        {
            protected:
				virtual void init();
            public:
				IObjectBaseBasic() = default;
				virtual ~IObjectBaseBasic() = default;
                virtual void Render() = 0;

				
		};

		}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif