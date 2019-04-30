using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SqilteTest : MonoBehaviour
{
	// https://www.jianshu.com/p/381ed9d59654

	public SqliteDatabase Sqlite;

	void Start()
    {
		//打开测试数据库
		Sqlite = new SqliteDatabase("Sqlite.db");
		PrintData();

	}

   private void PrintData()
	{
		DataTable dt = Sqlite.ExecuteQuery("SELECT * FROM Supplement");
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
