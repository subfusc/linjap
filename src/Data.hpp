#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
#include <string>
using namespace std;

class Data 
{
  bool **data_arr;
  int dimx, dimy;
  vector<string> *chap_names;
  vector<string> *part_names;

public:
  Data(int x, int y);
  ~Data() {} 

  void set_place(int x, int y);
  void set_chap_names(vector<string> in_chap_names);
  void set_part_names(vector<string> in_part_names);
  bool get_place(int x, int y);
  vector<string>* get_chap_names();
  vector<string>* get_part_names();
  int length_x();
  int length_y();
};

#endif //DATA_HPP
