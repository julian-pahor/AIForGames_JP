using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ABCDecisionSummon : Decision
{
    public Decision A;
    public Decision B;
    public Decision C;

    public Boss boss;

    public override void MakeDecision()
    {
        if(boss.CheckSummon())
        {
            A.MakeDecision();
        }
        else
        {
            if(Random.Range(0, 100) <= 40)
            {
                B.MakeDecision();
            }
            else
            {
                C.MakeDecision();
            }
        }
    }
}
