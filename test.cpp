#include "magicSocket.hpp"
#include <iostream>


int main(){
    MagicSocket s(true);
    s.Listen(1931);
    s.Connect("127.0.0.1",1931);
    s.Send("Hello world");
    s.Close();
}