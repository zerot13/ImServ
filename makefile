make: server.c logger.c dbops.c
	gcc -o server server.c logger.c dbops.c `mysql_config --cflags --libs`
