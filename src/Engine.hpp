#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "LList.hpp"
#include "Data.hpp"
#include "Av.hpp"
#include "FileReader.hpp"
#include "Mode.hpp"
#include "Mode_eng_jap.hpp"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Engine {
  LList *db;
  Mode *mod;
  bool in_session;

public:
  Engine(string filename);
  ~Engine();

  void load_dict(string filename);
  Data* get_data();
  bool prepare_session(vector<Av> in);
  bool set_mode(string mode);
  ustring* next(ustring last);
  bool has_next();
  int words_left();
  int words_total();
  int wrong_total();
};

#endif
