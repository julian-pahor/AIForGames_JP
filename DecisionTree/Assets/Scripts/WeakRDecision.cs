using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeakRDecision : Decision
{
    public Boss boss;
    public override void MakeDecision()
    {
        Debug.Log("WeakRDecision");
        boss.RangedAction(false);
    }

}
