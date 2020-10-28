#include <mysql.h>
#include <my_global.h>
#include <stdlib.h>

#include "logger.h"

int CreateDatabase()
{
	MYSQL *conn = mysql_init(NULL);
	if(conn == NULL)
	{
		LogError("MySql error: %s", mysql_error(conn));
		return -1;
	}
	if(mysql_real_connect(conn, "localhost", "root", NULL, NULL, 0, NULL, 0) == NULL)
	{
		LogError("MySql error 1: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}
	if(mysql_query(conn, "CREATE DATABASE IF NOT EXISTS testdb"))
	{
		LogError("MySql error 2: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}
	if(mysql_query(conn, "USE testdb"))
	{
		LogError("MySql error 2.5: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}
	if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS Images(ImageKey INT NOT NULL AUTO_INCREMENT, FilePath LONGTEXT, CreateDate DATE, PRIMARY KEY (ImageKey))"))
	{
		LogError("MySql error 3: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}
	if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS Tags(ImageKey INT, TagType INT, Tag varchar(255), INDEX img_ind (ImageKey), FOREIGN KEY (ImageKey) REFERENCES Images(ImageKey))"))
	{
		LogError("MySql error 4: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}
	if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS Projects(ProjectKey INT NOT NULL AUTO_INCREMENT, Name varchar(255), PRIMARY KEY (ProjectKey))"))
	{
		LogError("MySql error 5: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}
	if(mysql_query(conn, "CREATE TABLE IF NOT EXISTS Proj_Imgs(ProjectKey INT, ImageKey INT, INDEX (ProjectKey), INDEX (ImageKey), FOREIGN KEY (ProjectKey) REFERENCES Projects(ProjectKey), FOREIGN KEY (ImageKey) REFERENCES Images(ImageKey))"))
	{
		LogError("MySql error 6: %s", mysql_error(conn));
		mysql_close(conn);
		return -1;
	}

	mysql_close(conn);
	return 0;
}

void WriteRecord(char *filePath)
{
	MYSQL *con = mysql_init(NULL);
}
