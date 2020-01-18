using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScroller : MonoBehaviour
{
    private Vector3 newPos;
    public float speed = 7.0f;

    public GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        Player = GameObject.Find("Player");
        newPos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {

        if(Player.transform.position.x > 0)
        {
            newPos = Vector3.MoveTowards(transform.position, Player.transform.position, speed * Time.deltaTime);
            newPos.y = transform.position.y;
            newPos.z = transform.position.z;
        }

        transform.position = newPos;
    }
}
