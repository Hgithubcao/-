using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;
using System;
using System.Text;
using System.Text.RegularExpressions;

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
			line = line.Replace("\t", ", ");
			lines[i] = line;
		}
		ChangeTextToCSV(lines, "Supplement");
	}

	[MenuItem("Assets/SeenToSeenSqlite", false, 2)]
	static public void SeenToSqlite()
	{
		string path = AssetDatabase.GetAssetPath(Selection.activeObject);
		ReadText(path, "Seen");
	}

	static private void ChangeTextToCSV(string[] lines, string tableName)
	{
		string filePath = Application.streamingAssetsPath + "//" + tableName + ".csv";
		string info = "";
		foreach(string line in lines)
		{
			info += line + "\n";
		}
		FileStream fs = null;
		StreamWriter sw = null;
		try
		{
			fs = new FileStream(filePath, FileMode.Append, FileAccess.Write);
			sw = new StreamWriter(fs);
			sw.Write(info);
		}
		finally
		{
			if (sw != null)
			{
				sw.Close();
			}
			if (fs != null)
			{
				fs.Close();
			}
		}
	}

	/// <summary>
	/// Problem:
	/// 1、写进数据库之后，db browser看不到，但是程序读的到
	/// 2、中文写不进数据库
	/// </summary>
	/// <param name="lines"></param>
	/// <param name="tableName"></param>
	static private void ChangeTextToSqlite(string[] lines, string tableName)
	{
		SqliteDatabase sqlite = new SqliteDatabase("Sqlite.db");
		PrintSqlite(sqlite, tableName);
		foreach (string line in lines)
		{
			string sqlQuery = string.Format("insert into {0} values({1})", tableName, line);
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
		//PrintSqlite(sqlite, tableName);
		
	}

	static private string[] ReadFileLines(string path)
	{
		if (!File.Exists(path))
			return null;
		return File.ReadAllLines(path, Encoding.Default);
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

	/// <summary>
	/// 测试一下StreamReader
	/// </summary>
	/// <param name="path"></param>
	static private void ReadText(string path, string tableName)
	{
		string filePath = Application.streamingAssetsPath + "//" + tableName + ".csv";
		FileStream fs = new FileStream(filePath, FileMode.Append);
		StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);
		using (StreamReader streamReader = new StreamReader(path, Encoding.Default))
		{

			string oneLineString;
			int rowIndex = 0;
			string csvLine = "";
			while ((oneLineString = streamReader.ReadLine()) != null)
			{
				if(string.IsNullOrEmpty(oneLineString))
				{
					rowIndex = 0;
					Debug.Log(csvLine);
					sw.Write(csvLine);
					csvLine = "";
					continue;
				}

				switch(rowIndex)
				{
					case (0):
					{
							string[] info = oneLineString.Split(':');
							// 第一行拿到看完日期和番名
							Match match = Regex.Match(info[0], @"\d+年\d+月\d+日");
							if(match != null)
							{
								csvLine += string.Format("{0}, {1}", info[1], match.Value);
							}
							break;
					}
					case (5):
					{
							// 第六行拿到看的时候的分数
							string[] info = oneLineString.Split('：');
							if (info.Length >= 2)
								csvLine += "," + info[1] + "\n";
							else
								Debug.LogError(oneLineString);
							break;
					}
					default:
					{
							// 第二行拿到开始想看的日期
							// 第三行拿到当年热度
							// 第四行拿到集数
							// 第五行拿到更新年份
							string[] info = oneLineString.Split(':');
							if (info.Length >= 2)
								csvLine += "," + info[1];
							else
								Debug.LogError(oneLineString);
							break;
					}
				}

				rowIndex ++;
			}
		}

		if (sw != null)
		{
			sw.Close();
		}
		if (fs != null)
		{
			fs.Close();
		}
	}
}
