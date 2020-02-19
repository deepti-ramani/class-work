/* GhostAI.cs
 * by Deepti Ramani
 * 01/28/2020
 * This is a class that contains functions for the ghosts' animations, states, and movement patterns
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GhostAI : MonoBehaviour
{
    //which ghost is it
    public enum GhostType
    {
        Blinky,
        Pinky,
        Inky,
        Clyde
    }
    public GhostType ghostType = GhostType.Blinky;

    //what state is the ghost in
    public enum GhostState
    {
        Chase,
        Scatter,
        Frightened,
        Eaten
    }
    public GhostState ghostState = GhostState.Scatter;

    //how many times has it chased (currentphase) & for how long (leveltimer)
    public int currentPhase = 0;
    public float levelTimer = 0;
    //array of phase times from 0 to 6 (odd = chase, even = scatter)
    public float[] ChaseTime = { 7, 27, 34, 54, 59, 79, 83 };

    public float FrightenedTime = 7.0f;
    public float FrightenedCooldown = 5.0f;
    public float frightenedTimer = 0;

    //movement
    public float speed = 0.1f;
    public Vector2 Direction = new Vector2(-1, 0);
    public Vector2 Destination = Vector2.zero;
    public Vector2 ChaseTarget = Vector2.zero;
    public Vector2 ScatterTarget = new Vector2(11, 15);
    public Vector2 EatenTarget = new Vector2(-0.5f, 4.0f);

    private bool Done = true;
    private bool noUpTurn = false;
    private int countUpTurns = 0;

    //components
    private Rigidbody2D myRb;
    private Animator myAnimator;

    //game objects
    public GameObject PacMan;

    // Awake is called before Start()
    private void Awake()
    {
        PacMan = GameObject.Find("Player");
        myRb = gameObject.GetComponent<Rigidbody2D>();
        myAnimator = gameObject.GetComponent<Animator>();
    }

    // Start is called before the first frame update
    void Start()
    {
        CalculateTarget();
    }

    // Update is called once per frame
    void Update()
    {
        //increment chase/scatter timer
        levelTimer += Time.deltaTime;
        //check if current phase is within array of phase times
        if(currentPhase < ChaseTime.Length)
        {
            //check if timer has exceeded max chase time
            if(levelTimer > ChaseTime[currentPhase])
            {
                //go to next phase
                currentPhase++;
                //make sure its not frightened/eaten
                if((ghostState == GhostState.Chase || ghostState == GhostState.Scatter))
                {
                    //if odd, chase
                    if(currentPhase % 2 == 1)
                    {
                        ChangeState(GhostState.Chase);
                    }
                    //if even, scatter
                    else
                    {
                        ChangeState(GhostState.Scatter);
                    }
                }
            }
        }
        //after 7 phases, ghost is permanently on chase (if not frightened or eaten).
        else
        {
            //make sure its not frightened/eaten
            if(ghostState == GhostState.Chase || ghostState == GhostState.Scatter)
            {
                ChangeState(GhostState.Chase);
            }
        }

        //increment frightened timer
        if (ghostState == GhostState.Frightened)
        {
            frightenedTimer += Time.deltaTime;
            //chase or scatter
            if (frightenedTimer > FrightenedTime)
            {
                Calm();
                frightenedTimer = 0;
            }
            //play "flickering" animation to signify end of frightened phase
            else if (frightenedTimer > FrightenedCooldown)
            {
                myAnimator.SetInteger("State", 6);
            }
        }

        //after deciding what state its in, move accordingly
        if (Done)
        {
            Done = false;
            switch(ghostState)
            {
                //find chase target and move
                case GhostState.Chase:
                    CalculateTarget();
                    ChooseDirection(ChaseTarget);
                    break;

                //find scatter target & move
                case GhostState.Scatter:
                    ChooseDirection(ScatterTarget);
                    break;

                //move in a random direction
                case GhostState.Frightened:
                    RandValidDir();
                    break;

                //go back to inital pos, then continue
                case GhostState.Eaten:
                    speed = GameManager.instance.BaseSpeed * 1.1f;
                    ChooseDirection(EatenTarget);
                    if(Vector2.Distance(EatenTarget, (Vector2)transform.position) < 1.0f)
                    {
                        Calm();
                        speed = GameManager.instance.BaseSpeed;
                    }
                    break;
            }
        }
    }

    //choose chase target
    void CalculateTarget()
    {
        switch (ghostType)
        {
            case GhostType.Blinky:
                ChaseTarget = PacMan.transform.position;
                break;

            case GhostType.Pinky:
                ChaseTarget = PacMan.transform.position;
                break;

            case GhostType.Inky:
                ChaseTarget = PacMan.transform.position;
                break;

            case GhostType.Clyde:
                ChaseTarget = PacMan.transform.position;
                break;
        }
    }

    //choose optimal path for getting to a target
    void ChooseDirection(Vector2 target)
    {
        //can keep moving in the same direction or turn left/right
        Vector2 Perpendicular = new Vector2(Direction.y, Direction.x);
        var possibleDirections = new List<Vector2> { Direction, Perpendicular, -Perpendicular };
        int closest = 0;
        float distanceToTarget = float.MaxValue;

        //remove some possibile movement options if we can't move up (specific areas)
        if (noUpTurn)
        {
            for (int i = 0; i < possibleDirections.Count; i++)
            {
                if (possibleDirections[i].y > 0)
                {
                    possibleDirections.RemoveAt(i);
                }
            }
        }

        //iterate through all movement options and check if they are valid (no maze in the way)
        for(int i = 0; i < possibleDirections.Count; i++)
        {
            if(IsValidDirection(possibleDirections[i]))
            {
                //if two paths are equally close, check conditions
                if (distanceToTarget == Vector2.Distance((Vector2)transform.position + possibleDirections[i], target))
                {
                    //going upwards has highest priority
                    if(possibleDirections[i].y > 0)
                    {
                        closest = i;
                    }
                    //going down & left has next highest priority
                    else if (possibleDirections[i].x < 0 && possibleDirections[closest].y <= 0)
                    {
                        closest = i;
                    }
                    //going down & right has the lowest priority
                    else if (possibleDirections[i].x > 0 && possibleDirections[closest].y <= 0 && possibleDirections[closest].x >= 0)
                    {
                        closest = i;
                    }
                }
                //if the current path is longer than the possible path, set the current path as the closest
                if(distanceToTarget > Vector2.Distance((Vector2)transform.position + possibleDirections[i], target))
                {
                    closest = i;
                    distanceToTarget = Vector2.Distance((Vector2)transform.position + possibleDirections[i], target);
                }
            }
        }
       
        //set the ghost's path to the optimal movement option
        Direction = possibleDirections[closest];
        Destination = (Vector2)transform.position + Direction;
        Destination.x = Mathf.Round(Destination.x);
        Destination.y = Mathf.Round(Destination.y);

        SelectAnimation();
        StartCoroutine(Move());
    }

    //select a random valid direction (current or perpendicular) and move (for frightened)
    void RandValidDir()
    {
        //list possible directions
        Vector2 Perpendicular = new Vector2(Direction.y, Direction.x);
        var possibleDirections = new List<Vector2> { Direction, Perpendicular, -Perpendicular };
        var validDirections = new List<int>();

        //check which of the possible directions are valid
        for(int i = 0; i < possibleDirections.Count; i++)
        {
            if(IsValidDirection(possibleDirections[i]))
            {
                validDirections.Add(i);
            }
        }

        //randomly choose from the valid directions
        int randNum = Random.Range(0, validDirections.Count - 1);
        Direction = possibleDirections[validDirections[randNum]];
        Destination = (Vector2)transform.position + Direction;
        Destination.x = Mathf.Round(Destination.x);
        Destination.y = Mathf.Round(Destination.y);

        //start moving the player
        StartCoroutine(Move());
    }

    //check if the ghost can move w/o running into a wall
    private bool IsValidDirection(Vector2 direction)
    {
        //draw a line to the next tile over (+ a little bit) and check if the wall is in the way
        Vector2 pos = transform.position;
        direction += direction * 0.55f;
        //only check layer 8 (maze)
        int layerMask = 1 << 8;
        RaycastHit2D hit = Physics2D.Linecast(pos + direction, pos, layerMask);
        //return true if it doesn't detect the wall
        return hit.collider == null;
    }

    //move ghost
    IEnumerator Move()
    {

        //while the ghost isn't at its destination, keep moving towards it
        while (Vector2.Distance(transform.position, Destination) > 0.0001)
        {
            Vector2 p = Vector2.MoveTowards(transform.position, Destination, speed);

            myRb.MovePosition(p);

            yield return new WaitForFixedUpdate();
        }

        //when it reaches its destination
        StopAllCoroutines();
        Done = true;
    }

    //decide movement pattern after frightened state ends
    public void Calm()
    {
        if(currentPhase % 2 == 1)
        {
            ChangeState(GhostState.Chase);
        }
        else
        {
            ChangeState(GhostState.Scatter);
        }
    }

    //change state, movement direction, and animation
    public void ChangeState(GhostState newState)
    {
        //change direction when the state changes
        if(ghostState == GhostState.Chase && newState != GhostState.Chase)
        {
            Direction = -Direction;
        }
        if(ghostState == GhostState.Scatter && newState != GhostState.Scatter)
        {
            Direction = -Direction;
        }
        //change animation & update state
        ghostState = newState;
        SelectAnimation();
    }

    //change animation based on ghostState/movement direction
    void SelectAnimation()
    {
        switch(ghostState)
        {            
            case GhostState.Frightened:
                myAnimator.SetInteger("State", 5);
                break;

            case GhostState.Eaten:
                //right
                if (Direction.x > 0)
                {
                    myAnimator.SetInteger("State", 7);
                }
                //left
                else if (Direction.x < 0)
                {
                    myAnimator.SetInteger("State", 8);
                }
                //up
                else if (Direction.y > 0)
                {
                    myAnimator.SetInteger("State", 9);
                }
                //down
                else if (Direction.y < 0)
                {
                    myAnimator.SetInteger("State", 10);
                }
                break;

            //chase and scatter use the default movement animations
            default:
                //right
                if(Direction.x > 0)
                {
                    myAnimator.SetInteger("State", 1);
                }
                //left
                else if(Direction.x < 0)
                {
                    myAnimator.SetInteger("State", 2);
                }
                //up
                else if(Direction.y > 0)
                {
                    myAnimator.SetInteger("State", 3);
                }
                //down
                else if(Direction.y < 0)
                {
                    myAnimator.SetInteger("State", 4);
                }
                break;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.name == "NoUpTurn")
        {
            if (countUpTurns < 2)
            {
                noUpTurn = true;
                countUpTurns++;
            }
        }

        if(collision.gameObject.name == "GhostSlow")
        {
            speed = GameManager.instance.BaseSpeed * 0.5f;
        }

        if(collision.gameObject.name == "Player")
        {
            if(ghostState == GhostState.Frightened)
            {
                ChangeState(GhostState.Eaten);
                frightenedTimer = 0;
            }
            else if(ghostState != GhostState.Eaten)
            {
                Destroy(collision.gameObject);
                UnityEditor.EditorApplication.isPlaying = false;
            }
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if(collision.gameObject.name == "NoUpTurn")
        {
            noUpTurn = false;
        }

        if(collision.gameObject.name == "GhostSlow")
        {
            speed = GameManager.instance.BaseSpeed;
        }
    }
}
