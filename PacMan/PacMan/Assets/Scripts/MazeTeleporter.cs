/* MazeTeleporter.cs
 * by Deepti Ramani
 * 01/06/2020
 * This is a class that will teleport players to a certain posiiton on colision (for the tunnels)
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MazeTeleporter : MonoBehaviour
{
    public Vector2 teleportExit = Vector2.zero;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        collision.gameObject.transform.position = teleportExit;

        if(collision.gameObject.name == "Player")
        {
            collision.gameObject.GetComponent<PlayerController>().Destination = teleportExit;
        }
        if(collision.gameObject.tag == "Ghost")
        {
            collision.gameObject.GetComponent<GhostAI>().Destination = teleportExit;
        }
    }
}
