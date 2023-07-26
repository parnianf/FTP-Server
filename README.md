# FTP-Server
This is an implementation of a simplified version of FTP. This program consists `client` and `server`. The server is responsible for serving files to the client.
In this protocol, communication requires two different channels to send and receive data. The first channel, called the `command channel`, is the channel through which commands and responses are sent. The other channel, which is called the `data channel`, is the channel responsible for data transfer.
