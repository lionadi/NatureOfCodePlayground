using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


    public static class AIConstants
    {
        public static float TWO_PI = 6.28318530718F;
        public static float maxforce = 0.1F;
        public static float MAX_COS_TWO_PI = UnityEngine.Mathf.Cos(AIConstants.TWO_PI);
        public static float MAX_SIN_TWO_PI = UnityEngine.Mathf.Sin(AIConstants.TWO_PI);
        public static UnityEngine.Vector2 MAX_Vector2d_COSIN_TWO_PI = new UnityEngine.Vector2(AIConstants.MAX_COS_TWO_PI, AIConstants.MAX_SIN_TWO_PI);
    public static float MaxTravelDistance = 0;
}
