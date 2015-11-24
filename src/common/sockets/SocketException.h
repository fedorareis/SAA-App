// SocketException class
// Taken from tldp.org/LDP/LG/issue74/misc/tougher
#ifndef SocketException_class
#define SocketException_class

#include <string>

/**
 * A SocketException is thrown when any issues occur
 * with socket connections
 */
class SocketException
{
 public:
  SocketException ( std::string s ) : m_s ( s ) {};
  ~SocketException (){};

  std::string description() { return m_s; }

 private:

  std::string m_s;

};

#endif
