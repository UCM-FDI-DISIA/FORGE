using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityCodeGen;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Windows;

[Generator]
public class LuaWriter : MonoBehaviour, ICodeGenerator
{
    Dictionary<string, GameObject> savedObjects = new Dictionary<string, GameObject> ();
    string data = "";
    int i=0;

    //Saves relevant data from all scenes except for bootscene using playerprefs
    public void SaveAll()
    {

        //Aqui se escribe "local scenes = {" en el archivo de lua
        data += "local scenes = {\n";
        i++;
        foreach (Scene scene in SceneManager.GetAllScenes())
        {
            Tabulate();
            // "mystring" + var + ""
            // string.format("{0}", var), 
           data += scene.name+" = {\n";
           i++;
           foreach (GameObject obj in scene.GetRootGameObjects())
           {
                Tabulate();
                //"{*obj} = {"
                //Sacar componentes del padre components = 
                SaveGameObjectAndChildren(obj);
                //"}"
           }
            i--;
            Tabulate();
           data += "},\n";
           
        }
        //Se quita la ultima coma
        data = data.Remove(data.Length-2);
        Tabulate();
        data += "\n";
        //Aqui se cierra con una llave "}"
        data += "}";
        i--;
        data += "\nreturn prefabs, scenes";
        //y se escribe al final del archivo "return prefabs, scenes"
    }

    //Adds the game object and its children to be saved recursively
    private void SaveGameObjectAndChildren(GameObject obj)
    {
        data += "\n";
        i++;
        data += obj.name + "= {\n";
        Tabulate();
        data += "components = {\n";
        foreach (Component component in obj.GetComponents(typeof(Component)))
        {
            Tabulate();
            data += component.GetType() + "= {";
            data += "\n";
            Tabulate();
            data += "},\n";
        }
        data = data.Remove(data.Length-2);
        data += "\n}\n";
        for (int i = 0; i < obj.transform.childCount; i++)
        {
            Tabulate();
            SaveGameObjectAndChildren(obj.transform.GetChild(i).gameObject);
        }
        i--;
        savedObjects.Add(obj.name, obj);
        data += "}\n";
    }

    public void Tabulate()
    {
        for (int n = 0; n < i; n++)
        {
            data += "\t";
        }
    }

    public void Execute(GeneratorContext context)
    {
        SaveAll();
        data = data.Replace("UnityEngine.", "");
        context.AddCode("luatest.lua", data);
    }
}
