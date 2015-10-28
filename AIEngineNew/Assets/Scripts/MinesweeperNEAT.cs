using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Assets.Scripts.AI.NeuralNetworks.NEAT;
using Assets.Scripts.AI.DataStructures;

public class MinesweeperNEAT : MonoBehaviour {


    Vector3 sweeperLastPosition = Vector3.zero;
    /// <summary>
    /// the minesweeper's neural net
    /// </summary>
    private NeuralNet Brain;

    Vector3 maxScreenTopRight;
    Vector3 minScreenBottomLeft;

    /// <summary>
    /// Weight value determining how sensitive the obstacle avoidance should be. The higher the value the more sensitive it is.
    /// </summary>
    public float SensorCollisionSensitivityAndAvoidance = 10000;

    public MemoryMapper MemoryMap;

    /// <summary>
    /// its position in the world
    /// </summary>
    public Vector2 Position;

    public LayerMask layerMask = -1; //make sure we aren't in this layer 

    /// <summary>
    /// direction sweeper is facing
    /// </summary>
    Vector2 LookAt;

    /// <summary>
    /// its rotation (surprise surprise)
    /// </summary>
    public double Rotation;

    public double Speed;

    /// <summary>
    /// to store output from the ANN, the current frame’s output from the network
    /// </summary>
    public double LeftTrack;

    /// <summary>
    /// //to store output from the ANN, the current frame’s output from the network
    /// </summary>
    public double RightTrack;

    /// <summary>
    /// The sweeper's fitness score. Every time the minesweeper finds a mine, its fitness score increases
    /// </summary>
    public double Fitness;
    public double RealTimeFitness;

    /// <summary>
    /// the scale of the sweeper when drawn
    /// </summary>
    public double Scale;
    Rigidbody2D rig2d;

    public double RotationTolerance = 1f;

    public Vector2 acceleration;
    public Vector2 velocity;

    /// <summary>
    /// Index position of closest mine
    /// </summary>
    public int ClosestMine;

    public bool HasHitObstacle = false;

    public float CollisionDistance = 0.5f;

    List<double> sweeperCollisionSensorData;
    List<double> sweeperMemoryMapSensorData;

    int numberOfCollisionSensors = 5;

    public int MemoryMapNumberOfCellAxisX = 10;
    public int MemoryMapNumberOfCellAxisY = 10;

    // Use this for initialization
    void Start()
    {
        this.sweeperCollisionSensorData = new List<double>();
        for (int x = 0; x < this.numberOfCollisionSensors; ++x)
            this.sweeperCollisionSensorData.Add(-1);

        this.sweeperMemoryMapSensorData = new List<double>();
        for (int x = 0; x < this.numberOfCollisionSensors; ++x)
            this.sweeperMemoryMapSensorData.Add(-1);
    }

    public void EndOfRunCalculations()
    {
        Fitness += MemoryMap.NumCellsVisited();
    }

    public void RealTimeRunCalculations()
    {
        RealTimeFitness += MemoryMap.NumCellsVisited();
    }

