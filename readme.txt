
                          * ICQpipe - READ.ME *
                          -------------------


This README file is divided into the following categories:

	- About ICQpipe

	- Before You Install ICQpipe
	  - Software Requirements

	- Installation

	- Configuration

        - To developers

	- Author


About ICQpipe
-------------

	ICQpipe is a very simple pwICQ's plugin originally developed
as a "test" module for the plugin specs it acts as  a  interface  to 
sysbar/2 (or any other) pipe monitor converting the pwICQ's reported
events to text strings and sending then to the configured pipe.

Before You Install ICQpipe
--------------------------

   Software Requirements
   ---------------------

   . pwICQ version 0.29 or greater

   . SysBar/2 (or any other) pipe monitor



Installation
------------

   Uncompress the zip file and copy ICQpipe.dll to the folder
   plugins under pwICQ, the plugin will be loaded in the
   next restart of the program.


Configuration
-------------

   When activated the plugin adds one page on the pwICQ's main
   configuration with the following options:

   . Pipe name
     Name of the pipe to send notifications

   . Notify System changes
     Send the pwICQ's status changes to the pipe

   . Notify user online status
     Send the user's status changes to the pipe

   . Notify on waiting message   
     Send information about the pending message (not opened) to the pipe.
     

To developers
-------------

   To compile this module you'll need the .LIB files from the pwICQ's modules, you 
   can get it using the IMPLIB tool.

   This is a very simple plugin and it not implements all the pwICQ's plugin 
   functions. 


Author
------

   Perry Werneck
   perryw@zaz.com.br
   ICQ# 27241234


