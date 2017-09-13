# MagicSocket
A simple wrapper for sockets in C++.

## Why
During the development of a personal project I had to use sockets in C++. Instead of writing all the cluttering code, I decided to write a simple wrapper for future reuse.<br>
The class `MagicSocket` implements all the classic socket functions but at an higher level.<br>
## Usage
Just include `MagicSocket.hpp` and `MagicSocket.cpp` in your project.

## Example code

#### Send a message

```
#include "magicSocket.hpp"
#include <iostream>


int main(){
    MagicSocket s(true); //create a reusable socket
    s.Connect("127.0.0.1",1931); //connect it to a local server (I used netcat)
    s.Send("Hello world"); //send
    s.Close(); //close
}
```
#### Receive a message
```
#include "magicSocket.hpp"
#include <iostream>

int main()
{
    MagicSocket s(true); //create a reusable socket
    s.Listen(1931); //listen to the 1931 port
    MagicSocket newSocket = s.Accept(); //wait and accept a connection. This is a blocking call.
    char msg[20];
    int len = newSocket.Receive(msg, 20); //receive on a buffer
    std::cout<<"Received "<<len<<" bytes"<<std::endl;
    std::cout << "Received message: " << msg << std::endl;
    s.Close(); //close
}
```
Note that the `NewSocket` **IS NOT** reusable.

## Credits
Idea and code: [Antonello Galipò](https://github.com/magicleon94)<br>
Code and debug: [Federico Rizzo](https://github.com/federix93)


