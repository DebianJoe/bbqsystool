bbqsystool
==========

A System Tool in ncurses for LinuxBBQ

Requires root permissions to run.

Depends on libncurses.

==========
Under HEAVY construction.  Thus, there is no included makefile because I don't want someone to come along and think it's done.  If you wish to test it out, then it's very simple.  Download source, unpack it, navigate to the bbqsystool directory.  Use "gcc bbqsystem.c -lncurses" to create a binary for your system.  Then execute it with "sudo ./a.out", or log in as root and run the created binary.

If I have to explain to you why it might not be totally safe to run a tool that is under construction that allows the root user to adjust CPU frequency and thresholds from userspace, then I believe that you deserve whatever happens.  Assuming that you simply wish to help test or troubleshoot the sections that are being worked on, then put in a pull-request with fixes or open an issue to discuss.

-joe
