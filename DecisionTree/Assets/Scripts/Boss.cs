using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss : MonoBehaviour
{
    public GameObject target;

    public GameObject bullet;

    public GameObject summons;
    public float maxSummons = 3;

    public GameObject meleeAttack;

    public float health = 20;
    private float maxHealth;

    public float decisionCooldown = 5;
    private float decisionTime = 0;

    public float summonCooldown = 20;
    private float summonTime = 0;
    private bool summonUp = false;

    public Decision tree;

    private Rigidbody2D rb;

    // Start is called before the first frame update
    void Start()
    {
        decisionTime = decisionCooldown;
        maxHealth = health;

        rb = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        
        transform.Rotate(0,0,50*Time.deltaTime);

        decisionTime -= Time.deltaTime;


        if (!summonUp)
        {
            summonTime -= Time.deltaTime;
        }

        if (summonTime <= 0)
        {
            summonUp = true;
            summonTime = summonCooldown;
        }

        
        if(decisionTime <= 0)
        {
            Decide();
            decisionTime = decisionCooldown;
        }

        if(health <= 0)
        {
            Destroy(gameObject);
        }

        if (rb.velocity.magnitude > 0)
        {
            rb.AddForce(-rb.velocity * 0.4f);
        }

    }

    public bool CheckSummon()
    {
        return summonUp;
    }

    private void Decide()
    {
        tree.MakeDecision();
    }

    public bool HealthCheck()
    {
        if(health <= maxHealth / 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public void SummonAction()
    {
        for(int i = 0; i < maxSummons; i++)
        {
            GameObject minion = Instantiate(summons, new Vector3(Random.Range(this.transform.position.x - 2, this.transform.position.x + 2), Random.Range(this.transform.position.y - 2, this.transform.position.y + 2), 0), Quaternion.identity);
            minion.GetComponent<Minion>().SetTarget(target);
            minion = null;
        }
        
        summonUp = false;
    }

    public void  RushAction()
    {
        Vector3 movement = (this.transform.position - target.transform.position).normalized;

        rb.AddForce(-movement * 65, ForceMode2D.Impulse);
    }

    public void MeleeAction(bool rage)
    {
        if(rage)
        {
            Vector3 movement = (target.transform.position - this.transform.position).normalized;
            Vector3 bSpawn = this.transform.position + movement * 1.5f;
            GameObject go = Instantiate(meleeAttack, bSpawn, Quaternion.identity);
        }
        else
        {
            //Couldn't figure out prefab rotation to have melee playout towards player
            Vector3 movement = (target.transform.position - this.transform.position).normalized;
            Vector3 bSpawn = this.transform.position + movement * 1.5f;
            GameObject go = Instantiate(meleeAttack, bSpawn, Quaternion.identity);

        }
    }

    public void RangedAction(bool rage)
    {
        if(rage)
        {

            Vector3 movement = (target.transform.position - this.transform.position).normalized;
            Vector3 bSpawn = this.transform.position + movement * 2f;
            GameObject go = Instantiate(bullet, bSpawn, Quaternion.identity);
            go.GetComponent<Bullet>().SetBullet(movement, 50);
           
        }
        else
        {
            Vector3 movement = (target.transform.position - this.transform.position).normalized;
            Vector3 bSpawn = this.transform.position + movement * 2f;
            GameObject go = Instantiate(bullet, bSpawn, Quaternion.identity);
            go.GetComponent<Bullet>().SetBullet(movement, 30);
        }
    }

    public void TakeDamage()
    {
        health--;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "Player")
        {
            collision.gameObject.GetComponent<Player>().TakeDamage();
        }
    }






}
