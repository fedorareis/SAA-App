#include <iostream>
#include <fstream>
#include <string>
#include "Message.pb.h"
#include "ClientSocket.h"
#include "SocketException.h"
#include "ProtobufSocketSerializer.h"
int main(int argC, char* argV[])
{
   test::Msg msg;
   int port;
   std::string host;
   if(argC < 3)
   {
      std::cout << "usage: [host] [port]";
      return 0;
   }
   try
   {
      host = argV[1];
      int port = atoi(argV[2]);

      ClientSocket client_socket(host,port);
      std::string rawMessage;
      do
      {
         std::cout << "Enter Message: ";
         getline(std::cin,rawMessage);

         if(!rawMessage.empty())
         {
            test::Msg reply;
            std::cout << "Sending: " << rawMessage << std::endl;;
            msg.set_name(rawMessage);
            msg.set_age(5);
            client_socket << msg;
            client_socket >> reply;
            std::cout << "Server says: " << reply.name() << ": age " << reply.age() << std::endl;
         }

      }while(!rawMessage.empty());

   }
   catch(SocketException & e)
   {
      std::cout << "Exception was caught:" << e.description() << std::endl;
   }
   google::protobuf::ShutdownProtobufLibrary();
   return 0;
}