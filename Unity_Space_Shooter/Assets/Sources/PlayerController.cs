using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    float speed = 5;
    float tilt = 5;

    void Start()
    {
        
    }

    void FixedUpdate()
    {
        float dirX = Input.GetAxis("Horizontal");
        float dirY = Input.GetAxis("Vertical");

        Vector3 movement = new Vector3(dirX, 0, dirY); // 이동방향

        GetComponent<Rigidbody>().velocity = movement * speed;
        GetComponent<Rigidbody>().rotation = Quaternion.Euler(0, 0, GetComponent<Rigidbody>().velocity.x * -tilt);
    }
}
