using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Minion : MonoBehaviour
{
    public float speed = 5f;

    private GameObject target;

    private Rigidbody2D rb;

    private Vector3 movement;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    public void SetTarget(GameObject go)
    {
        target = go;
    }

    // Update is called once per frame
    void Update()
    {
        transform.Rotate(0, 0, 70 * Time.deltaTime);
        movement = (this.transform.position - target.transform.position).normalized;

        rb.AddForce(-movement * speed);

        if(rb.velocity.magnitude > 0)
        {
            rb.AddForce(-rb.velocity * 0.2f);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "Player")
        {
            collision.gameObject.GetComponent<Player>().TakeDamage();
            Destroy(this.gameObject);
        }

        if(collision.gameObject.tag == "Wall")
        {
            Destroy(this.gameObject);
        }
    }
}
