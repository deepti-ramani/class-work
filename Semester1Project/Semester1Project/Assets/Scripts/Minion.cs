using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Minion : MonoBehaviour
{
    public int damage = 1;
    public int points = 1;
    public int health = 5;

    public float speed = 3.0f;

    public GameObject BossEnemy;
    public GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        Player = GameObject.Find("Player");
        BossEnemy = GameObject.Find("BossEnemy");
    }

    // Update is called once per frame
    void Update()
    {
        FollowPlayer();

        if (health <= 0)
        {
            BossEnemy.GetComponent<BossEnemy>().DecrementMinionCount();
            Destroy(gameObject);
        }
    }

    //following movement
    void FollowPlayer()
    {
        Vector2 newPos = Vector2.MoveTowards(transform.position, Player.transform.position, speed * Time.deltaTime);
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
