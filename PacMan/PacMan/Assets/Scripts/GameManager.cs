/* GameManager.cs
 * by Deepti Ramani
 * 01/06/2020
 * This is a singleton class that stores global game data like lives, level number, score, gamestates, etc.
 */


using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class GameManager : MonoBehaviour
{
    //basic game data
    public static int Level = 0;
    public static int Lives = 3;
    public static int Score = 0;
    
    //global gamestates
    public enum GameState
    {
        Init,
        Game,
        Dead,
        Scores
    }
    public static GameState gameState;

    //player
    public GameObject PacMan;

    //ghosts
    public float SpeedPerLevel = 0.025f;
    public float BaseSpeed = 0.1f;
    public float scareLength;
    private float _timeToCalm;
    public GameObject Blinky;
    public GameObject Pinky;
    public GameObject Inky;
    public GameObject Clyde;

    //UI
    private static TextMesh ScoreText;

    //max = 231
    public int dotsEaten = 0;


    
    //singleton implementation
    private static GameManager _instance;

    public static GameManager instance
    {
        get
        {
            //if instance isn't found, try to find it
            if(_instance == null)
            {
                _instance = GameObject.FindObjectOfType<GameManager>();
                DontDestroyOnLoad(_instance);
            }
            return _instance;
        }
    }

    //runs even before the start function
    private void Awake()
    {
        //set the singleton _instance
        if(_instance == null)
        {
            _instance = this;
            DontDestroyOnLoad(_instance);
        }
        else if(_instance != this)
        {
            Destroy(this);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        AssignGhosts();

        ScoreText = GameObject.Find("ScoreText").GetComponent<TextMesh>();
        //TODO set this to init once you have a start screen made
        gameState = GameState.Game;
    }

    // Update is called once per frame
    void Update()
    {
        if(dotsEaten >= 245)
        {
            //quit game when we win
            UnityEditor.EditorApplication.isPlaying = false;
        }
    }

    public static void UpdateScore(int amount)
    {
        //add amount to score
        Score += amount;

        //update score text
        ScoreText.text = Score.ToString();
    }

    //assign and initialize ghosts/pacman
    void AssignGhosts()
    {
        PacMan = GameObject.Find("Player");

        Blinky = GameObject.Find("Blinky");
        Pinky = GameObject.Find("Pinky");
        Inky = GameObject.Find("Inky");
        Clyde = GameObject.Find("Clyde");

        if(Blinky == null || Pinky == null || Inky == null || Clyde == null)
        {
            Debug.Log("One of the ghosts is null.");
        }

        if(PacMan == null)
        {
            Debug.Log("Pacman is null.");
        }
    }
}
