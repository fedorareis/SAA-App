/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
// Definition of the Socket class
//Taken from tldp.org/LDP/LG/issue74/misc/tougher
#ifndef Socket_class
#define Socket_class


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket
{
   protected:

   Socket();
   Socket(const Socket & other);
   virtual ~Socket();


   /**
    * create a new socket
    * @return true if no problems occurred.
    */
   bool create();

   /**
    * Bind a socket to a port
    * @param  port the port to bind the socket to
    * @return      true if no problems
    */
   bool bind ( const int port );

   /**
    * Listen for incoming connections
    * @return true if no issues on listening.
    */
    bool listen() const;

    /**
     * Accept a socket connection, and bind it to the new socket.
     */
    bool accept ( Socket& ) const;

    /**
     * Connect to a current socket
     * @param  host the host to connect to
     * @param  port the port to connect to
     * @return      true if connection was successful
     */
    bool connect ( const std::string host, const int port );

    /**
     * Connect to a current socket
     * @param  host connection info to connect on
     * @return      true if connection was successful
     */
    bool connect ( const sockaddr_in host );

    /**
     * Send string data down the socket
     * @param  msg the string message to send
     * @return     true if no issues
     */
    bool send (const std::string & msg) const;

    /**
     * Send raw data down the socket
     * @param  msg the raw data to send
     * @param  len the length of the data
     * @return     true if no issues.
     */
    bool send (const void * msg, int len) const;

    /**
     * Recieve string data from the socket. (Default, 500 bytes)
     * @param  bfr   The string to write to
     * @param  flags Flags for socket reading options
     * @return       the number of bytes read
     */
    ssize_t recv ( std::string & bfr, int flags = 0 ) const;

    /**
     * Recieve raw data from a socket
     * @param  bfr      the buffer to write data into (Ensure it is big enough!)
     * @param  numBytes the number of bytes to recieve
     * @param  flags    flags for socket reading options
     * @return          the number of bytes read
     */
    ssize_t recv ( void * bfr, int numBytes ,int flags = 0) const;

   /**
    * Set the socket to non-blocking mode
    * @param bool whether or not the socket should block
    */
    void set_non_blocking ( const bool );

    bool hasData() const;

   /**
    * Check of the socket is valid for use
    * @return false if the socket has not been created
    */
   bool is_valid() const { return m_sock != -1; }

   void close();

   private:
   /**
    * the socket file descriptor
    */
   int m_sock;

   protected:
   /**
    * The connected port
    */
   int port;

   /**
    * The socket address information of the active
    * connection
    */
   sockaddr_in m_addr;


};


#endif