    public void StartInitialization()
    {
        // TODO Optimize here: Remove this to a more general place.
        maxScreenTopRight = Camera.main.ScreenToWorldPoint(new Vector3(NeuralNetworkParams.WindowWidth, NeuralNetworkParams.WindowHeight, 0));
        minScreenBottomLeft = Camera.main.ScreenToWorldPoint(Vector3.zero);
        this.Position = Camera.main.ScreenToWorldPoint(new Vector2((float)(RandomProvider.RandomFloat() * NeuralNetworkParams.WindowWidth), (float)(RandomProvider.RandomFloat() * NeuralNetworkParams.WindowWidth)));
        this.sweeperLastPosition = this.Position;
        //this.Position = this.transform.position;
        float angle = (float)RandomProvider.RandomFloat() * UnityEngine.Random.Range(0, AIConstants.TWO_PI);
        this.LookAt = new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle));
        this.LookAt.Normalize();

        //float angle = (float)RandomProvider.GetRandomNumber(RandomProvider.RND, -AIEngine.AIConstants.TWO_PI, AIEngine.AIConstants.TWO_PI);
        this.acceleration = Vector2.zero;
        this.velocity = Vector2.zero;
        this.Rotation = 0;
        this.LeftTrack = 0.16;
        this.RightTrack = 0.16;
        this.RealTimeFitness = 0;
        this.Fitness = 0;
        this.Scale = NeuralNetworkParams.SweeperScale;
        this.ClosestMine = 0;
        //this.Brain = new NeuralNet(NeuralNetworkParams.NumInputs, NeuralNetworkParams.NumOutputs, NeuralNetworkParams.NumHidden, NeuralNetworkParams.NeuronsPerHiddenLayer, NeuralNetworkParams.LEARNING_RATE);
        this.rig2d = this.GetComponent<Rigidbody2D>();
        this.MemoryMap = new MemoryMapper();
        this.MemoryMap.Init(new Cell(maxScreenTopRight.y, minScreenBottomLeft.y, minScreenBottomLeft.x, maxScreenTopRight.x, 0), this.MemoryMapNumberOfCellAxisX, this.MemoryMapNumberOfCellAxisY);
    }

    // Update is called once per frame
    void Update()
    {
        this.Position = this.transform.position;
    }

    

    /// <summary>
    /// Updates the ANN with information from the sweepers enviroment
    /// First we take sensor readings and feed these into the sweepers brain.
    ///
    ///	The inputs are:
    ///	
    ///	A vector to the closest mine (x, y)
    ///	The sweepers 'look at' vector (x, y)
    ///
    ///	We receive two outputs from the brain.. lTrack & rTrack.
    ///	So given a force for each track we calculate the resultant rotation 
    ///	and acceleration and apply to current velocity vector.
    /// </summary>
    /// <param name="mines"></param>
    /// <returns></returns>
    public bool UpdateANN(List<Vector2> mines)
    {
        this.acceleration = Vector2.zero;
        this.velocity = Vector2.zero;
        //this.Rotation = 0;
        //Debug.Log("Before: UpdateANN start");

        //this will store all the inputs for the NN
        List<double> inputs = new List<double>();
        //this.Rotation = UnityEngine.Random.Range(0, AIConstants.TWO_PI);
        /*
            First of all, the function calculates a vector to the closest mine and then normalizes
            it. (Remember, when a vector is normalized its length becomes 1.) The
            minesweeper’s look-at vector doesn’t need to be normalized in this way because its
            length is always 1. Because both vectors have been effectively scaled to within the
            same limits, the inputs can be considered to be standardized.
        */
        //get vector to closest mine
        Vector2 vectorClosestMine = GetClosestMine(mines);

        //normalise it
        vectorClosestMine.Normalize();

        float dot = Vector2.Dot(this.LookAt, vectorClosestMine);
        int sign = -1;

        if (this.LookAt.y * vectorClosestMine.x > this.LookAt.x * vectorClosestMine.y)
        {
            sign=  1;
        }
        else
        {
            sign = - 1;
        }

        /*
            The look-at vector and the vector to the closest mine are then input into the neural
            network. The NeuralNet Update function updates the minesweeper’s network with
            this information and returns a List of doubles as the output.
        */

        //add in vector to closest mine
        //inputs.Add(vectorClosestMine.x);
        //inputs.Add(vectorClosestMine.y);

        //add in sweepers look at vector
        //inputs.Add(this.LookAt.x);
        //inputs.Add(this.LookAt.y);
        //if (HasHitObstacle)
        //{
        //    int y = 0;
        //    Debug.Log("#####################################################");
        //    Debug.Log(dot);
        //    Debug.Log("item count: " + this.sweeperCollisionSensorData.Count);
        //    foreach (double d in this.sweeperCollisionSensorData)
        //        Debug.Log("sw: " + d);
        //}

        // TODO: Add mines to the neural network
        //inputs.Add(dot*sign);
        inputs.Add(this.HasHitObstacle ? 1 : 0);
        inputs.AddRange(this.sweeperCollisionSensorData);
        inputs.AddRange(this.sweeperMemoryMapSensorData);

        //Debug.Log("update the brain and get feedback");
        //update the brain and get feedback
        List<double> output = this.Brain.Update(inputs, RunType.Active);


        //make sure there were no errors in calculating the 
        //output
        if (output.Count < NeuralNetworkParams.NumOutputs)
        {
            return false;
        }


        //assign the outputs to the sweepers left & right tracks
        this.LeftTrack = output[0];
        this.RightTrack = output[1];

        /*
            After checking to make sure there are no errors when updating the neural network,
            the program assigns the outputs to LeftTrack and RightTrack. These values represent the
            forces being exerted on the left track and right track of the minesweeper.
        */

        //calculate steering forces
        double RotForce = this.LeftTrack - this.RightTrack;

        //clamp rotation
        Mathf.Clamp((float)RotForce, -(float)NeuralNetworkParams.MaxTurnRate, (float)NeuralNetworkParams.MaxTurnRate);

        /*
            The vehicle’s rotational force is calculated by subtracting the force exerted by the
            right track from the force exerted by the left track. This is then clamped to make
            sure it doesn’t exceed the maximum turn rate specified in the ini file. The vehicle’s
            speed is simply the sum of the left track and right track. Now that we know the
            minesweeper’s rotational force and speed, its position and rotation can be updated
            accordingly.
        */

        //update the minesweepers rotation
        this.Rotation += RotForce;
        //if (Rotation < 0)
        //    Rotation = AIConstants.TWO_PI;

        //if (Rotation > AIConstants.TWO_PI)
        //    Rotation = 0;

        if(this.HasHitObstacle)
        {
            this.Rotation += RotForce * 100;
        }

        this.Speed = (this.LeftTrack + this.RightTrack);
        if(this.Speed > NeuralNetworkParams.MaxSpeed)
            this.Speed = NeuralNetworkParams.MaxSpeed;
        //this.Speed *= 0.5f;
        //update Look At 
        
        this.LookAt.x = Mathf.Cos((float)this.Rotation);
        this.LookAt.y = -Mathf.Sin((float)this.Rotation);

        this.acceleration += (this.LookAt * (float)this.Speed);
        this.velocity += this.acceleration;
        var previousPosition = this.transform.position;

        var newPosition = previousPosition + (Vector3)this.velocity;
        var movementThisStep = newPosition - previousPosition;
        var movementLastStep = previousPosition - this.sweeperLastPosition;
        var previousPositionContinuedDirection = (previousPosition + movementLastStep) - previousPosition;
        var forward = transform.forward;
        float angle = Vector3.Angle(movementThisStep, previousPositionContinuedDirection);
        // Rotate the object towards the movement direction. NOTICE: the -90 degree turn is to point the sprite to the right direction
        transform.rotation = Quaternion.Euler(new Vector3(0, 0, (Mathf.Atan2(movementThisStep.y, movementThisStep.x) * Mathf.Rad2Deg) + -90));
        var movementThisStepSensorLength = movementThisStep * 4;

        this.DetectObstacles(previousPosition, movementThisStepSensorLength);
        this.ProcessMemoryMapWithSensors(previousPosition, movementThisStepSensorLength);
        

        // Move the object only if it has not hitted any obstacles
        if (!this.HasHitObstacle)
        {
            this.transform.position += (Vector3)this.velocity;


                //wrap around window limits
            if (this.transform.position.x > maxScreenTopRight.x)
                this.transform.position = new Vector3(minScreenBottomLeft.x, this.transform.position.y, 0);
            if (this.transform.position.x < minScreenBottomLeft.x)
                this.transform.position = new Vector3(maxScreenTopRight.x, this.transform.position.y, 0);
            if (this.transform.position.y > maxScreenTopRight.y)
                this.transform.position = new Vector3(this.transform.position.x, minScreenBottomLeft.y, 0);
            if (this.transform.position.y < minScreenBottomLeft.y)
                this.transform.position = new Vector3(this.transform.position.x, maxScreenTopRight.y, 0);
            this.sweeperLastPosition = previousPosition;
        }

        //if (this.GetComponent<SpriteRenderer>().color == Color.red || this.GetComponent<SpriteRenderer>().color == Color.yellow || this.GetComponent<SpriteRenderer>().color == Color.magenta)
        {
            Debug.DrawRay(previousPosition, movementThisStep, this.GetComponent<SpriteRenderer>().color, 1.7f);


            // Draw rays from current new position forward, this can be used for collision detection
            //--------------------------------------------------------

            // Points forward
            Debug.DrawRay(this.transform.position, movementThisStepSensorLength, Color.green);

            var sensorIn45DegreeForwardAngle = Quaternion.Euler(0, 0, 45) * movementThisStepSensorLength;
            var sensorInMinus45DegreeForwardAngle = Quaternion.Euler(0, 0, -45) * movementThisStepSensorLength;
            // Point 45 degrees forward
            Debug.DrawRay(this.transform.position, sensorIn45DegreeForwardAngle, Color.cyan);
            Debug.DrawRay(this.transform.position, sensorInMinus45DegreeForwardAngle, Color.cyan);

            var sensorIn90DegreeForwardAngle = Quaternion.Euler(0, 0, 90) * movementThisStepSensorLength;
            var sensorInMinus90DegreeForwardAngle = Quaternion.Euler(0, 0, -90) * movementThisStepSensorLength;
            // Points to the side of the object
            Debug.DrawRay(this.transform.position, sensorIn90DegreeForwardAngle, Color.yellow);
            Debug.DrawRay(this.transform.position, sensorInMinus90DegreeForwardAngle, Color.yellow);

            // Points backwards
            Debug.DrawRay(this.transform.position, movementThisStepSensorLength * -1, Color.red);


            //--------------------------------------------------------
        }

        this.MemoryMap.Update(this.transform.position.x, this.transform.position.y);
        return true;
    }

    public int GetNumberOfVisitedCellsInMemoryMap()
    {
        return this.MemoryMap.NumCellsVisited();
    }

    public float GetRatioOfNumberOfVisitedCellsInMemoryMap()
    {
        return (float)this.MemoryMap.NumCellsVisited() / (float)this.MemoryMap.NumCells();
    }

    public void DetectObstacles(Vector3 startPosition, Vector3 movementStep)
    {
        //TODO: This could be replaced entirely with Unity physics triggers and rigidbody but the position based movement needs to be removed and replaced with velocity or other which does not interfere with the physics engine.
        // TODO: Or if OOTB Unity physics is not good enough then use a custom sprehe vector to identify collisions.
        this.HasHitObstacle = false;
        this.sweeperCollisionSensorData.Clear();

        // Points forward
        this.sweeperCollisionSensorData.Add(this.DetectCollisionForSensorVector(startPosition, movementStep));

        // Point 45 and -45 degrees forward
        var sensorIn45DegreeForwardAngle = Quaternion.Euler(0, 0, 45) * movementStep;
        var sensorInMinus45DegreeForwardAngle = Quaternion.Euler(0, 0, -45) * movementStep;
        
        this.sweeperCollisionSensorData.Add(this.DetectCollisionForSensorVector(startPosition, sensorIn45DegreeForwardAngle));
        this.sweeperCollisionSensorData.Add(this.DetectCollisionForSensorVector(startPosition, sensorInMinus45DegreeForwardAngle));

        // Points 90 and -90 degreees to the side of the object
        var sensorIn90DegreeForwardAngle = Quaternion.Euler(0, 0, 90) * movementStep;
        var sensorInMinus90DegreeForwardAngle = Quaternion.Euler(0, 0, -90) * movementStep;
        
        this.sweeperCollisionSensorData.Add(this.DetectCollisionForSensorVector(startPosition, sensorIn90DegreeForwardAngle));
        this.sweeperCollisionSensorData.Add(this.DetectCollisionForSensorVector(startPosition, sensorInMinus90DegreeForwardAngle));

        // Points backwards
        //this.sweeperCollisionSensorData.Add(this.DetectCollisionForSensorVector(startPosition, movementStep * -1));
    }

    public void ProcessMemoryMapWithSensors(Vector3 startPosition, Vector3 movementStep)
    {
        this.sweeperMemoryMapSensorData.Clear();

        // Points forward
        this.sweeperMemoryMapSensorData.Add(this.DetectCellHistoryInMemoryMap(startPosition, movementStep));

        // Point 45 and -45 degrees forward
        var sensorIn45DegreeForwardAngle = Quaternion.Euler(0, 0, 45) * movementStep;
        var sensorInMinus45DegreeForwardAngle = Quaternion.Euler(0, 0, -45) * movementStep;

        this.sweeperMemoryMapSensorData.Add(this.DetectCellHistoryInMemoryMap(startPosition, sensorIn45DegreeForwardAngle));
        this.sweeperMemoryMapSensorData.Add(this.DetectCellHistoryInMemoryMap(startPosition, sensorInMinus45DegreeForwardAngle));

        // Points 90 and -90 degreees to the side of the object
        var sensorIn90DegreeForwardAngle = Quaternion.Euler(0, 0, 90) * movementStep;
        var sensorInMinus90DegreeForwardAngle = Quaternion.Euler(0, 0, -90) * movementStep;

        this.sweeperMemoryMapSensorData.Add(this.DetectCellHistoryInMemoryMap(startPosition, sensorIn90DegreeForwardAngle));
        this.sweeperMemoryMapSensorData.Add(this.DetectCellHistoryInMemoryMap(startPosition, sensorInMinus90DegreeForwardAngle));
    }

    /// <summary>
    /// Get an input data representing a "fitness" value for the neural network based on how many times the sweeper has been in a cell.
    /// </summary>
    /// <param name="startPosition"></param>
    /// <param name="movementStep"></param>
    /// <returns></returns>
    public float DetectCellHistoryInMemoryMap(Vector3 startPosition, Vector3 movementStep)
    {
        var sensorPosition = startPosition + movementStep;
        //check how many times the minesweeper has visited the cell
        //at the current position
        int HowOften = this.MemoryMap.TicksLingered(sensorPosition.x, sensorPosition.y);

        if (HowOften == 0)
        {
            return -1;
        }
        if (HowOften < 10)
        {
            return 0;
        }
        if (HowOften < 20)
        {
            return 0.2f;
        }
        if (HowOften < 30)
        {
            return 0.4f;
        }
        if (HowOften < 50)
        {
            return 0.6f;
        }
        if (HowOften < 80)
        {
            return 0.8f;
        }

        return 1;
    }

    public float DetectCollisionForSensorVector(Vector3 startPosition, Vector3 movementStep)
    {
        var movementThisStepSensorLength = movementStep;
        float movementSqrMagnitude = movementThisStepSensorLength.sqrMagnitude;
        float movementMagnitude = Mathf.Sqrt(movementSqrMagnitude);
        RaycastHit2D hitInfo = Physics2D.Raycast(startPosition, movementThisStepSensorLength, movementMagnitude, layerMask.value);
        
        if (hitInfo.collider)
        {

            // TODO: Collision detection does not work in NEAT
            var collisionRay = hitInfo.point - new Vector2(startPosition.x, startPosition.y);
            var ratio = collisionRay.sqrMagnitude / movementSqrMagnitude;
            if (ratio <= this.CollisionDistance)
            {
                this.HasHitObstacle = true;

                // TODO: Solve how to avoid object moving to fast going through obstacles?
                // This calculation is done to make the collision more sensitive in the neural network and force a quicker turn. Notice that the closer the sweeper is to an obstacle the higher the weight value is to avoid it.
                // Meaning the closer to zero the ratio is the more the sweeper needs to avoid it. This is to compensate higher speeds and not go through obstacles.
                //return (1- ratio) * this.SensorCollisionSensitivityAndAvoidance;
                return ratio;
            }
        }

        return -1;
    }

    //used to transform the sweepers vertices prior to rendering
    public void WorldTransform(List<Vector2> sweeper)
    {
        this.transform.localScale = new Vector3((float)this.Scale, (float)this.Scale);
        this.transform.Rotate(Vector3.right, (float)this.Rotation);
        this.transform.Translate(new Vector3(this.Position.x, this.Position.y));
    }

    /// <summary>
    /// returns a vector to the closest mine
    /// </summary>
    /// <param name="mines"></param>
    /// <returns></returns>
    public Vector2 GetClosestMine(List<Vector2> mines)
    {
        double closestSoFar = 99999;

        Vector2 ClosestObject = Vector2.zero;

        //cycle through mines to find closest
        for (int i = 0; i < mines.Count; i++)
        {
            double distanceToObject = Vector2.Distance(this.Position, mines[i] );

            if (distanceToObject < closestSoFar)
            {
                closestSoFar = distanceToObject;

                ClosestObject = (Vector3)mines[i] - this.transform.position;

                ClosestMine = i;
            }
        }

        return ClosestObject;
    }

    /// <summary>
    /// checks to see if the minesweeper has 'collected' a mine
    /// this function checks for collision with its closest mine (calculated
    ///  earlier and stored in m_iClosestMine)
    /// </summary>
    /// <param name="mines"></param>
    /// <param name="size"></param>
    /// <returns>-1 if nothing was collected or a index number of the closest mine</returns>
    public int CheckForMine(List<Vector2> mines, double size)
    {
        float DistToObject = Vector2.Distance(this.Position, mines[this.ClosestMine]);

        if (DistToObject < (size))
        {
            return ClosestMine;
        }

        return -1;
    }

    /// <summary>
    /// Resets the sweepers position, fitness and rotation
    /// </summary>
    public void Reset()
    {
        //reset the sweepers positions
        this.transform.position = this.Position = Camera.main.ScreenToWorldPoint(new Vector2((float)(RandomProvider.RandomFloat() * NeuralNetworkParams.WindowWidth), (float)(RandomProvider.RandomFloat() * NeuralNetworkParams.WindowWidth)));
        this.acceleration = Vector2.zero;
        this.velocity = Vector2.zero;
        this.Fitness = 0;
        this.Rotation = 0;
        this.RealTimeFitness = 0;
        this.MemoryMap.Reset();
        this.MemoryMap.Init(new Cell(maxScreenTopRight.y, minScreenBottomLeft.y, minScreenBottomLeft.x, maxScreenTopRight.x, 0), this.MemoryMapNumberOfCellAxisX, this.MemoryMapNumberOfCellAxisY);
    }


    public void IncrementFitness() { ++Fitness; }

    public void IncrementFitness(float value)
    {
        Fitness += value;
    }

    public void IncrementFitnessSmallerImpact()
    {
        Fitness += 0.01f;
    }

    public void IncrementFitnessMediumImpact()
    {
        Fitness += 0.02f;
    }

    //public void PutWeights(ref List<double> weights) { this.Brain.PutWeights(ref weights); }

    //public List<int> GetSplitPoints()
    //{
    //    return this.Brain.CalculateSplitPoints();
    //}

    //public int GetNumberOfWeights()
    //{
    //    return this.Brain.GetNumberOfWeights();
    //}

    public void InsertNewBrain(NeuralNet brain) { this.Brain = brain; }

}
