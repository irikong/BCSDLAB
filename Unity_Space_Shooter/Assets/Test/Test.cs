using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    int a = 10;
    float b = 0.1f;
    string c = "Unity";
    bool d = false;

    // Start is called before the first frame update
    void Start()
    {
        print("Hello World");
        Add();
    }

    void Add()
    {
        int result = 10 + 30;
        print(result);
    }

    // Update is called once per frame
    void Update()
    {
        print("Update!!!!!");
    }
}
