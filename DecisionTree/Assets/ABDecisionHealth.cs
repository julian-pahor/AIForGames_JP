using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ABDecisionHealth : Decision
{
    public Decision A;
    public Decision B;

    public Boss boss;

    public override void MakeDecision()
    {
        if(boss.HealthCheck())
        {
            A.MakeDecision();
        }
        else
        {
            B.MakeDecision();
        }
    }

    
}
