using AYellowpaper.SerializedCollections;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FORGEComponent : MonoBehaviour
{
    public string componentName;
    [SerializedDictionary("Key","Value")]
    public SerializedDictionary<string,string> values;
}

