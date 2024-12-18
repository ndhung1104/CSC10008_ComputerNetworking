COMPUTER NETWORKS COURSE PROJECT

DEVELOPING A REMOTE COMPUTER CONTROL SYSTEM USING E-MAIL

Description:
The system allows a user or admin to remotely control a specific computer within a LAN (identified by its IP address) to perform actions such as:

+ Shutdown
+ Reset
+ Screen capture
+ Keylogging
+ Listing/Starting/Stopping applications and processes
+ Copying/Deleting files
+ Starting/Stopping the webcam

The software system consists of two main modules:

[1]. SERVER
+ Runs on the controlled computer.
+ Receives control commands sent from the CLIENT and executes them, such as shutdown, reset, screen capture, keylogging, listing/starting/stopping apps, etc.
+ Sends the results back to the CLIENT after execution.

[2]. CLIENT
+ Performs the following main tasks:
+ Checks emails to receive control commands from the user or admin.
+ Based on the email content, sends corresponding control requests to the SERVER.
+ Sends an email reply with the results to the user or admin.