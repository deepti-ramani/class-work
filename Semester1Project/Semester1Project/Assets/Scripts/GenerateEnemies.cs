using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenerateEnemies : MonoBehaviour
{
    public GameObject BasicEnemy;
    public GameObject MediumEnemy;
    public GameObject HardEnemy;

    public GameObject Player;

    private float spawnX;
    private Vector3 spawnPos;

    private float timeUntilEnemyGenerates;
    private float timeRemaining;
    public bool stopGenerating = false;

    private float enemyToSpawn;

    // Start is called before the first frame update
    void Start()
    {
        //first enemy is hardcoded
        Instantiate(BasicEnemy, new Vector3(5, -4.5f, 0), transform.rotation);

        //timing of enemies is random
        timeUntilEnemyGenerates = Random.Range(4.0f, 7.0f);
        timeRemaining = timeUntilEnemyGenerates;

        //difficulty is random
        enemyToSpawn = Random.Range(0.0f, 1.0f);

        Player = GameObject.Find("Player");

    }

    // Update is called once per frame
    void Update()
    {      
        if(transform.position.x >= 43)
        {
            stopGenerating = true;
        }

        //if the countdown is reached
        if (timeRemaining <= 0.0f && !stopGenerating)
        {
            //generate an enemy a random distance away from the player
            spawnX = Player.transform.position.x + Random.Range(5.0f, 8.0f);
            spawnPos = new Vector3(spawnX, -1.0f, 0.0f);

            //random enemy
            if (enemyToSpawn < 0.45f)
            {
                Instantiate(BasicEnemy, spawnPos, transform.rotation);
            }
            else if (enemyToSpawn < 0.75f)
            {
                Instantiate(MediumEnemy, spawnPos, transform.rotation);
            }
            else
            {
                Instantiate(HardEnemy, spawnPos, transform.rotation);
            }

            //reset random variables
            timeRemaining = Random.Range(4.0f, 7.0f);
            enemyToSpawn = Random.Range(0.0f, 1.0f);
        }
        //increment time
        timeRemaining -= Time.deltaTime;
    }
}
