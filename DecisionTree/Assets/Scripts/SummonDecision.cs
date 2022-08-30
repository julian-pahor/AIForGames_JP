using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SummonDecision : Decision
{
    public Boss boss;

    public override void MakeDecision()
    {
        Debug.Log("SummonDecision");
        boss.SummonAction();
    }
}
