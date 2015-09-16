using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.AI
{
    public class Host
    {
        public Genome DNA { get; set; }
        public Genome DNALocations { get; set; }
        public Vector2 StartLocation { get; set; }
        public Vector2 EndLocation { get; set; }
        public float DistanceToTarget { get; set; }
        public float DistanceTraveled { get; set; }
        public Vector2 ClosesLocationToTarget { get; set;}
        private LayerMask layerMask = -1; //make sure we aren't in this layer 

        public Vector2 velocity;
        private Vector2 acceleration;
        private float sqrMinimumExtent;
        public bool HitObstacle { get; set; }
        public bool HitTarget { get; set; }
        public int finnishTime = 0;
        public int obstaclesHit = 0;

        public float Fitness()
        {
            return this.DNA.Fitness;
        }

        public void SetFitness(float fitness)
        {
            this.DNA.Fitness = fitness;
        }


        public Host(int geneLength, Vector2 location, float sqrMinimumExtent, LayerMask layerMask)
        {
            this.DNA = new Genome(geneLength);
            this.DNALocations = new Genome(0);
            this.StartLocation = location;
            this.EndLocation = Vector2.zero;
            this.ClosesLocationToTarget = Vector2.zero;
            this.sqrMinimumExtent = sqrMinimumExtent;
            this.layerMask = layerMask;
            this.DistanceTraveled = 0;
        }

        public Vector2 CalcualteEndLocationOfHost(Vector2 targetLocation)
        {
            Color rayColor = Color.yellow;
            float rayLenght = 0.5F;
            this.EndLocation = this.StartLocation;
            for(int x = 0; x < this.DNA.Genes.Count; ++x)
            {
                // Update a new position for the host
                acceleration += this.DNA.Genes[x];
                velocity += acceleration;
                Vector2 previousPosition = this.EndLocation;
                this.EndLocation += velocity;

                // Check to see if the new position has moved to another location
                Vector2 movementThisStep = this.EndLocation - previousPosition;
                float movementSqrMagnitude = movementThisStep.sqrMagnitude;
                if (movementSqrMagnitude > sqrMinimumExtent)
                {
                    float movementMagnitude = Mathf.Sqrt(movementSqrMagnitude);

                    // Check to see if the host has hit something
                    RaycastHit2D hitInfo = Physics2D.Raycast(previousPosition, movementThisStep, movementMagnitude, layerMask.value);
                    Debug.DrawRay(previousPosition, movementThisStep, rayColor, rayLenght);
                    var distanceToTarget = Vector2.Distance(targetLocation, this.EndLocation);

                    this.DistanceTraveled += distanceToTarget;
                    
                    //if (!hitInfo.collider)
                    {
                        this.DNALocations.Genes.Add(this.EndLocation);
                        
                    }
                    // If a hit occured check to see is it the target or some other obstacle
                    if(hitInfo.collider)
                    {
                        

                        // this is must the the target
                        if (distanceToTarget < 0.2 && !this.HitObstacle)
                        {
                            rayColor = Color.green;
                            //this.DNALocations.Genes.Add(this.EndLocation);
                            this.HitTarget = true;
                            
                            break;
                        }
                        // We have hit an obstacle this stop processing
                        else
                        {
                            rayColor = Color.red;
                            this.HitObstacle = true;
                            this.obstaclesHit++;
                            //break;
                        }
                    }
                    
                    if(!this.HitTarget)
                        this.finnishTime++;
                }
                acceleration *= 0;
            }

            return this.EndLocation;
        }

        public float CalculateFitnessAndDistance(Vector2 targetLocation)
        {
            if(this.EndLocation != this.StartLocation)
            {
                this.DistanceToTarget = Vector2.Distance(targetLocation, this.EndLocation);
                float distanceToTargetFromStartLocation = Vector2.Distance(targetLocation, this.StartLocation);
                // The target has been reached and make sure we are not dividing by zero.
                if (this.DistanceToTarget == 0)
                    this.DistanceToTarget = 1;

                // This means only the target was hit and make sure that we do not end up diving by zero
                if (this.obstaclesHit == 0)
                  this.obstaclesHit = 1;

                /* The fitness score is based on four things. 
                    1. The time it takes a path to reach its target, if time is not taken into consideration the slowest and safest path will win
                    2. the distance from the path, if distance is not taken into consideration the result would be a long path
                    3. and how many obstacles hit along the path, if obstacles are not taken into consideration the GA will not know if a path is good or bad even if it hits obstacles and how bad it is. The more obstacles a path hits the more unlikely it is to get reproduced.
                    4. The travel distance. The smaller the distance is the better the fitness score will be.
                    In each of the values the lower the time, or the distance or the obstacles hit the better the fitness score is. That is the score will be closer to 1 or above it for the best possible path.
                    The higher any value is the more likely it is to not be the most optimal path. The worst path is the one that hits obstacles.
                */

                //float finnishTimeCalculation = Mathf.Abs(RandomProvider.Map(this.finnishTime, 0, this.DNA.Genes.Count, 0, 1) - 1);
                //if (finnishTimeCalculation <= 0)
                //    finnishTimeCalculation = 0.01F;
                //float distanceToTargetcalculcation = Mathf.Abs(RandomProvider.Map(distanceToTargetFromStartLocation, 0, this.DistanceToTarget, 0, 1));
                //float obstaclesHitCalculation = Mathf.Abs(RandomProvider.Map(this.obstaclesHit, 0, this.DNA.Genes.Count, 0, 1) - 1);
                //if (obstaclesHitCalculation <= 0)
                //    obstaclesHitCalculation = 0.01F;
                //float distanceTraveledCalculation = Mathf.Abs(RandomProvider.Map(this.DistanceTraveled, 0, AIConstants.MaxTravelDistance, 0, 1));
                //float calculation2 = (finnishTimeCalculation + distanceToTargetcalculcation + obstaclesHitCalculation + distanceTraveledCalculation) / 4;
                //this.DNA.Fitness = calculation2;
                //float finnishTimeCalculation = ((float)this.DNA.Genes.Count / (float)this.finnishTime);
                //float distanceToTargetcalculcation = (distanceToTargetFromStartLocation / this.DistanceToTarget);
                //float obstaclesHitCalculation = (((float)this.obstaclesHit / (float)this.DNA.Genes.Count) - 1);
                //float distanceTraveledCalculation = (distanceToTargetFromStartLocation / this.DistanceTraveled);
                //float calculation = Mathf.Abs(finnishTimeCalculation) * Mathf.Abs(distanceToTargetcalculcation) * Mathf.Abs(obstaclesHitCalculation) * Mathf.Abs(distanceTraveledCalculation);

                var calculation = (this.finnishTime) * this.DistanceToTarget * this.obstaclesHit * this.DistanceTraveled;
                this.DNA.Fitness = 1 / calculation;
            }
            // We have not reached the target yet, this is another obstacle and the fitness must be reduced. We want to penalize the path for any obstacles. This is not what we want in the population for possible solutions.
            if(this.HitObstacle)
            {
                this.DNA.Fitness *= 0.1F;
            }

            // Award the path for hitting the target.
            if(this.HitTarget)
            {
                this.DNA.Fitness += 1;
            }

            return this.DNA.Fitness;
        }

    }
}
