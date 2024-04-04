using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;

//using Unity.VisualScripting;
using UnityCodeGen;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Windows;

[Generator]
public class LuaWriter : MonoBehaviour, ICodeGenerator
{
    Dictionary<string, GameObject> savedObjects = new Dictionary<string, GameObject> ();
    string data = "";

    // Contador para las tabulaciones
    int i=0;

    //Saves relevant data from all scenes except for bootscene using playerprefs
    public void SaveAll()
    {

        //Aqui se escribe "local scenes = {" en el archivo de lua
        data += "local scenes = {\n";

        //Se suma uno al contador de tabulaciones
        i++;// = 1
        foreach (Scene scene in SceneManager.GetAllScenes())
        {
            Tabulate();
            
           //Escribimos el nombre de la escena
           data += scene.name+" = {\n";

           //Incrementamos el contador de tabulacion
           i++; // = 2
           foreach (GameObject obj in scene.GetRootGameObjects())
           {
                //Sacar componentes del padre components
                SaveGameObjectAndChildren(obj);
           }
           //Decrementamos
           i--; // = 1
           Tabulate();
           data += "},\n";
           
        }
        //Se quita la ultima coma
        data = data.Remove(data.Length-2);
        Tabulate();
        data += "\n";
        //Aqui se cierra con una llave "}"
        data += "}";
        i--; // = 0

        //y se escribe al final del archivo "return prefabs, scenes"
        data += "\nreturn prefabs, scenes";
    }
    /// <summary>
    ///  Añade los componentes del padre y luego los objetos que tiene como hijo recursivamente
    /// </summary>
    /// <param name="obj">Objeto a escribir en el archivo de Lua</param>
    private void SaveGameObjectAndChildren(GameObject obj)
    {
        //Nombre del GameObject
        data += "\n";
        Tabulate();
        data += obj.name + "= {\n";

        //Componentes
        i++; // = x + 1
        Tabulate();
        data += "components = {\n";
        //Transform
        i++;// = x + 2

        var tf = obj.GetComponent<Transform>();
        Tabulate();
        data += tf.GetType() + "= {";
        i++;// = x + 3
        data += "\n";
        Tabulate();
        data += "position = " + "{" + tf.localPosition.x.ToString(new CultureInfo("en-US")) + 
            "," + tf.localPosition.y.ToString(new CultureInfo("en-US")) +
            "," + tf.localPosition.z.ToString(new CultureInfo("en-US")) + "}" + ",\n";
        Tabulate();
        data += "rotation = " + "{" + tf.localRotation.x.ToString(new CultureInfo("en-US")) + 
            "," + tf.localRotation.y.ToString(new CultureInfo("en-US")) + 
            "," + tf.localRotation.z.ToString(new CultureInfo("en-US")) + 
            "," + tf.localRotation.w.ToString(new CultureInfo("en-US")) + "}" + ",\n";
        Tabulate();
        data += "scale = " + "{" + tf.localScale.x.ToString(new CultureInfo("en-US")) + 
            "," + tf.localScale.y.ToString(new CultureInfo("en-US")) + 
            "," + tf.localScale.z.ToString(new CultureInfo("en-US")) + "}" + "\n";

        i--;// = x + 2
        Tabulate();
        data += "},\n";


        //eotransform

        foreach (FORGEComponent component in obj.GetComponents(typeof(FORGEComponent)))
        {
            Tabulate();
            data += component.componentName + "= {\n";
            i++;// = x + 3
            foreach(KeyValuePair<string, string> value in component.values)
            {
                Tabulate();
                data += value.Key + " = " + value.Value + ",\n";
            }
            data = data.Remove(data.Length-2);
            Tabulate();
            data += "\n";
            i--;// = x + 2
            Tabulate();
            data += "},\n";
        }
        i--; // = x + 1
        data = data.Remove(data.Length-2);
        data += "\n";
        Tabulate();
        data += "}\n";

        //Objetos hijos
        // = x + 1
        for (int i = 0; i < obj.transform.childCount; i++)
        {
            Tabulate();
            SaveGameObjectAndChildren(obj.transform.GetChild(i).gameObject);
        }
        i--; // = x + 1
        savedObjects.Add(obj.name, obj);
        Tabulate();
        data += "}\n";
        i--;// = x

        i++;

    }

    /// <summary>
    /// Metodo para tabular correctamente en el archivo de Lua
    /// </summary>
    public void Tabulate()
    {
        for (int n = 0; n < i; n++)
        {
            data += "\t";
        }
    }

    /// <summary>
    /// Metodo heredado que al darle a tools->UnityCodeGen->Generate genera el codigo en Lua
    /// </summary>
    /// <param name="context"></param>
    public void Execute(GeneratorContext context)
    {
        SaveAll();
        data = data.Replace("UnityEngine.", "");
        context.OverrideFolderPath("Assets/FORGE Data");
        context.AddCode("luatest.lua", data);
    }
}
