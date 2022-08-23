using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public float health = 5;

    public float speed = 3;

    private Vector3 movement;

    private Vector2 velocityref;
    private Rigidbody2D rb;

    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }
    // Update is called once per frame
    void Update()
    {
        movement.x = Input.GetAxisRaw("Horizontal");
        movement.y = Input.GetAxisRaw("Vertical");

        rb.AddForce(movement * speed);

        if(rb.velocity.magnitude > 0)
        {
            rb.AddForce(-rb.velocity * 0.3f);
        }
        

        if(Input.GetKeyDown(KeyCode.Mouse0)) //Left Click = Meele
        {

        }
        if( Input.GetKeyDown(KeyCode.Mouse1)) //Right Click = Ranged
        {

        }


    }
}
