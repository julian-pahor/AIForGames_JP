using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss : MonoBehaviour
{
    public GameObject target;

    public float health = 20;
    private float maxHealth;

    public float decisionCooldown = 5;
    private float decisionTime = 0;

    public float summonCooldown = 20;
    private float summonTime = 0;
    private bool summonUp = false;

    public Decision tree;
    

    // Start is called before the first frame update
    void Start()
    {
        decisionTime = decisionCooldown;
        maxHealth = health;
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
        if(maxHealth / 2 <= health)
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
        summonUp = false;
    }

    
    
}
