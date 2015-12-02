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
 public:
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
  int recv ( std::string & bfr, int flags = 0 ) const;
  
  /**
   * Recieve raw data from a socket
   * @param  bfr      the buffer to write data into (Ensure it is big enough!)
   * @param  numBytes the number of bytes to recieve
   * @param  flags    flags for socket reading options
   * @return          the number of bytes read
   */
  int recv ( void * bfr, int numBytes ,int flags = 0) const;

  /**
   * Set the socket to non-blocking mode
   * @param bool whether or not the socket should block
   */
  void set_non_blocking ( const bool );

   bool hasData();
  /**
   * Check of the socket is valid for use
   * @return false if the socket has not been created
   */
  bool is_valid() const { return m_sock != -1; }

   void close();

 private:

  int m_sock;

   protected:
   int port;
   sockaddr_in m_addr;


};


#endif
