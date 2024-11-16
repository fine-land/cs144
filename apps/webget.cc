#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  //cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  //cerr << "Warning: get_URL() has not been implemented yet.\n";
  Address addr{host, "http"};
  TCPSocket ts{};

  std::string header{};
  header += "GET ";
  header += path;
  header += " HTTP/1.1\r\n";
  header += "Host: " + host + "\r\n";
  header += "Connection: close\r\n";
  header += "\r\n";

  ts.connect(addr);
  ts.write(header);
  std::vector<std::string> page{};
  while(!ts.eof()){
    std::string temp{};
    ts.read(temp);
    page.emplace_back(temp);
  }
    for( const auto& i : page ){
      std::cout << i;
    }

}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
