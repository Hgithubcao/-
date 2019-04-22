using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;
using System;

public class TextToSqlite : Editor
{
	[MenuItem("Assets/补番计划ToSupplement", false, 1)]
	static public void BFJHToSupplement()
	{
		string path = AssetDatabase.GetAssetPath(Selection.activeObject);
		var lines = ReadFileLines(path);
		//PrintLines(lines);
		for(int i = 0; i < lines.Length; i ++)
		{
			string line = lines[i];
			line = line.Replace("\t", "', '");
			line = "'" + line + "'";
			//int index = line.IndexOf(',');
			//line = line.Insert(index, "'");
			lines[i] = line;
			//Debug.Log(i + ": " +lines[i] + " " + index);
		}
		ChangeTextToSqlite(lines, "Supplement");
	}

	[MenuItem("Assets/SeenToSeenSqlite", false, 2)]
	static public void SeenToSqlite()
	{
		//ChangeTextToSqlite("Seen");
	}

	static private void ChangeTextToSqlite(string[] lines, string tableName)
	{
		SqliteDatabase sqlite = new SqliteDatabase("Sqlite.db");
		Debug.Log(lines.Length);
		PrintSqlite(sqlite, tableName);
		foreach (string line in lines)
		{
			string sqlQuery = string.Format("insert into {0} values({1})", tableName, line);
			//Debug.Log(sqlQuery);
			try
			{
				sqlite.ExecuteNonQuery(sqlQuery);
			}
			catch (Exception e)
			{
				Debug.LogError(sqlQuery + "\n" + e.ToString());
			}
			finally
			{

			}
		}
		PrintSqlite(sqlite, tableName);
		
	}

	static private string[] ReadFileLines(string path)
	{
		if (!File.Exists(path))
			return null;
		return File.ReadAllLines(path, System.Text.Encoding.Default);
	}

	static private void PrintLines(string[] lines)
	{
		for (int i = 0; i < lines.Length; i++)
		{
			Debug.Log(i + "  " + lines[i]);
		}
	}

	static private void PrintSqlite(SqliteDatabase sqlite, string tableName)
	{
		DataTable dt = sqlite.ExecuteQuery("SELECT * FROM " + tableName);
		foreach (DataRow item in dt.Rows)
		{
			string str = "";
			foreach (var obj in item)
			{
				str += obj.Key + ":" + obj.Value + "\t";
			}
			Debug.Log(str);
		}
	}
}
