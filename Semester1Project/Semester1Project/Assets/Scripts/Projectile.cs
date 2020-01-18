using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
    public float speed = 5.0f;
    public int damage = 1;

    public float timeUntilDewpawn = 2.0f;
    public float timeRemaining;

    public GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        timeRemaining = timeUntilDewpawn;
        Player = GameObject.Find("Player");
    }

    // Update is called once per frame
    void Update()
    {
        Vector2 newPos = Vector2.MoveTowards(transform.position, Player.transform.position, speed * Time.deltaTime);
        newPos.y = transform.position.y;
        transform.position = newPos;

        timeRemaining -= Time.deltaTime;
        if(timeRemaining <= 0)
        {
            Destroy(gameObject);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.transform.gameObject.name == "Player" && !Player.GetComponent<Player>().isAttacking)
        {
            Player.GetComponent<Player>().UpdateHealth(damage);
        }
        Destroy(gameObject);
    }
}
