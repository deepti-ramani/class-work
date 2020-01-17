using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    public int damage = 1;
    public int points = 1;
    public int health = 3;
    
    public float minDistToFollow = 3.0f;
    public float maxPacingDistance = 1.0f;
    private float distanceTravelled = 0.0f;

    private int direction = 1;
    public float speed = 3.0f;

    public Color attackColor = Color.red;
    public Color idleColor = new Color(255, 127, 127);

    public GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        gameObject.GetComponent<SpriteRenderer>().color = idleColor;
        Player = GameObject.Find("Player");       
    }

    // Update is called once per frame
    void Update()
    {
        float distanceFromPlayer = Mathf.Abs(Vector2.Distance(Player.transform.position, transform.position));
        if(distanceFromPlayer < minDistToFollow)
        {
            gameObject.GetComponent<SpriteRenderer>().color = attackColor;
            FollowPlayer();
        }
        else
        {
            gameObject.GetComponent<SpriteRenderer>().color = idleColor;
            MoveBackAndForth();
        }

        if (health <= 0)
        {
            Player.GetComponent<Player>().UpdateScore(points);
            Destroy(gameObject);
        }
    }

    //back and forth movement
    void MoveBackAndForth()
    {
        Vector2 newPos = transform.position;
        if(distanceTravelled < maxPacingDistance)
        {
            newPos.x += speed * direction * Time.deltaTime;
            distanceTravelled += speed * Time.deltaTime;
        }
        else
        {
            distanceTravelled = 0.0f;
            direction *= -1;
        }
        transform.position = newPos;
    }

    //following movement
    void FollowPlayer()
    {
        Vector2 newPos = Vector2.MoveTowards(transform.position, Player.transform.position, speed * 1.5f * Time.deltaTime);
        transform.position = newPos;
    }

    //take damage from player
    public void Damage(int damage)
    {
        //update health
        health -= damage;
    }

    //deal damage to player
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.transform.gameObject.name == "Player" && !Player.GetComponent<Player>().isAttacking)  //player is temp invulnerable while attacking
        {
            Player.GetComponent<Player>().UpdateHealth(damage);
        }
    }
}
