/* PointCOllectible.cs
 * by Deepti Ramani
 * 01/06/2020
 * This is a class that deals with the dots and power pellets, updates score, and changes the ghost state if necessary
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointCollectible : MonoBehaviour
{
    public int Points = 10;
    public bool DestroyOnCollide = true;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //only players can collect dots/pellets
        if (collision.gameObject.name == "Player")
        {
            GameManager.UpdateScore(Points);
            if (DestroyOnCollide)
            {
                Destroy(gameObject);
                GameManager.instance.dotsEaten++;
            }
            //check if its a power pellet
            if(gameObject.name == "PowerPellet")
            {
                //set ghosts to frightened (if they aren't eaten)
                if (GameObject.Find("Blinky").GetComponent<GhostAI>().ghostState != GhostAI.GhostState.Eaten)
                {
                    GameObject.Find("Blinky").GetComponent<GhostAI>().ChangeState(GhostAI.GhostState.Frightened);
                }
                if (GameObject.Find("Pinky").GetComponent<GhostAI>().ghostState != GhostAI.GhostState.Eaten)
                {
                    GameObject.Find("Pinky").GetComponent<GhostAI>().ChangeState(GhostAI.GhostState.Frightened);
                }
                if (GameObject.Find("Inky").GetComponent<GhostAI>().ghostState != GhostAI.GhostState.Eaten)
                {
                    GameObject.Find("Inky").GetComponent<GhostAI>().ChangeState(GhostAI.GhostState.Frightened);
                }
                if (GameObject.Find("Clyde").GetComponent<GhostAI>().ghostState != GhostAI.GhostState.Eaten)
                {
                    GameObject.Find("Clyde").GetComponent<GhostAI>().ChangeState(GhostAI.GhostState.Frightened);
                }
            }
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
