using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeakMDecision : Decision
{

    public Boss boss;
    public override void MakeDecision()
    {
        Debug.Log("WeakMDecision");
    }
}
