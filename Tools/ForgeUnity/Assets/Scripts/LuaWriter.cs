using System.Collections.Generic;
using System.Globalization;
using UnityCodeGen;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;

[Generator]
public class LuaWriter : MonoBehaviour, ICodeGenerator
{
    private string fileName = "luaTest.lua";
    private string folderPath = "Assets/FORGE Data";

    Dictionary<string, int> prefabData = new Dictionary<string, int> ();
    HashSet<string> hashData = new HashSet<string> ();
    string data = "";

    // Contador para las tabulaciones
    private int i=0;
    private bool firstSearch = false;
    //Saves relevant data from all scenes except for bootscene using playerprefs
    public void SaveAll()
    {
        //Primera busqueda de prefabs en la escena
        data += "local prefabs = {\n";
        i++;
#pragma warning disable
        foreach(Scene scene in SceneManager.GetAllScenes())
        {
#pragma warning restore

            foreach (GameObject obj in scene.GetRootGameObjects())
            {
                LookForPrefab(obj);
            }
        }

        //Cuando se acaba la primera busqueda se marca
        firstSearch = true;
        i--;
        data += "}\n\n";
        //Aqui se escribe "local scenes = {" en el archivo de lua
        data += "local scenes = {\n";

        //Se suma uno al contador de tabulaciones
        i++;// = 1
#pragma warning disable
        foreach (Scene scene in SceneManager.GetAllScenes())
        {
#pragma warning restore
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

    private void LookForPrefab(GameObject obj)
    {
        int j = 0;
        bool found = false;
        if (PrefabUtility.IsPartOfAnyPrefab(obj))
        {
            found =true;
            string prefabName = PrefabUtility.GetCorrespondingObjectFromOriginalSource(obj).name;
            if (!prefabData.ContainsKey(prefabName))
            {
                prefabData[prefabName] = 0;
                SaveGameObjectAndChildren(obj);
            }
        }
        while(j < obj.transform.childCount&&!found)
        {
            LookForPrefab(obj.transform.GetChild(j).gameObject);
            j++;
        }
    }

    /// <summary>
    ///  Añade los componentes del padre y luego los objetos que tiene como hijo recursivamente
    /// </summary>
    /// <param name="obj">Objeto a escribir en el archivo de Lua</param>
    private void SaveGameObjectAndChildren(GameObject obj)
    {
        bool prefab = PrefabUtility.IsPartOfAnyPrefab(obj);
        if (prefab && firstSearch)
        {
            //Nombre del GameObject
            data += "\n";
            Tabulate();
            int repetitions = (prefabData[PrefabUtility.GetCorrespondingObjectFromOriginalSource(obj).name] += 1);
            obj.name = PrefabUtility.GetCorrespondingObjectFromOriginalSource(obj).name + repetitions;
            data += obj.name + "= {\n";
            i++;
            Tabulate();
            data += "blueprint = " + "\"" + PrefabUtility.GetCorrespondingObjectFromOriginalSource(obj).name+ "\"\n";
            i--;
        }
        else
        {
            WriteData(obj);
            //Objetos hijos
            // = x + 1
            for (int i = 0; i < obj.transform.childCount; i++)
            {
                Tabulate();
                SaveGameObjectAndChildren(obj.transform.GetChild(i).gameObject);
            }
            i--; // = x + 1
        }
        Tabulate();
        data += "}\n";
        i--;// = x

        i++;

    }

    private void WriteData(GameObject obj)
    {
        //Nombre del GameObject
        data += "\n";
        Tabulate();
        data += obj.name + "= {\n";

        //Componentes
        i++; // = x + 1
        if (obj.tag != "Untagged")
        {
            if (!hashData.Contains(obj.tag))
                hashData.Add(obj.tag);
            else
                Debug.LogWarning("Handler with the same name already exists!! Change the tag on " + obj);
            Tabulate();
            data += "handler = " + "\"" + obj.tag + "\",\n";
        }

        if (LayerMask.LayerToName(obj.layer) != "Default")
        {
            Tabulate();
            data += "group = " + "\"" + LayerMask.LayerToName(obj.layer) + "\",\n";
        }
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
        CultureInfo rightFormat = new CultureInfo("en-US");
        data += "position = " + "{" + tf.localPosition.x.ToString(rightFormat) +
            "," + tf.localPosition.y.ToString(rightFormat) +
            "," + tf.localPosition.z.ToString(rightFormat) + "}" + ",\n";
        Tabulate();
        data += "rotation = " + "{" + tf.localRotation.x.ToString(rightFormat) +
            "," + tf.localRotation.y.ToString(rightFormat) +
            "," + tf.localRotation.z.ToString(rightFormat) +
            "," + tf.localRotation.w.ToString(rightFormat) + "}" + ",\n";
        Tabulate();
        data += "scale = " + "{" + tf.localScale.x.ToString(rightFormat) +
            "," + tf.localScale.y.ToString(rightFormat) +
            "," + tf.localScale.z.ToString(rightFormat) + "}" + "\n";

        i--;// = x + 2
        Tabulate();
        data += "},\n";


        //eotransform

        foreach (FORGEComponent component in obj.GetComponents(typeof(FORGEComponent)))
        {
            Tabulate();
            data += component.componentName + "= {\n";
            i++;// = x + 3
            foreach (KeyValuePair<string, string> value in component.values)
            {
                Tabulate();
                data += value.Key + " = " + value.Value + ",\n";
            }
            data = data.Remove(data.Length - 2);
            Tabulate();
            data += "\n";
            i--;// = x + 2
            Tabulate();
            data += "},\n";
        }
        i--; // = x + 1
        data = data.Remove(data.Length - 2);
        data += "\n";
        Tabulate();
        data += "}\n";
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
        context.OverrideFolderPath(folderPath);
        context.AddCode(fileName, data);
    }
}
