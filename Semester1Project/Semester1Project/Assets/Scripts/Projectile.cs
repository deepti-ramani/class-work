using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
    public float speed = 5.0f;
    public int damage = 1;

    public GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        Player = GameObject.Find("Player");
    }

    // Update is called once per frame
    void Update()
    {
        Vector2 newPos = Vector2.MoveTowards(transform.position, Player.transform.position, speed * Time.deltaTime);
        transform.position = newPos;
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
