using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StrongRDecision : Decision
{
    public Boss boss;
    public override void MakeDecision()
    {
        Debug.Log("StrongRDecision");
    }

}
