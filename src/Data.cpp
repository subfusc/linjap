#include "Data.hpp"

Data::Data(int x, int y)
{
  chap_names = NULL;
  part_names = NULL;

  dimx = x;
  dimy = y;
  int hx;
  int hy;
  data_arr = new bool *[dimx];
  for (hx = 0; hx < dimx; hx++) {
    data_arr[hx] = new bool[dimy];
  }
  for (hx = 0; hx < dimx; hx++) {
    bool *tmp_arr = data_arr[hx];
    for (hy = 0; hy < dimy; hy++) {
      tmp_arr[hy] = false;
    }
  }
}

void Data::set_place(int x, int y) 
{
  if (x >= 0 && y >= 0 && x < dimx && y < dimy) {
    data_arr[x][y] = true;
  }
}

void Data::set_chap_names(vector<string> in_chap_names)
{
  chap_names = new vector<string>(in_chap_names);
}

void Data::set_part_names(vector<string> in_part_names)
{
  part_names = new vector<string>(in_part_names);
}

bool Data::get_place(int x, int y) 
{
  if (x >= 0 && y >= 0 && x < dimx && y < dimy) {
    return data_arr[x][y];
  }
  return false;
}

vector<string>* Data::get_chap_names() 
{
  return chap_names;
}

vector<string>* Data::get_part_names()
{
  return part_names;
}

int Data::length_x()
{
  return dimx;
}

int Data::length_y()
{
  return dimy;
}
