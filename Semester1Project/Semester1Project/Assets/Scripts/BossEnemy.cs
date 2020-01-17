using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossEnemy : MonoBehaviour
{
    public int physdamage = 5;
    public int projdamage = 1;
    public int points = 30;
    public int health = 13;
    public float speed = 2.0f;

    public bool isInvincible = false;
    private bool isInStage3 = false;

    public int maxMinionCount = 5;
    private int currMinionCount;
    public GameObject Minion;

    public float timeUntilProjectile = 1.5f;
    private float timeRemaining = 1.5f;
    public GameObject Projectile;

    public Color attackColor = Color.red;
    public Color idleColor = new Color(255, 127, 127);
    public Color invincibleColor = new Color(135, 68, 68);

    public GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        gameObject.GetComponent<SpriteRenderer>().color = idleColor;
        currMinionCount = maxMinionCount;
        timeRemaining = timeUntilProjectile;
        Player = GameObject.Find("Player");
    }

    // Update is called once per frame
    void Update()
    {   
        //stage 1
        if (health >= 10.0f)
        {
            Stage1();
        }
        //stage 2
        else if (health >= 3.0f)
        {
            Stage2();
        }
        //stage 3
        else if (!isInStage3)
        {
            //can only enter stage 3 once
            isInStage3 = true;
            Stage3();
        }

        //check if minions are all killed
        if(currMinionCount <= 0)
        {
            isInvincible = false;
            Stage2();
        }

        //check if it dies
        if(health <= 0)
        {
            Player.GetComponent<Player>().UpdateScore(points);
            Destroy(gameObject);
        }

        //increment time for projectiles
        timeRemaining -= Time.deltaTime;

    }
    void Stage1()
    {
        float distanceFromPlayer = Mathf.Abs(Vector2.Distance(Player.transform.position, transform.position));

        //if player is too close shoot & move back
        if (distanceFromPlayer < 10.0f)
        {
            //create projectiles
            if (timeRemaining <= 0)
            {
                timeRemaining = timeUntilProjectile;
                Instantiate(Projectile, new Vector3(transform.position.x, -4, 0), transform.rotation);
            }
        }

        if (distanceFromPlayer <= 5.0f)
        {
            //move back
            Vector2 newPos = transform.position;
            newPos.x += speed * Time.deltaTime;
            transform.position = newPos;
        }
    }

    void Stage2()
    {
        //follow player
        gameObject.GetComponent<SpriteRenderer>().color = attackColor;
        Vector2 newPos = Vector2.MoveTowards(transform.position, Player.transform.position, speed * Time.deltaTime);
        newPos.y = -2.75f;
        transform.position = newPos;
    }

    void Stage3()
    { 
        //summon minions
        for (int i = 1; i <= maxMinionCount; i++)
        {
            Instantiate(Minion, new Vector3(transform.position.x - 2 * i, -4.125f, 0), transform.rotation);
        }

        //become invincible until minions are defeated
        isInvincible = true;
        gameObject.GetComponent<SpriteRenderer>().color = invincibleColor;
    }

    public void DecrementMinionCount()
    {
        currMinionCount--;
    }

    public void Damage(int damage)
    {
        health -= damage;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.transform.gameObject.name == "Player" && !Player.GetComponent<Player>().isAttacking)  //player is temp invulnerable while attacking
        {
            Player.GetComponent<Player>().UpdateHealth(physdamage);
        }
    }
}
