/* GameManager.cs
 * by Deepti Ramani
 * 01/06/2020
 * This is a singleton class that stores global game data like lives, level number, score, gamestates, etc.
 */


using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

    //link to special game objects
    private GameObject PacMan;
    private static TextMesh ScoreText;
    public float SpeedPerLevel = 0.025f;
    
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
        ScoreText = GameObject.Find("ScoreText").GetComponent<TextMesh>();
        //TODO set this to init once you have a start screen made
        gameState = GameState.Game;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public static void UpdateScore(int amount)
    {
        //add amount to score
        Score += amount;

        //update score text
        ScoreText.text = Score.ToString();
    }
}
