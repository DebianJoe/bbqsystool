bbqsystool
==========

A System Tool in ncurses for LinuxBBQ

Requires root permissions to run, some features are available without it...but the control over governing will require root permission.

Depends on libncurses 5.9+20...so as new as possible is a good idea.

Note:
==========
This is the development branch for the LinuxBBQ CPU System Tool.
The htop option is simply a loader, and assumes you have alredy installed htop.


Installation:
==========
After downloading the source, cd into the newly created directory.  Then simply 

```
make 

```

and with root permission

```
make install

```  

The newly created binary will be located in /usr/bin by default.  Hack up the Makefile if you don't like it.  The progam is provided "as-is" and devoid of warranty.  

If I have to explain to you why it might not be totally safe to run a tool that is under construction that allows the root user to adjust CPU frequency and thresholds from userspace, then I believe that you deserve whatever happens.  Assuming that you simply wish to help test or troubleshoot the sections that are being worked on, then put in a pull-request with fixes or open an issue to discuss.

Misc:
========
Special thanks to Pidsley and Xaos52 for assistance with implementing awk into tutor mode.

-joe
