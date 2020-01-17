using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIScroller : MonoBehaviour
{
    private Vector3 newPos;
    public float xOffset;
    public float yOffset;

    public GameObject Camera;

    // Start is called before the first frame update
    void Start()
    {
        Camera = GameObject.Find("Main Camera");
    }

    // Update is called once per frame
    void Update()
    {
        newPos = Camera.transform.position;
        newPos.x += xOffset;
        newPos.y += yOffset;
        newPos.z = transform.position.z;

        transform.position = newPos;
    }
}
