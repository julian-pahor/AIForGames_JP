using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public float health = 5;

    public float speed = 3;

    private Vector3 movement;

    private Rigidbody2D rb;

    public GameObject bullet;

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
        
        if( Input.GetKeyDown(KeyCode.Mouse0)) //Attack
        {
            Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            Vector3 dir = (mousePos - gameObject.transform.position);
            dir.Normalize();
            Vector3 bSpawn = this.transform.position + dir * 1.7f;
            GameObject go = Instantiate(bullet, bSpawn, Quaternion.identity);
            go.GetComponent<Bullet>().SetBullet(dir, 70);
        }

        if(health <= 0)
        {
            Destroy(gameObject);
        }

    }

    public void TakeDamage()
    {
        health--;
    }
}
