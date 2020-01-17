using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointCollectible : MonoBehaviour
{
    public int Points = 10;
    public bool DestroyOnCollide = true;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        GameManager.UpdateScore(Points);
        if(DestroyOnCollide)
        {
            Destroy(gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
