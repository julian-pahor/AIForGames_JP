using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ABDecisionDistance : Decision
{
    

    public Decision A;
    public Decision B;

    public float m_distance;

    public GameObject m_target;
    public GameObject m_parent;

    
    //Could not figure out how to pass in a custom comparitor method into constructor

    //public ABDecisionDistance(Decision first, Decision second, float distance, GameObject target)
    //{
    //    A = first;
    //    B = second;
    //    m_distance = distance;
    //    m_target = target;
    //}

    

    public override void MakeDecision()
    {
        if(Vector3.Distance(m_target.transform.position, m_parent.transform.position) < m_distance)
        {
            A.MakeDecision();
        }
        else
        {
            B.MakeDecision();
        }
    }
}
