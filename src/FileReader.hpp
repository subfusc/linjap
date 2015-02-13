#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include "LList.hpp"
#include "Word.hpp"
#include <string>
using namespace std;

class FileReader
{
  
public:
  FileReader();
  ~FileReader();

  static LList* read_dict(string file_name);
};
#endif
