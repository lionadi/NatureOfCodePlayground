using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.AI
{
    public class GA : MonoBehaviour
    {
        public List<Host> Hosts { get; set; }
        public int PopulationSize;
        public float CrossoverRate;
        public float MutationRate;

        //this is the max amount a gene can be mutated by using UniformMutation
        public float MutationDelta = 0.3F;

        public float time = 1;

        //public int ChromoLengt;
        public int GeneLength;
        public Host FittestGenome { get; set; }
        public float BestFitnessScore;
        public float WorstFitnessScore;
        public float AverageFitnessScore;
        public float TotalFitnessScore;
        public float Sigma;
        public int Generation;
        private int pathPosition = 0;
        public float targetAccuracyPercentage = 0.95F;
        public float BoltzmannTemperature = 550;
        public Vector2 mutationBoundryValueMin;
        public Vector2 mutationBoundryValueMax;
        /// <summary>
        /// the lower this value, the more species you will get.
        /// </summary>
        public float CompatibilityTolerance = 0.32F;

        /// <summary>
        /// this is the number of generations a species is allowed to live 
        ///without showing any fitness improvement.
        /// </summary>
        public int GenerationsAllowedWithoutImprovement = 20;

        private float BOLTZMANN_DT = 0.05F;
        private float BOLTZMANN_MIN_TEMP = 1;

        private Component target;
        private Component previousTarget;
        Rigidbody2D hostRB;

        public Vector2 velocity;
        private Vector2 acceleration;
        public float speed = 0.1F;
        public bool HitObstacle { get; set; }
        public bool HitTarget { get; set; }
        private Vector2 previousPosition;

        public LayerMask layerMask = -1; //make sure we aren't in this layer 
        private float minimumExtent;
        private float partialExtent;
        private float sqrMinimumExtent;
        private Rigidbody2D myRigidbody;
        private Collider2D myCollider;
        public float skinWidth = 0.1f; //probably doesn't need to be changed 

        public int finnishTime = 0;
        public int obstaclesHit = 0;
        private bool automaticLoop = true;

        float width = 1.0F;
        Color color = Color.red;
        List<GameObject> waypoints;
        List<Target> targets;
        List<Species> Species;

        public int NextGenomeID = 0;
        public int NextSpeciesID = 0;
        private int targetCounter = 0;

        private DontGoThroughThings dgtt = null;

        #region UnityRelatedAndInit

        void Start()
        {
            this.BestFitnessScore = 0;
            this.WorstFitnessScore = 0;
            this.TotalFitnessScore = 0;
            this.AverageFitnessScore = 0;

            // Calculate the max travel distance for the max vector(from position zero) multiplied by the amount of max steps/position an object can make(gene length)
            AIConstants.MaxTravelDistance = (this.GeneLength * (Vector2.Distance(Vector2.zero, AIConstants.MAX_Vector2d_COSIN_TWO_PI))) * this.GeneLength;
            this.dgtt = this.GetComponent<DontGoThroughThings>();
            myRigidbody = GetComponent<Rigidbody2D>();
            myCollider = GetComponent<Collider2D>();

            minimumExtent = 0;// Mathf.Min(myCollider.bounds.extents.x, myCollider.bounds.extents.y);
            partialExtent = minimumExtent * (1.0f - skinWidth);
            sqrMinimumExtent = minimumExtent * minimumExtent;
            this.waypoints = new List<GameObject>();

            this.targets = new List<Target>();
            this.Species = new List<Species>();
            // Get all the targets in the scene and order them so that the closest ones are first to tbe processed(notice that after the fist target has been reached this is not true anymore)
            this.targets.AddRange(GameObject.FindObjectsOfType<Target>().OrderBy(o => Vector2.Distance(transform.position, o.transform.position)));
            this.target = this.targets[targetCounter];

            this.CreateStartPopulation();
            this.UpdateFitnessScores();
            var hosts = this.Hosts;
            this.FitnessScaleRankingToFloatRangeZeroToOne(ref hosts);
            //hostRB = this.GetComponent<Rigidbody2D>();




        }

        IEnumerator MoveObject(Transform thisTransform, Vector3 startPos, Vector3 endPos, float time, int positionCount, int maxPositions)
        {
            var i = 0.0f;
            var rate = 1.0f / time;
            {
                while (i < 1.0f)
                {
                    i += Time.deltaTime * rate;
                    thisTransform.position = Vector3.Lerp(startPos, endPos, i);

                    yield return null;
                }
            }
        }

        void OnTriggerEnter2D(Collider2D other)
        {
            //Destroy(other.gameObject);
            var parentIsTarget = other.GetComponentInParent<Target>();
            if (parentIsTarget != null)
            {
                this.HitTarget = true;
                // Reset the GA only if this is not the last target and only if the collided object is the same as the target. The host can collide with other objects to
                if (this.targets.Last().transform.position != parentIsTarget.transform.position && parentIsTarget.transform.position == target.transform.position)
                {
                    this.ResetGAData();
                }
            } else
            {
                //var parentIsObstacle = other.GetComponentInParent<Obstacle>();
                //if (parentIsObstacle != null)
                //{
                //    this.HitObstacle = true;
                //}
            }
        }

        void OnTriggerExit2D(Collider2D other)
        {
            var parentIsTarget = other.GetComponentInParent<Target>();
            if (parentIsTarget != null)
            {
                //this.HitTarget = false;
            }
            else
            {
                //var parentIsObstacle = other.GetComponentInParent<Obstacle>();
                //if (parentIsObstacle != null)
                //{
                //    this.HitObstacle = false;
                //}
            }
        }

        void OnTriggerStay2D(Collider2D other)
        {
            //var parentIsObstacle = other.GetComponentInParent<Obstacle>();
            //if (parentIsObstacle != null)
            //{
            //    this.HitObstacle = false;
            //    this.dgtt.HasHit = false;
            //}
        }

        void ResetGAData()
        {
            if (targetCounter < this.targets.Count)
                previousTarget = this.targets[this.targetCounter];

            targetCounter++;
            if (this.targetCounter >= this.targets.Count || previousTarget.transform.position == targets[this.targetCounter].transform.position)
                return;

            this.Generation = 0;
            this.TotalFitnessScore = 0;
            this.BestFitnessScore = 0;
            this.FittestGenome = null;
            this.HitTarget = false;
            this.HitObstacle = false;
            this.obstaclesHit = 0;
            this.finnishTime = 0;


            this.target = this.targets[this.targetCounter];

            this.CreateStartPopulation();
            this.UpdateFitnessScores();
            // Move to the next target in the list

            this.pathPosition = 0;
        }

        void Update()
        {
            //if (Input.GetKeyDown("space") && !this.automaticLoop)
            //{
            //    this.TesgroundUpdate();
            //}
            //else if (this.automaticLoop || Input.GetKeyDown("up"))
            //{
            //    this.automaticLoop = true;
            //    this.TesgroundUpdate();
            //}

            //this.TesgroundUpdate();
            this.MichalewiczUpdate();
            //this.SpeciationUpdate();
        }

        /// <summary>
        /// Remember fixed update is more taxing, especially on raycasting
        /// </summary>
        void FixedUpdate()
        {
            //this.TesgroundUpdate();

            //if (Input.GetKeyDown("space"))
            //{
            //    //this.CreateStartPopulation();
            //    //this.UpdateFitnessScores();
            //    this.MonteCarloUpdate();
            //}
        }


        /// <summary>
        /// This is not ready!!!
        /// </summary>
        public void SpeciationUpdate()
        {
            acceleration *= 0;
            float step = 0;


            // Check to see if the target has been reached
            if (FittestGenome != null && this.HitTarget && !this.HitObstacle)
            {
                if (pathPosition < (this.FittestGenome.DNALocations.Genes.Count))
                {
                    {
                        Debug.Log("target reached and no more calculations will be done. this path is to be drawn");
                        // Move the object to the next position
                        pathPosition++;

                        if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count - 1)
                            return;

                        step = speed * Time.deltaTime;

                        // Some simple waypoints drawing on the screen for the fittest genome
                        if (pathPosition > 0 && (pathPosition - 1) < this.FittestGenome.DNA.Genes.Count - 1)
                        {
                            this.previousPosition = this.FittestGenome.DNALocations.Genes[pathPosition - 1];
                            Debug.DrawLine(previousPosition, this.FittestGenome.DNALocations.Genes[pathPosition], Color.red, 60);
                            waypoints.Add(GameObject.CreatePrimitive(PrimitiveType.Cube));
                            waypoints[waypoints.Count - 1].transform.position = this.FittestGenome.DNALocations.Genes[pathPosition];
                            waypoints[waypoints.Count - 1].transform.localScale *= 0.05F;
                        }


                        StartCoroutine(MoveObject(transform, transform.position, this.FittestGenome.DNALocations.Genes[pathPosition], time, pathPosition, this.FittestGenome.DNALocations.Genes.Count - 1));
                    }
                    return;
                }
                // If the target has reached it's position then do not do anything else or reset the data
                else if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count)
                {
                    var d = Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]);
                    if (this.myRigidbody.IsSleeping() && Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]) < 1)
                        this.ResetGAData();

                    return;
                }
            }
            else
            {
                List<Host> matingPool = new List<Host>();
                int SpawnAmountRqd = PopulationSize;
                var hosts = this.Hosts;
                //assign each individual to a species
                this.Speciate(ref hosts);

                //calculate the number of offspring each species
                //should produce
                CalculateExpectedOffspring(SpawnAmountRqd);

                //assign a different color to each of the top few species
                this.SortAndAssignVisualAid();

                foreach (Species curSpc in this.Species)
                {
                    int NumToSpawnFromThisSpecies = Mathf.RoundToInt(curSpc.ExpectedOffspring());
                    int NewBabies = 0;

                    var host = this.Hosts;

                    while ((NumToSpawnFromThisSpecies-- > 0) && (NewBabies < PopulationSize))
                    {
                        Host mum = curSpc.SpawnGenome();
                        Host dad = curSpc.SpawnGenome();

                        Host baby1 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                        Host baby2 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                        this.CrossoverMichalewicz(ref mum.DNA.Genes, ref dad.DNA.Genes, ref baby1.DNA.Genes, ref baby2.DNA.Genes);

                        this.MutateMichalewicz(ref baby1.DNA.Genes);
                        this.MutateMichalewicz(ref baby2.DNA.Genes);

                        matingPool.Add(baby1);
                        matingPool.Add(baby2);

                        NewBabies += 2;
                    }

                }

                this.Hosts = matingPool;
                this.UpdateFitnessScores();

                this.FitnessScaleRankingToFloatRangeZeroToOne(ref hosts);
                ++this.Generation;

                this.DrawFailedPaths();

                step = speed * Time.deltaTime;

            }
        }

        // Work in progress
        public void TesgroundUpdate()
        {
            acceleration *= 0;
            float step = 0;


            // Check to see if the target has been reached
            if (FittestGenome != null && this.HitTarget && !this.HitObstacle)
            {
                if (pathPosition < (this.FittestGenome.DNALocations.Genes.Count))
                {
                    {
                        Debug.Log("target reached and no more calculations will be done. this path is to be drawn");
                        // Move the object to the next position
                        pathPosition++;

                        if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count - 1)
                            return;

                        step = speed * Time.deltaTime;

                        // Some simple waypoints drawing on the screen for the fittest genome
                        if (pathPosition > 0 && (pathPosition - 1) < this.FittestGenome.DNA.Genes.Count - 1)
                        {
                            this.previousPosition = this.FittestGenome.DNALocations.Genes[pathPosition - 1];
                            Debug.DrawLine(previousPosition, this.FittestGenome.DNALocations.Genes[pathPosition], Color.red, 60);
                            waypoints.Add(GameObject.CreatePrimitive(PrimitiveType.Cube));
                            waypoints[waypoints.Count - 1].transform.position = this.FittestGenome.DNALocations.Genes[pathPosition];
                            waypoints[waypoints.Count - 1].transform.localScale *= 0.05F;
                        }


                        StartCoroutine(MoveObject(transform, transform.position, this.FittestGenome.DNALocations.Genes[pathPosition], time, pathPosition, this.FittestGenome.DNALocations.Genes.Count - 1));
                    }
                    return;
                }
                // If the target has reached it's position then do not do anything else or reset the data
                else if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count)
                {
                    var d = Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]);
                    if (this.myRigidbody.IsSleeping() && Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]) < 1)
                        this.ResetGAData();

                    return;
                }
            }
            else
            {
                List<Host> matingPool = new List<Host>();

                int NewBabies = 0;

                var host = this.Hosts;

                while (NewBabies < PopulationSize)
                {
                    Host mum = MonteCarloSelection();
                    Host dad = MonteCarloSelection();

                    Host baby1 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                    Host baby2 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                    this.CrossoverSinglePoint(ref mum.DNA.Genes, ref dad.DNA.Genes, ref baby1.DNA.Genes, ref baby2.DNA.Genes);

                    MutateReplace(ref baby1.DNA.Genes);
                    MutateReplace(ref baby2.DNA.Genes);

                    matingPool.Add(baby1);
                    matingPool.Add(baby2);

                    NewBabies += 2;
                }
                this.Hosts = matingPool;
                this.UpdateFitnessScores();
                var hosts = this.Hosts;
                this.FitnessScaleRankingToFloatRangeZeroToOne(ref hosts);
                ++this.Generation;

                this.DrawFailedPaths();

                step = speed * Time.deltaTime;

            }
        }

        /// <summary>
        /// This is not ready!!!
        /// </summary>
        public void MichalewiczUpdate()
        {
            acceleration *= 0;
            float step = 0;


            // Check to see if the target has been reached
            if (FittestGenome != null && this.HitTarget && !this.HitObstacle)
            {
                if (pathPosition < (this.FittestGenome.DNALocations.Genes.Count))
                {
                    {
                        Debug.Log("target reached and no more calculations will be done. this path is to be drawn");
                        // Move the object to the next position
                        pathPosition++;

                        if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count - 1)
                            return;

                        step = speed * Time.deltaTime;

                        // Some simple waypoints drawing on the screen for the fittest genome
                        if (pathPosition > 0 && (pathPosition - 1) < this.FittestGenome.DNA.Genes.Count - 1)
                        {
                            this.previousPosition = this.FittestGenome.DNALocations.Genes[pathPosition - 1];
                            Debug.DrawLine(previousPosition, this.FittestGenome.DNALocations.Genes[pathPosition], Color.red, 60);
                            waypoints.Add(GameObject.CreatePrimitive(PrimitiveType.Cube));
                            waypoints[waypoints.Count - 1].transform.position = this.FittestGenome.DNALocations.Genes[pathPosition];
                            waypoints[waypoints.Count - 1].transform.localScale *= 0.05F;
                        }


                        StartCoroutine(MoveObject(transform, transform.position, this.FittestGenome.DNALocations.Genes[pathPosition], time, pathPosition, this.FittestGenome.DNALocations.Genes.Count - 1));
                    }
                    return;
                }
                // If the target has reached it's position then do not do anything else or reset the data
                else if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count)
                {
                    var d = Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]);
                    if (this.myRigidbody.IsSleeping() && Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]) < 1)
                        this.ResetGAData();

                    return;
                }
            }
            else
            {
                List<Host> matingPool = new List<Host>();

                int NewBabies = 0;

                var host = this.Hosts;

                while (NewBabies < PopulationSize)
                {
                    Host mum = MonteCarloSelection();
                    Host dad = MonteCarloSelection();

                    Host baby1 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                    Host baby2 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                    this.CrossoverMichalewicz(ref mum.DNA.Genes, ref dad.DNA.Genes, ref baby1.DNA.Genes, ref baby2.DNA.Genes);

                    MutateMichalewicz(ref baby1.DNA.Genes);
                    MutateMichalewicz(ref baby2.DNA.Genes);

                    matingPool.Add(baby1);
                    matingPool.Add(baby2);

                    NewBabies += 2;
                }
                this.Hosts = matingPool;
                this.UpdateFitnessScores();
                var hosts = this.Hosts;
                this.FitnessScaleRankingToFloatRangeZeroToOne(ref hosts);
                ++this.Generation;

                this.DrawFailedPaths();

                step = speed * Time.deltaTime;

            }
        }

        public void MonteCarloUpdate()
        {
            acceleration *= 0;
            float step = 0;


            // Check to see if the target has been reached
            if (FittestGenome != null && this.HitTarget && !this.HitObstacle)
            {
                if (pathPosition < (this.FittestGenome.DNALocations.Genes.Count))
                {
                    {
                        Debug.Log("target reached and no more calculations will be done. this path is to be drawn");
                        // Move the object to the next position
                        pathPosition++;

                        if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count - 1)
                            return;

                        step = speed * Time.deltaTime;
                        if (pathPosition > 0 && (pathPosition - 1) < this.FittestGenome.DNA.Genes.Count - 1)
                        {
                            this.previousPosition = this.FittestGenome.DNALocations.Genes[pathPosition - 1];
                            Debug.DrawLine(previousPosition, this.FittestGenome.DNALocations.Genes[pathPosition], Color.red, 60);
                            waypoints.Add(GameObject.CreatePrimitive(PrimitiveType.Cube));
                            waypoints[waypoints.Count - 1].transform.position = this.FittestGenome.DNALocations.Genes[pathPosition];
                            waypoints[waypoints.Count - 1].transform.localScale *= 0.05F;
                        }


                        StartCoroutine(MoveObject(transform, transform.position, this.FittestGenome.DNALocations.Genes[pathPosition], time, pathPosition, this.FittestGenome.DNALocations.Genes.Count - 1));
                    }
                    return;
                }
                // If the target has reached it's position then do not do anything else.
                else if (pathPosition >= this.FittestGenome.DNALocations.Genes.Count)
                {
                    var d = Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]);
                    if (this.myRigidbody.IsSleeping() && Vector2.Distance(transform.position, this.FittestGenome.DNALocations.Genes[pathPosition - 1]) < 1)
                        this.ResetGAData();

                    return;
                }
            }
            else
            {
                List<Host> matingPool = new List<Host>();

                int NewBabies = 0;
                //if(this.FittestGenome != null)
                //for(int x = 0; x < 10; ++x)
                //    matingPool.Add(this.FittestGenome);

                //var hosts = this.Hosts;

                //this.GrabNBest(3, 3, ref hosts, ref matingPool);
                //NewBabies = 3 * 3;

                while (NewBabies < PopulationSize)
                {
                    Host mum = MonteCarloSelection();
                    Host dad = MonteCarloSelection();

                    Host baby1 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                    Host baby2 = new Host(0, this.transform.position, sqrMinimumExtent, layerMask);
                    CrossoverSinglePoint(ref mum.DNA.Genes, ref dad.DNA.Genes, ref baby1.DNA.Genes, ref baby2.DNA.Genes);

                    MutateReplace(ref baby1.DNA.Genes);
                    MutateReplace(ref baby2.DNA.Genes);

                    matingPool.Add(baby1);
                    matingPool.Add(baby2);

                    NewBabies += 2;
                }
                this.Hosts = matingPool;
                this.UpdateFitnessScores();


                ++this.Generation;

                this.DrawFailedPaths();

                //acceleration += this.FittestGenome.DNA.Genes[pathPosition];
                //velocity += acceleration;
                step = speed * Time.deltaTime;
                //transform.position = Vector3.MoveTowards(transform.position, new Vector3(this.FittestGenome.DNALocations.Genes[pathPosition].x, this.FittestGenome.DNALocations.Genes[pathPosition].y), step);
                //StartCoroutine(MoveObject(transform, transform.position, this.FittestGenome.DNALocations.Genes[pathPosition], 3.0f));
            }
        }

        public void DrawFailedPaths()
        {
            var pathsToDraw = this.Hosts.OrderByDescending(o => o.DNA.Fitness).Take(1);
            Vector2 pastPathPosition = this.transform.position;
            foreach (Host path in pathsToDraw)
                foreach (Vector2 position in path.DNALocations.Genes)
                {
                    Debug.DrawLine(pastPathPosition, position, Color.green, 0.5F);
                    pastPathPosition = position;
                }
        }

        #endregion



        #region Speciation

        /// <summary>
        /// Separate the population into species. This separates the individuals into species of similar genomes.
        /// </summary>
        public void Speciate(ref List<Host> population)
        {
            //first clear the existing members and kill off any non developing
            //species
            this.Species.Clear();

            //now separate the population into species
            for (int gen = 0; gen < population.Count; ++gen)
            {
                bool bAdded = false;

                foreach(Species curSpecies in this.Species)
                {
                    //calculate the compatibility score
                    double cs = Compatibility(population[gen], curSpecies.Sample());

                    //if the compatibility score is less than our tolerance then
                    //this genome is added to the species
                    if (cs < CompatibilityTolerance)
                    {
                        curSpecies.AddGenome(population[gen]);

                        bAdded = true;

                        break;
                    }

                }//next species

                if (!bAdded)
                {
                    //not compatible with any current species so create a new 
                    //species
                    Species.Add(new Species(population[gen], NextSpeciesID++));
                }

            }//next genome



            //update all the species to make sure their sample member is set
            //to the best genome found so far. Kill off any empty species
            //foreach (Species curSpecies in this.Species)
            for(int x = this.Species.Count -1; x >= 0; --x)
            {
                var curSpecies = this.Species[x];
                curSpecies.UpdateSampleGenome();

                if ((curSpecies.Empty() ||
                     (curSpecies.GenerationsNoImprovement() > GenerationsAllowedWithoutImprovement)) &&
                     (Species.Count > 1))
                {
                    Species.RemoveAt(x);
                }
            }
        }

        /// <summary>
        /// this allocates a compatibility score between two genomes. If the
        /// score is below a certain threshold then the two genomes are </summary>
        /// considered to be of the same species<param name="g1"></param>
        /// <param name="g2"></param>
        /// <returns></returns>
        public float Compatibility(Host g1, Host g2)
        {
            if (g1.DNA.Genes.Count != g2.DNA.Genes.Count) return 0;

            float RunningTotal = 0.0F;

            for (int gene = 0; gene < g1.DNA.Genes.Count; ++gene)
            {
                //RunningTotal += Mathf.Abs(g1.Genes[gene] - g2.Genes[gene]);
                RunningTotal += Vector2.Distance(g1.DNA.Genes[gene], g2.DNA.Genes[gene]);
            }

            return RunningTotal / g1.DNA.Genes.Count;
        }

        /// <summary>
        /// this method calculates the amount of offspring each species
        /// should produce.</summary>
        /// <param name="AmountNeeded"></param>
        public void CalculateExpectedOffspring(int AmountNeeded)
        {
            //first calculate the total fitness of all active genomes
            float TotalFitness = 0.0F;

            foreach (Species curSpecies in this.Species)
            {
                //apply fitness sharing first
                curSpecies.FitnessShare();

                TotalFitness += curSpecies.TotalFitness();
            }

            //now it is necessary to calculate the expected amount of offspring
            //from each species
            double expec = 0.0;

            foreach (Species curSpecies in this.Species)
            {
                curSpecies.SetExpectedOffspring(TotalFitness, AmountNeeded);

                expec += curSpecies.ExpectedOffspring();
            }
        }

        /// <summary>
        /// this sorts the species and assigns a color to each one.
        /// The color is just cosmetic to be used as a visual aid.</summary>
        public void SortAndAssignVisualAid()
        {
            if (this.Species.Count < 0) return;
            this.Species.OrderByDescending(o => o.BestEverFitness());
        }

        #endregion

        #region MutatioOperators

        /// <summary>
        /// Exchange Mutation operator does this by choosing two genes in a chromosome and swapping them.
        /// </summary>
        /// <param name="genes"></param>
        public void MutateEM(ref List<Vector2> genes)
        {
            //return dependent upon mutation rate
            if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > MutationRate) return;

            //choose first gene
            int pos1 = RandomProvider.RND.Next(0, genes.Count - 1);

            //choose second
            int pos2 = pos1;
            while (pos1 == pos2)
            {
                pos2 = RandomProvider.RND.Next(0, genes.Count - 1);
            }

            Vector2 temp = genes[pos1];
            genes[pos1] = genes[pos2];
            genes[pos2] = temp;
        }

        public void ChooseSection(ref int begin, ref int end, int count, int minSpanSize)
        {
            //choose first gene
            begin = RandomProvider.RND.Next(0, count);

            //choose second
            end = begin;
            while (begin >= end)
            {
                end = RandomProvider.RND.Next(begin, begin + minSpanSize);
            }

        }

        public void MutateDM(ref List<Vector2> genes)
        {
            //return dependent upon mutation rate
            if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > MutationRate) return;

            //first we choose a section of the chromosome
            const int MinSpanSize = 3;

            //these will hold the beginning and end points of the span
            int beg = 0, end = 0;
            ChooseSection(ref beg, ref end, genes.Count - 1, MinSpanSize);

            // Calculate how many items to get and later remove
            int span = end - beg;

            //hold on to the section we are moving
            List<Vector2> aSectionOfGenes = genes.GetRange(beg, span);

            //erase from current position
            genes.RemoveRange(beg, span);

            int newInsertPosition = RandomProvider.RND.Next(0, genes.Count - 1);

            genes.InsertRange(newInsertPosition, aSectionOfGenes);

        }

        public void MutateIVM(ref List<Vector2> genes)
        {
            //return dependent upon mutation rate
            if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > MutationRate) return;

            //first we choose a section of the chromosome
            const int MinSpanSize = 3;

            //these will hold the beginning and end points of the span
            int beg = 0, end = 0;
            ChooseSection(ref beg, ref end, genes.Count - 1, MinSpanSize);

            // Calculate how many items to reverse
            int span = end - beg;

            genes.Reverse(beg, span);
        }

        public void MutateDIVM(ref List<Vector2> genes)
        {
            //return dependent upon mutation rate
            if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > MutationRate) return;

            //first we choose a section of the chromosome
            const int MinSpanSize = 3;

            //these will hold the beginning and end points of the span
            int beg = 0, end = 0;
            ChooseSection(ref beg, ref end, genes.Count - 1, MinSpanSize);

            // Calculate how many items to reverse
            int span = end - beg;

            genes.Reverse(beg, span);

            //hold on to the section we are moving
            List<Vector2> aSectionOfGenes = genes.GetRange(beg, span);

            //erase from current position
            genes.RemoveRange(beg, span);

            int newInsertPosition = RandomProvider.RND.Next(0, genes.Count - 1);

            genes.InsertRange(newInsertPosition, aSectionOfGenes);
        }

        public void MutateIM(ref List<Vector2> genes)
        {
            //return dependent upon mutation rate
            if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > MutationRate) return;

            int newInsertPosition = RandomProvider.RND.Next(0, genes.Count - 1);

            //erase from current position
            Vector2 gene = genes[newInsertPosition];

            genes.RemoveAt(newInsertPosition);

            newInsertPosition = RandomProvider.RND.Next(0, genes.Count - 1);

            genes.Insert(newInsertPosition, gene);
        }

        /// <summary>
        /// Requires a larger mutation rate
        /// </summary>
        /// <param name="genes"></param>
        public void MutateSM(ref List<Vector2> genes)
        {
            //return dependent upon mutation rate
            if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > MutationRate) return;

            //first we choose a section of the chromosome
            const int MinSpanSize = 3;

            //these will hold the beginning and end points of the span
            int beg = 0, end = 0;
            ChooseSection(ref beg, ref end, genes.Count - 1, MinSpanSize);

            int span = end - beg;

            //now we just swap randomly chosen genes with the beg/end
            //range a few times to scramble them
            int NumberOfSwapsRqd = span;

            while (--NumberOfSwapsRqd >= 0)
            {
                //choose two loci within the range
                int pos1 = beg + RandomProvider.RND.Next(0, span);
                int pos2 = beg + RandomProvider.RND.Next(0, span);


                //exchange them
                if (pos1 != pos2)
                {
                    Vector2 temp = genes[pos1];
                    genes[pos1] = genes[pos2];
                    genes[pos2] = temp;
                }
            }//repeat
        }

        /// <summary>
        /// replaces the gene with a completely new value
        /// </summary>
        /// <param name="genes"></param>
        public void MutateReplace(ref List<Vector2> genes)
        {
            for (int i = 0; i < genes.Count; i++)
            {
                //flip this bit?
                if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) < MutationRate)
                {
                    float angle = UnityEngine.Random.Range(0, AIConstants.TWO_PI);
                    genes[i] = ((new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle))) * UnityEngine.Random.Range(0, AIConstants.maxforce));
                }
            }
        }

        /// <summary>
        /// displaces a gene's value by a small random amount (limited by
        ///  MutationDelta)
        /// </summary>
        /// <param name="genes"></param>
        public void MutateUniform(ref List<Vector2> genes)
        {
            for (int i = 0; i < genes.Count; i++)
            {
                //flip this bit?
                if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) < MutationRate)
                {
                    float angle = UnityEngine.Random.Range(0, AIConstants.TWO_PI);
                    genes[i] = ((new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle))) * UnityEngine.Random.Range(0, (float)RandomProvider.RandomClamped() * this.MutationDelta));
                }
            }
        }

        /// <summary>
        /// displaces the genes value by an amount described by a normal  distribution
        /// </summary>
        /// <param name="genes"></param>
        public void MutateGaussian(ref List<Vector2> genes)
        {
            for (int i = 0; i < genes.Count; i++)
            {
                //flip this bit?
                if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) < MutationRate)
                {
                    //genes[i] =
                         
                    /*
                //do we mutate this gene?
	  if (RandFloat() < m_dMutationRate)
	  {
      gen.vecGenes[gene] += RandGaussian(0.0, 0.1);

      //make sure the value stays within the desired lims
      Clamp(gen.vecGenes[gene], 0.0, 1.0);    
                */
                }
            }
        }

        /// <summary>
        /// Sets a gene to either the min or max possible value (0 or 1 in this
        ///  implementation)
        /// </summary>
        /// <param name="genes"></param>
        public void MutateBoundary(ref List<Vector2> genes)
        {
            for (int i = 0; i < genes.Count; i++)
            {
                float angle = UnityEngine.Random.Range(0, AIConstants.TWO_PI);
                //flip this bit?
                Vector2 tempVector = new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle)) * UnityEngine.Random.Range(0, AIConstants.maxforce);
                if (tempVector.x < mutationBoundryValueMin.x && tempVector.y < mutationBoundryValueMin.y)
                {
                    genes[i] = Vector2.zero;
                }
                else
                {
                    genes[i] = this.mutationBoundryValueMax;
                }
            }
        } 
                
 

        public void MutateMichalewicz(ref List<Vector2> genes)
        {
            float chance = (float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1);

            if (chance <= 0.333)
            {
                MutateBoundary(ref genes);
            }

            else if (chance >= 0.667)
            {
                MutateUniform(ref genes);
            }

            else
            {
                MutateReplace(ref genes);
            }
        }


        #endregion

        #region CrossoverOperators


        /// <summary>
        /// This function performs multipoint crossover on the genes. That is to
        ///  say for each chromosome where crossover is to be performed we determine
        ///  a swap rate and iterate through each chromosome swap over individual
        ///  genes where appropriate. 
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverMultiPoint(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            if ((mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            //iterate down the length of the genomes swapping genes
            //depending on the crossover rate
            for (int gen = 0; gen < mum.Count; ++gen)
            {
                if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) < CrossoverRate))
                {
                    //swap the genes
                    baby2.Add(mum[gen]);
                    baby1.Add(dad[gen]);
                }
                else
                {
                    //don't swap the genes
                    baby1.Add(mum[gen]);
                    baby2.Add(dad[gen]);
                }
            }
        }

        /// <summary>
        /// This crossover operator simply averages the genes at each locus
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverAverage(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            for (int gen = 0; gen < mum.Count; ++gen)
            {
                baby1.Add((mum[gen] + dad[gen]) * 0.5F);
                baby2.Add((mum[gen] + dad[gen]) * 0.5F);
            }
        }

        /// <summary>
        ///  this operator creates a child whos genes are biased towards the 
        /// fitter parent.
        ///
        /// The heuristic used is r(V1-V2) + V1 where V1 is the fitter parent
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverHeuristic(ref List<Vector2> fittest, ref List<Vector2> not_so_fit, ref List<Vector2> baby1)
        {

            float rate = (float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1);

            //iterate down the length of the genome using the heuristic
            for (int gene = 0; gene < fittest.Count; ++gene)
            {
                Vector2 NewGeneValue = fittest[gene] + rate *
      (fittest[gene] - not_so_fit[gene]);
                baby1.Add(NewGeneValue);
            }
        }

        public void CrossoverPBX(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            //just return dependent on the crossover rate or if the
            //chromosomes are the same.
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            //initialize the babies with minus values so we can tell which positions
            //have been filled later in the algorith
            for (int x = 0; x < mum.Count; ++x)
            {
                baby1.Add(Vector2.zero);
                baby2.Add(Vector2.zero);
            }

            int l = baby2.Count;

            //holds the positions of the chosen elements
            List<int> positions = new List<int>();

            //first chosen city position
            int Pos = RandomProvider.RND.Next(0, mum.Count - 2);

            //keep adding random cities until we can add no more
            //record the positions as we go
            while (Pos < mum.Count)
            {
                positions.Add(Pos);

                // next gene
                Pos += RandomProvider.RND.Next(1, mum.Count - Pos);
            }

            //now we have chosen some cities it's time to copy the selected cities
            //over into the offspring in the same position.
            for (int pos = 0; pos < positions.Count; ++pos)
            {
                //baby1 receives from mum
                baby1[positions[pos]] = mum[positions[pos]];
                //baby2 receives from dad
                baby2[positions[pos]] = dad[positions[pos]];
            }

            //fill in the blanks. First create two position markers so we know
            //whereabouts we are in baby1 and baby2
            int c1 = 0, c2 = 0;
            for (int pos = 0; pos < mum.Count; ++pos)
            {
                //advance position marker until we reach a free position
                //in baby2
                while ((baby2[c2] != Vector2.zero) && (c2 < mum.Count -1))
                {
                    ++c2;
                }

                Vector2 tempElement = mum[pos];
                //baby2 gets the next city from mum which is not already
                //present
                if (!baby2.Exists(o => o == tempElement))
                {
                    baby2[c2] = mum[pos];
                }
                //now do the same for baby1
                while ((baby1[c1] != Vector2.zero) && (c1 < mum.Count -1))
                {
                    ++c1;
                }

                tempElement = dad[pos];
                //baby1 gets the next city from dad which is not already
                //present
                if (!baby1.Exists( o => o == tempElement))
                {
                    baby1[c1] = dad[pos];
                }
            }
        }

        public void CrossoverOBX(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            //just return dependent on the crossover rate or if the
            //chromosomes are the same.
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            baby1 = mum;
            baby2 = dad;

            List<Vector2> tempGenes = new List<Vector2>();
            List<int> positions = new List<int>();

            //first chosen city position
            int Pos = RandomProvider.RND.Next(0, mum.Count - 2);

            //keep adding random cities until we can add no more
            //record the positions as we go
            while (Pos < mum.Count)
            {
                positions.Add(Pos);

                tempGenes.Add(mum[Pos]);

                // next gene
                Pos += RandomProvider.RND.Next(1, mum.Count - Pos);
            }

            //so now we have n amount of cities from mum in the tempCities
            //vector we can impose their order in dad.
            int cPos = 0;

            for (int cit = 0; cit < baby2.Count; ++cit)
            {
                for (int i = 0; i < tempGenes.Count; ++i)
                {
                    if (baby2[cit] == tempGenes[i])
                    {
                        baby2[cit] = tempGenes[cPos];
                        ++cPos;
                        break;
                    }
                }
            }

            //now vice versa. Choose the same positioned cities from dad and impose
            //their order in mum
            tempGenes.Clear();
            cPos = 0;

            //first grab the cities from the same positions in dad
            for (int i = 0; i < positions.Count; ++i)
            {
                tempGenes.Add(dad[positions[i]]);
            }

            //and impose their order in mum
            for (int cit = 0; cit < baby1.Count; ++cit)
            {
                for (int i = 0; i < tempGenes.Count; ++i)
                {
                    if (baby1[cit] == tempGenes[i])
                    {
                        baby1[cit] = tempGenes[cPos];
                        ++cPos;
                        break;
                    }
                }
            }
        }

        /// <summary>
        /// the Michalewicz crossover operator choses one of three different
        ///  crossover operators based on an even probability
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverMichalewicz(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            float chance = (float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1);

            if (chance <= 0.333)
            {
                CrossoverTwoPoint(ref mum, ref dad, ref baby1, ref baby2);
            }

            else if (chance >= 0.667)
            {
                CrossoverAverage(ref mum, ref dad, ref baby1, ref baby2);
            }

            else
            {
                CrossoverHeuristic(ref mum, ref dad, ref baby1);
                CrossoverHeuristic(ref mum, ref dad, ref baby2);
            }
        }

        /// <summary>
        /// Partially-Mapped Crossover
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverPMX(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            //just return dependent on the crossover rate or if the
            //chromosomes are the same.
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            baby1 = mum;
            baby2 = dad;

            int maxItemsCount = mum.Count;

            if (mum.Count > dad.Count)
                maxItemsCount = dad.Count;

            //first we choose a section of the chromosome
            int begin = RandomProvider.RND.Next(0, maxItemsCount - 2);
            int end = begin;

            //find an end
            while (end <= begin)
            {
                end = RandomProvider.RND.Next(0, maxItemsCount - 1);
            }

            //now we iterate through the matched pairs of genes from beg
            //to end swapping the places in each child
            for (int pos = begin; pos < end + 1; ++pos)
            {

                //these are the genes we want to swap
                Vector2 gene1 = mum[pos];
                Vector2 gene2 = dad[pos];
                if (gene1 != gene2)
                {
                    //find and swap them in baby1
                    int posGene1 = baby1.IndexOf(gene1);
                    int posGene2 = baby1.IndexOf(gene2);

                    if (posGene1 >= 0)
                        baby1[posGene1] = gene2;

                    if (posGene2 >= 0)
                        baby2[posGene2] = gene1;

                    //and in baby2
                    posGene1 = baby2.IndexOf(gene1);
                    posGene2 = baby2.IndexOf(gene2);

                    if (posGene1 >= 0)
                        baby2[posGene1] = gene2;

                    if (posGene2 >= 0)
                        baby2[posGene2] = gene1;
                }
            }//next pair
        }

        /// <summary>
        /// given parents and storage for the offspring this method performs
        ///	crossover according to the GAs crossover rate
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverSinglePoint(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            int cp = RandomProvider.RND.Next(0, this.GeneLength - 1);

            for (int i = 0; i < cp; i++)
            {
                baby1.Add(mum[i]);
                baby2.Add(dad[i]);
            }
            for (int i = cp; i < mum.Count; i++)
            {
                baby1.Add(dad[i]);
                baby2.Add(mum[i]);
            }
        }

        /// <summary>
        /// given parents and storage for the offspring, this method performs
        ///	crossover according to the GAs crossover rate
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverTwoPoint(ref List<Vector2> mum, ref List<Vector2> dad, ref List<Vector2> baby1, ref List<Vector2> baby2)
        {
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0 || mum.Count != dad.Count)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            int cp = RandomProvider.RND.Next(0, this.GeneLength - 1);
            int cp2 = RandomProvider.RND.Next(0, this.GeneLength - 1);

            while(cp2 == cp)
                cp2 = RandomProvider.RND.Next(0, this.GeneLength - 1);

            baby1.AddRange(mum);
            baby2.AddRange(dad);

            for (int i = cp; i < cp2; i++)
            {
                baby1[i] = dad[i];
                baby2[i] = mum[i];
            }
        }

        #endregion

        #region SelectionOperators

        /// <summary>
        /// 
        /// </summary>
        /// <param name="N">Select N members from the population at random testing against</param>
        /// <returns></returns>
        public Host TournamentSelection(int N)
        {
            double BestFitnessSoFar = 0;

            int ChosenOne = 0;

            //Select N members from the population at random testing against
            //the best found so far
            for (int i = 0; i < N; ++i)
            {
                int ThisTry = RandomProvider.RND.Next(0, this.PopulationSize - 2);
                if (this.Hosts[ThisTry].DNA.Fitness > BestFitnessSoFar)
                {
                    ChosenOne = ThisTry;
                    BestFitnessSoFar = this.Hosts[ThisTry].DNA.Fitness;
                }
            }

            //return the champion
            return this.Hosts[ChosenOne];
        }
        /// <summary>
        /// this function calculates the variance of the population
        /// </summary>
        /// <param name="hosts"></param>
        /// <returns></returns>
        float CalculateVariance(ref List<Host> hosts)
        {
            float RunningTotal = 0.0F;

            //first iterate through the population to calculate the standard
            //deviation
            for (int gen = 0; gen < hosts.Count; ++gen)
            {
                RunningTotal += (hosts[gen].DNA.Fitness - this.AverageFitnessScore) *
                                (hosts[gen].DNA.Fitness - this.AverageFitnessScore);
            }

            return RunningTotal / hosts.Count;
        }

        /// <summary>
        /// calculates the fittest and weakest genome and the average/total 
        ///  fitness scores.
        /// </summary>
        /// <param name="source"></param>
        public void CalculateBestWorstAverageTotalFitnessScore(ref List<Host> source)
        {
            this.TotalFitnessScore = 0;
            this.BestFitnessScore = 0;
            this.WorstFitnessScore = float.MaxValue;
            foreach (Host host in source)
            {
                float normalizedFitnessScore = host.DNA.Fitness;

                if (normalizedFitnessScore < this.WorstFitnessScore)
                    this.WorstFitnessScore = normalizedFitnessScore;

                if (normalizedFitnessScore > this.BestFitnessScore)
                    this.BestFitnessScore = normalizedFitnessScore;

                this.TotalFitnessScore += normalizedFitnessScore;
            }

            this.AverageFitnessScore = this.TotalFitnessScore / source.Count;
        }

        public void SUSSelection(ref List<Host> source, ref List<Host> target)
        {
            //this algorithm relies on all the fitness scores to be positive so
            //these few lines check and adjust accordingly (in this example

            //Sigma scaling can give negative fitness scores
            if (WorstFitnessScore < 0)
            {
                //recalculate
                for (int gen = 0; gen < source.Count; ++gen)
                {
                    source[gen].DNA.Fitness += Mathf.Abs(WorstFitnessScore);
                }
                CalculateBestWorstAverageTotalFitnessScore(ref source);
            }

            int curGen = 0;
            double sum = 0;

            //NumToAdd is the amount of individuals we need to select using SUS.
            //Remember, some may have already been selected through elitism
            int NumToAdd = this.PopulationSize - target.Count;

            //calculate the hand spacing
            float PointerGap = this.TotalFitnessScore / (float)NumToAdd;

            float ptr = UnityEngine.Random.Range(0, 1) * PointerGap;

            while (target.Count < NumToAdd)
            {
                for (sum += source[curGen].DNA.Fitness; sum > ptr; ptr += PointerGap)
                {
                    target.Add(source[curGen]);
                    if (target.Count == NumToAdd)
                    {
                        return;
                    }
                }
                ++curGen;
            }
        }

        public Host MonteCarloSelection()
        {
            Host selectionHost = null;

            while (selectionHost == null)
            {
                int a = RandomProvider.RND.Next(0, this.Hosts.Count - 1);
                int b = RandomProvider.RND.Next(0, this.Hosts.Count - 1);

                int populationIndexChosen = -1;

                if (this.Hosts[a].DNA.Fitness > this.Hosts[b].DNA.Fitness)
                {
                    populationIndexChosen = a;
                }
                else
                {
                    populationIndexChosen = b;
                }

                if (populationIndexChosen >= 0 && (this.Hosts[populationIndexChosen].DNA.Fitness) < 1)
                    selectionHost = this.Hosts[populationIndexChosen];
            }

            return selectionHost;
        }

        /// <summary>
        /// selects a member of the population by using roulette wheel 
        ///  selection as described in the text.
        /// </summary>
        /// <returns></returns>
        public Host RouletteWheelSelection()
        {
            double fSlice = (float)RandomProvider.GetRandomNumber(RandomProvider.RND,0 ,1) * TotalFitnessScore;

            double cfTotal = 0;
            int SelectedGenome = 0;
            for (int i = 0; i < PopulationSize; ++i)
            {
                cfTotal += this.Hosts[i].DNA.Fitness;
                if (cfTotal > fSlice)
                {
                    SelectedGenome = i;
                    break;
                }
            }
            return this.Hosts[SelectedGenome];
        }

        /// <summary>
        /// This works like an advanced form of elitism by inserting NumCopies
        ///  copies of the NBest most fittest genomes into a population vector
        /// </summary>
        /// <param name="NBest"></param>
        /// <param name="numCopies"></param>
        /// <param name="source"></param>
        /// <param name="target"></param>
        public void GrabNBest(int NBest, int numCopies, ref List<Host> source, ref List<Host> target)
        {
            var hostToGrab = source.OrderByDescending(o => o.DNA.Fitness).Take(NBest);

            foreach (Host host in hostToGrab)
                for (int x = 0; x < numCopies; ++x)
                    target.Add(host);
        }

        #endregion

        #region Scaling

        /// <summary>
        /// Scales the fitness using sigma scaling 
        /// </summary>
        /// <param name="pop"></param>
        public void FitnessScaleSigma(ref List<Host> pop)
        {

            
            //standard deviation is the square root of the variance
            Sigma = Mathf.Sqrt(this.CalculateVariance(ref pop));
            //now iterate through the population to reassign the fitness scores

            for (int gen = 0; gen < pop.Count; ++gen)
            {
                float OldFitness = pop[gen].DNA.Fitness;
                pop[gen].DNA.Fitness = (OldFitness - this.AverageFitnessScore) /
                (2 * Sigma);
            }
            //recalculate values used in selection
            this.CalculateBestWorstAverageTotalFitnessScore(ref pop);

        }

        /// <summary>
        /// This function applies Boltzmann scaling to a population's fitness
        ///  scores.
        /// </summary>
        /// <param name="pop"></param>
        public void FitnessScaleBoltzmann(ref List<Host> pop)
        {
            //reduce the temp a little each generation
            this.BoltzmannTemperature -= BOLTZMANN_DT;
            //make sure it doesn't fall below minimum value
            if (this.BoltzmannTemperature < BOLTZMANN_MIN_TEMP)
            {
                this.BoltzmannTemperature = BOLTZMANN_MIN_TEMP;
            }
            //first calculate the average fitness/Temp
            float divider = this.AverageFitnessScore / this.BoltzmannTemperature;
            //now iterate through the population and calculate the new expected
            //values
            for (int gen = 0; gen < pop.Count; ++gen)
            {
                float OldFitness = pop[gen].DNA.Fitness;
                pop[gen].DNA.Fitness = (OldFitness / this.BoltzmannTemperature) / divider;
            }
            //recalculate values used in selection
            this.CalculateBestWorstAverageTotalFitnessScore(ref pop);
        }

        /// <summary>
        /// This type of fitness scaling simply assigns a fitness score based 
        ///	on its sorted position. (so if a genome ends up last it
        ///	gets score of zero, if best then it gets a score equal to the size
        ///	of the population.
        /// </summary>
        /// <param name="pop"></param>
        public void FitnessScaleRanking(ref List<Host> pop)
        {
            // Arrange the population according to the highest fitness score currently
            var population = pop.OrderByDescending(o => o.DNA.Fitness);

            // The highest ranking value will be the max count of hosts in the population, while the minimum is for the least fittest memeber will have the fit score of one.
            int populationSize = pop.Count;
            foreach(Host host in population)
            {
                // Apply a new fittness score based on the raking value which is determined by the population size.
                host.DNA.Fitness = populationSize;
                // Go to the next ranking value for the next host
                populationSize--;
            }

            this.CalculateBestWorstAverageTotalFitnessScore(ref pop);
        }

        public void FitnessScaleRankingToFloatRangeZeroToOne(ref List<Host> pop)
        {
            // Arrange the population according to the highest fitness score currently
            var population = pop.OrderByDescending(o => o.DNA.Fitness);

            // The highest ranking value will be the max count of hosts in the population, while the minimum is for the least fittest memeber will have the fit score of one.
            int populationSize = pop.Count;
            foreach (Host host in population)
            {
                // Apply a new fittness score based on the raking value which is determined by the population size.
                host.DNA.Fitness = Mathf.Abs((1 / (float)populationSize) - 1);
                // Go to the next ranking value for the next host
                populationSize--;
            }

            this.CalculateBestWorstAverageTotalFitnessScore(ref pop);
        }

        #endregion

        public void UpdateFitnessScores()
        {
            this.TotalFitnessScore = 0;
            for (int x = 0; x < this.Hosts.Count; x++)
            {
                this.Hosts[x].CalcualteEndLocationOfHost(target.transform.position);
                this.Hosts[x].CalculateFitnessAndDistance(target.transform.position);
                float normalizedFitnessScore = (this.Hosts[x].DNA.Fitness );

                if (normalizedFitnessScore < this.WorstFitnessScore)
                    this.WorstFitnessScore = normalizedFitnessScore;

                if (normalizedFitnessScore > this.BestFitnessScore)
                    this.BestFitnessScore = normalizedFitnessScore;

                if (normalizedFitnessScore > this.targetAccuracyPercentage && this.Hosts[x].HitTarget) //&& this.BestFitnessScore < this.targetAccuracyPercentage) || (normalizedFitnessScore > this.targetAccuracyPercentage && normalizedFitnessScore > this.BestFitnessScore))
                {
                    this.BestFitnessScore = normalizedFitnessScore;
                    this.FittestGenome = this.Hosts[x];
                    this.HitTarget = this.FittestGenome.HitTarget;
                    this.HitObstacle = this.FittestGenome.HitObstacle;
                    this.obstaclesHit = this.FittestGenome.obstaclesHit;
                    this.finnishTime = this.FittestGenome.finnishTime;
                }

                this.TotalFitnessScore += this.Hosts[x].DNA.Fitness;
            }

            this.AverageFitnessScore = this.TotalFitnessScore / this.Hosts.Count;
        }

        // Generate random bits between source and pointing directions towards the target
        public void CreateStartPopulation()
        {
            if (this.Hosts == null)
                this.Hosts = new List<Host>();

            if (this.Hosts != null && this.Hosts.Count > 0)
                this.Hosts.Clear();

                for (int x = 0; x < this.PopulationSize; x++)
            {
                this.Hosts.Add(new Host(this.GeneLength, this.transform.position, sqrMinimumExtent, layerMask));
            }
        }

        public GA(float crossoverRate, float mutationRate, int chromoLengt, int popSize, int geneLength)
        {
            this.CrossoverRate = crossoverRate;
            this.MutationRate = mutationRate;
            //this.ChromoLengt = chromoLengt;
            this.PopulationSize = popSize;
            this.GeneLength = geneLength;

            this.Generation = 0;
            this.TotalFitnessScore = 0;

            
        }
    }
}
