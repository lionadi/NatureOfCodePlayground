using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using AIEngine;
using AIEngine.DataStructures;

public class Main : MonoBehaviour {

    int lifetime = 100;  // How long should each generation live
    int populationCount = 50;

    Population population;  // Population

    int lifecycle;          // Timer for cycle of generation
    int recordtime;         // Fastest time to target
    float mutationRate = 0.01F;

    Target target;        // Target location
    List<Obstacle> obstacles;
    Rigidbody2D hostRB;
	// Use this for initialization
	void Start () {
        hostRB = this.GetComponent<Rigidbody2D>();
	        obstacles = new List<Obstacle>();
            obstacles.AddRange(GameObject.FindObjectsOfType<Obstacle>());

            this.target = GameObject.FindObjectOfType<Target>();
            this.population = new Population(this.target, mutationRate, populationCount, Camera.main.pixelWidth, Camera.main.pixelHeight, lifetime, this.transform.position);
            

	}
	
	// Update is called once per frame
	void Update () {
        // If the generation hasn't ended yet
        //if (lifecycle < lifetime)
        //{
        //    population.Live();
        //    if ((population.TargetReached()) && (lifecycle < recordtime))
        //    {
        //        recordtime = lifecycle;
        //    }
        //    lifecycle++;
        //    // Otherwise a new generation
        //}
        //else
        if (!population.TargetReached())
        {
            population.Live();
            population.CalculateFitness();
            population.NaturalSelection();
            population.Reproduction();
            hostRB.velocity = population.GetMaxFitness().velocity;
        }
	}
}
