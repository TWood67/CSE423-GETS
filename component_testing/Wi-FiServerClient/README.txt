/* ==================================================================================

 * File: README.txt

 * System: Host PC

 * Team: MUSCA

 * Course Info: CSE 423 Fall 2013

 * 

 * Author(s): Taylor Wood

 * Email: Taylorwood67@gmail.com

 * ==================================================================================

 * Description: README text file for the client and server executables.

 * ==================================================================================

 * Change History: File created

 * ________________________________________________________________

 * || Author || Date || Description ||

 * ----------------------------------------------------------------

 * || Taylor Wood || 12/28/13 || Added README ||

 * ----------------------------------------------------------------

 *

 * ==================================================================================*/

				Client/Server README

I've created this README to explain what is going on. For more indepth information
on the client and server files, go to the site listed in each. I have included a
makefile to create both of the executables. Ignore any warnings that gcc outputs, 
these are to be expected. All files and code have been tested and executed 
successfully in Ubuntu 12.04.

For now, the client simply sends numbered packets labeled with strings to the server. 

1. Before compiling, change the SRV_IP definition in client.c. This needs to be
the ip address of the host machine. This can be found by using the "ifconfig"
command in a terminal window.

2. Run the make file to create the executables.

3. Run "./server" to execute the server

4. Run "./client" to execute the client. This will need to be done in a separate
window. 

5. You should witness output on both terminals explaining what has happened. Run
"make clean" in the directory of the makefile to clean the executables before
commiting any changes to the server.
