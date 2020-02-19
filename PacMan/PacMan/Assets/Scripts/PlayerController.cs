/* PlayerController.cs
 * by Deepti Ramani
 * 01/06/2019
 * This is an implementation of pac-man's controllers, esentially storing where the player wants to go then checking at intersections if it can, followed by either continuing to move in a direction, turing, or stopping
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    // current and next moving directions
    Vector2 CurrDirection = Vector2.zero;
    Vector2 NextDirection = Vector2.zero;

    //next tile to move to
    public Vector3 Destination = Vector3.zero;

    //base speed
    public float Speed = 0.2f;

    Rigidbody2D myRb;
    Animator myAnim;

    // Start is called before the first frame update
    void Start()
    {
        myRb = GetComponent<Rigidbody2D>();
        myAnim = GetComponent<Animator>();
        Destination = transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        switch(GameManager.gameState)
        {
            case GameManager.GameState.Game:
                ReadInputAndMove();
                break;
        }
    }

    //figure out what to do with input and move pac-man if able
    void ReadInputAndMove()
    {
        //set according to desired controller sensitivity
        float sensitivity = 0.1f;
        //check for input and set desired direction
        if(Input.GetAxis("Horizontal") < -sensitivity)
        {
            NextDirection = new Vector2(-1, 0);
        }
        else if(Input.GetAxis("Horizontal") > sensitivity)
        {
            NextDirection = new Vector2(1, 0);
        }
        if(Input.GetAxis("Vertical") < -sensitivity)
        {
            NextDirection = new Vector2(0, -1);
        }
        else if(Input.GetAxis("Vertical") > sensitivity)
        {
            NextDirection = new Vector2(0, 1);
        }

        //check if pac-man is in the center of a tile then check if you change movement
        if(Vector2.Distance(Destination, transform.position) < 0.0001f)
        {
            //check if we can go where the player wants to
            if(isValidDirection(NextDirection))
            {
                transform.position = Destination;
                Destination = (Vector2)transform.position + NextDirection;
                CurrDirection = NextDirection;
                ChangeMovingState();
            }
            //check if pac-man can continue on its current path
            else if(isValidDirection(CurrDirection))
            {
                transform.position = Destination;
                Destination = (Vector2)transform.position + CurrDirection;
                ChangeMovingState();
            }
            //stop moving
            else
            {
                ChangeIdleState();
            }
        }

        //move closer to destination if possible
        Vector2 p = Vector2.MoveTowards(transform.position, Destination, Speed);

        //change pos
        myRb.MovePosition(p);

    }

    //return whether pac-man can move in the given direction
    bool isValidDirection(Vector2 direction)
    {
        //draw a line from the next tile over (+ a little) and check if the maze is in the way
        Vector2 pos = transform.position;
        direction += direction * 0.55f;
        //bit shift the index of the layermask to only check layer 8 (maze)
        int layerMask = 1 << 8;
        RaycastHit2D hit = Physics2D.Linecast(pos + direction, pos, layerMask);
        return hit.collider == null;
    }

    //change idle animations
    void ChangeIdleState()
    {
        if(CurrDirection.x > 0)
        {
            //right idle
            myAnim.SetInteger("State", 1);
        }
        else if(CurrDirection.x < 0)
        {
            //left idle
            myAnim.SetInteger("State", 2);
        }

        if(CurrDirection.y > 0)
        {
            //up idle
            myAnim.SetInteger("State", 3);
        }
        else if(CurrDirection.y < 0)
        {
            //down idle
            myAnim.SetInteger("State", 4);
        }
    }

    //change moving animations
    void ChangeMovingState()
    {
        if (CurrDirection.x > 0)
        {
            //right idle
            myAnim.SetInteger("State", 5);
        }
        else if (CurrDirection.x < 0)
        {
            //left idle
            myAnim.SetInteger("State", 6);
        }

        if (CurrDirection.y > 0)
        {
            //up idle
            myAnim.SetInteger("State", 7);
        }
        else if (CurrDirection.y < 0)
        {
            //down idle
            myAnim.SetInteger("State", 8);
        }
    }
}
