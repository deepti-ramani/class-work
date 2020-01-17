using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
    //"stats"
    public int damage = 2;
    public float speed = 5.0f;
    public int health = 10;
    private int score = 0;

    //invulnerable while attacking (in intervals)
    public bool isAttacking = false;
    public bool isCooldown = false;
    public float maxAttackCooldown = 2.5f;
    public float maxAttackDuration = 1.5f;
    private float currAttackTime;

    public Color idleColor = Color.white;
    public Color attackColor = new Color(255, 200, 150);
    public Color cooldownColor = new Color(255, 225, 200);

    //update ui
    public TextMesh HealthText;
    public TextMesh ScoreText;

    // Start is called before the first frame update
    void Start()
    {
        currAttackTime = maxAttackCooldown;
        HealthText = GameObject.Find("HealthText").GetComponent<TextMesh>();
        ScoreText = GameObject.Find("ScoreText").GetComponent<TextMesh>();
    }

    // Update is called once per frame
    void Update()
    {
        //user input
        ReadInputAndMove();

        //check atttack intervals for invulnerability and cooldown
        if (isCooldown)
        {
            //check if attack has finished
            if (currAttackTime <= maxAttackDuration && isAttacking)
            {
                gameObject.GetComponent<SpriteRenderer>().color = cooldownColor;
                speed /= 2.25f;
                isAttacking = false;
            }
            //check if cooldown has finished
            else if (currAttackTime <= 0.0f)
            {
                gameObject.GetComponent<SpriteRenderer>().color = idleColor;
                currAttackTime = maxAttackCooldown;
                isCooldown = false;
            }

            //keep counting down
            currAttackTime -= Time.deltaTime;
        }

        //lose condition (run out of health)
        if(health <= 0)
        {
            //lose screen
            SceneManager.LoadScene("LoseScreen");
            Destroy(gameObject);
        }
    }

    void ReadInputAndMove()
    {
        //move left or right
        Vector2 newPos = transform.position;
        if(Input.GetAxis("Horizontal") > 0)
        {
            newPos.x += speed * Time.deltaTime;
        }
        else if (Input.GetAxis("Horizontal") < 0)
        {
            newPos.x -= speed * Time.deltaTime;
        }
        if (Input.GetAxis("Vertical") > 0)
        {
            newPos.y += 1.3f * speed * Time.deltaTime;
        }
        transform.position = newPos;

        //attack
        if(Input.GetKey(KeyCode.Space) && !isAttacking && !isCooldown)
        {
            isAttacking = true;
            isCooldown = true;
            Attack(); 
        }
    }

    void Attack()
    {
        gameObject.GetComponent<SpriteRenderer>().color = attackColor;
        //gain speed boost
        speed *= 2.25f;
    }


    //UI updates
    public void UpdateHealth(int damage)
    {
        //update health
        health -= damage;
        //write to ui
        HealthText.text = "Health: " + health;
    }

    public void UpdateScore(int points)
    {
        score += points;
        ScoreText.text = "Score: " + score;
    }

    //deal damage to enemy
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(isAttacking && collision.transform.gameObject.tag == "Enemy")
        {
            collision.transform.gameObject.GetComponent<EnemyController>().Damage(damage);
        }
        else if(isAttacking && collision.transform.gameObject.tag == "Boss")
        {
            if(!collision.transform.gameObject.GetComponent<BossEnemy>().isInvincible)
            {
                collision.transform.gameObject.GetComponent<BossEnemy>().Damage(damage);
            }
        }
        else if(isAttacking && collision.transform.gameObject.tag == "Minion")
        {
            collision.transform.gameObject.GetComponent<Minion>().Damage(damage);
        }
        else if(collision.transform.gameObject.name == "Goal")
        {
            //victory "screen"
            SceneManager.LoadScene("WinScreen");
        }
    }
}
