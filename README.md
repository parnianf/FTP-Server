# FTP-Server
This is an implementation of a simplified version of FTP. This program consists `client` and `server`. The server is responsible for serving files to the client.
In this protocol, communication requires two different channels to send and receive data. The first channel, called the `command channel`, is the channel through which commands and responses are sent. The other channel, which is called the `data channel`, is the channel responsible for data transfer. Also, a file called `config.json` exists, which holds information about both users and the command channel and data channel port for authentication and authorization.



## Supported Commands
| Command                   | Description                               |
| :-------------------:     | :---------------------------------------: |
| user \<username>          | provide username for authentication       |
| pass \<password>          | provide password for authentication       |
| pwd                       | get the path of the current directory     |
| mkd \<directory>          | create new directory   |
| dele -f \<filename>       | delete file            |
| dele -d \<directory path> | delete directory     |
| ls                        | list the files and directories in the current working directory  |
| cwd \<path>               | change the current working directory to a different directory    |
| rename \<from> \<to>      | rename files or directories                                      |
| retr \<name>              | download file (if exists)                                        |
| help                      | display information about commands                               |
| quit                      | logout                                                           |

<br>

### Contributors
* [Paria Khoshtab](https://github.com/Theparia/)
* [Parnian Fazel](https://github.com/parnianf/)

