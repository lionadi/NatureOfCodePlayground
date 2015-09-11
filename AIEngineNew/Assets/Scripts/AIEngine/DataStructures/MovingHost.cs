using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace AIEngine.DataStructures
{
    public class MovingHost
    {

        #region Fields
        public IDNA Dna { get; set; }
        public Vector2 location;
        public Vector2 velocity;
        private Vector2 acceleration;
        
        /// <summary>
        /// Size
        /// </summary>
        public float r = 4;

        /// <summary>
        /// How close did it get to the target
        /// </summary>
        public float recordDist = 10000;

        /// <summary>
        /// Fitness and DNA
        /// </summary>
        public float Fitness;

        /// <summary>
        /// To count which force we're on in the genes
        /// </summary>
        public int geneCounter = 0;

        /// <summary>
        /// Am I stuck on an obstacle?
        /// </summary>
        public bool HitObstacle { get; set; }


        private bool hitTarget = false;
        /// <summary>
        /// Did I reach the target
        /// </summary>
        public bool HitTarget
        {
            get
            {
                return hitTarget;
            }

            set
            {
                if (!value)
                {
                    finishTime++;
                }

                hitTarget = value;
            }
        }

        /// <summary>
        /// What was my finish time?
        /// </summary>
        public int finishTime = 0;

        public UnityEngine.Component target;

        public int dnaLifetime;

        #endregion

        //Rigidbody2D hostRB;
        //// Use this for initialization
        //void Start()
        //{
        //    hostRB = this.GetComponent<Rigidbody2D>();
        //    //Instantiate(this);
        //    if(this.Dna == null)
        //    {
        //        this.Dna = new DNA(dnaLifetime);
        //    }
        //}

        // Update is called once per frame
        void Update()
        {
            //this.Run();
            velocity += acceleration;
            location += velocity;
            acceleration *= 0;
            this.UpdateDistanceToTarget();

            //this.GetComponentInParent<Rigidbody>().velocity = velocity;

            
            
            //hostRB.velocity = velocity;
            
        }

        //void OnTriggerEnter2D(Collider2D other)
        //{
        //    //Destroy(other.gameObject);
        //    if (other.GetType() == this.target.GetType())
        //        this.HitTarget = true;

        //    if (other.GetType() == typeof(Obstacle))
        //        this.HitObstacle = true;
        //}

        //void OnTriggerExit2D(Collider2D other) {
        //    if (other.GetType() == this.target.GetType())
        //        this.HitTarget = false;

        //    if (other.GetType() == typeof(Obstacle))
        //        this.HitObstacle = false;
        //}

        //void OnTriggerStay2D(Collider2D other)
        //{
            
        //}


        public MovingHost(Vector2 location, UnityEngine.Component target, int dnaLifetime)
        {
            this.acceleration = Vector2.zero;
            this.velocity = Vector2.zero;
            this.location = location;

            this.r = 0.5F;
            this.Dna = new DNA(dnaLifetime);
            this.finishTime = 0;
            this.recordDist = 10000;
            this.target = target;
        }

        public MovingHost(Vector2 location, IDNA dna, UnityEngine.Component target)
        {
            this.acceleration = Vector2.zero;
            this.velocity = Vector2.zero;
            this.location = location;

            this.r = 4;
            this.Dna = dna;
            this.finishTime = 0;
            this.recordDist = 10000;
            this.target = target;
        }

        /// <summary>
        /// FITNESS FUNCTION
        /// // distance = distance from target
        /// finish = what order did i finish (first, second, etc. . .)
        /// f(distance,finish) =   (1.0f / finish^1.5) * (1.0f / distance^6);
        /// a lower finish is rewarded (exponentially) and/or shorter distance to target (exponetially)
        /// </summary>
        public void EvalutateFitness()
        {
            if (recordDist < 1) recordDist = 1;

            // Reward finishing faster and getting close
            Fitness = (1 / (recordDist));

            // Make the function exponential
            //fitness = Mathf.Pow(fitness, 4);

            if (this.HitObstacle) Fitness *= 0.1F; // lose 90% of fitness hitting an obstacle
            if (hitTarget) Fitness *= 2; // twice the fitness for finishing!
        }

        /// <summary>
        /// Run in relation to all the obstacles
        /// If I'm stuck, don't bother updating or checking for intersection
        /// </summary>
        public void Run()
        {
            if (!this.HitObstacle && !hitTarget && Dna != null)
            {
                this.ApplyForce(Dna.Genes[geneCounter]);
                geneCounter = (geneCounter + 1) % Dna.Genes.Count;
                this.Update();
            }
        }

        /// <summary>
        /// Do this in the object update method(in rendered frames?)
        /// </summary>
        public void UpdateDistanceToTarget()
        {
            float d = Vector2.Distance(location, target.transform.position);
            if (d < recordDist) recordDist = d;

            if(d < 0.5F && !this.hitTarget)
            {
                hitTarget = true;
            } else if(!this.hitTarget)
            {
                this.finishTime++;
            }
        }

        void ApplyForce(Vector2 force)
        {
            acceleration += force;
        }



        public float GetFitness()
        {
            return Fitness;
        }

    }
}
