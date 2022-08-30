using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    private Vector3 velocity;
    private float power;
    private Rigidbody2D rb;

    private float lifeTimer = 5;
    // Start is called before the first frame update

    public void SetBullet(Vector3 vel, float pow)
    {
        velocity = vel;
        power = pow;

    }

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        Shoot();
    }
    private void Shoot()
    {
        rb.AddForce(velocity * power, ForceMode2D.Impulse);
    }
    // Update is called once per frame
    void Update()
    {
        lifeTimer -= Time.deltaTime;
        if(lifeTimer < 0)
        {
            Destroy(this.gameObject);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "Boss")
        {
            collision.gameObject.GetComponent<Boss>().TakeDamage();
        }
        else if(collision.gameObject.tag ==  "Player")
        {
            collision.gameObject.GetComponent<Player>().TakeDamage();
        }

        Destroy(this.gameObject);
    }
}
