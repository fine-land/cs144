#include "byte_stream.hh"

#include <cstdio>

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) 
  : capacity_( capacity ) {}

bool Writer::is_closed() const
{
   return closed_;
}

void Writer::push( string data )
{
  // Your code here.
  //Dont forget to update members

  if(is_closed() || data.empty()) return;

  if(data.size() > available_capacity()) {
     data.resize(available_capacity());
  }

  const auto size = data.size();
  bytes_pushed_ += size;
  bytes_buffered_ += size;

  buffer_.emplace(std::move(data));
}

void Writer::close()
{
  // Your code here.
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - bytes_buffered_;
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return closed_ && bytes_buffered_ == 0; 
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return bytes_popped_;
}

string_view Reader::peek() const
{
  // Your code here.
  return buffer_.empty() ? std::string_view{} : std::string_view{ buffer_.front()}.substr(index_);
}

void Reader::pop( uint64_t len )
{
  // Your code here.
 while(!buffer_.empty()){
    auto& frontstring = buffer_.front();
    const uint64_t left = frontstring.size() - index_;
    if(len >= left){
      buffer_.pop();
      bytes_buffered_ -= left;
      bytes_popped_ += left;
      index_ = 0;
      len -= left;
    } else{
      index_ += len;
      bytes_buffered_ -= len;
      bytes_popped_ += len;
      break;
    }    
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return bytes_buffered_;
}
