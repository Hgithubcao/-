using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Data;
using System.IO;

public partial class Leadin : System.Web.UI.Page
{
    private string ConnectionString = "Data Source=LZHGEDREWEN\\LZHSQL;Initial Catalog=Acg;Integrated Security=True";
    private SqlConnection conn;
    protected void Page_Load(object sender, EventArgs e)
    {
        conn = new SqlConnection(ConnectionString);
       /* string CommandString;
        SqlCommand com;
        SqlDataReader dr;*/
        conn.Open();
     /*   CommandString = "Select * from Student Where Sid='" + Session["Sid"].ToString() + "'";
        com = new SqlCommand(CommandString, conn);
        dr = com.ExecuteReader();
        dr.Read();
        dr.Close();*/
    }
    protected void Button1_Click(object sender, EventArgs e)
    {

    }
}