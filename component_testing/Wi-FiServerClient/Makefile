APPSERVER = server
APPCLIENT = client

default:
	gcc -o $(APPSERVER) server.c
	gcc -o $(APPCLIENT) client.c

clean:
	rm -f *.*~
	rm -f *~
	rm -f *.o
	rm -f $(APPSERVER)
	rm -f $(APPCLIENT)
