#ifndef LLIST_HPP
#define LLIST_HPP

#include <vector>
#include <list>
#include <string>

#include "Word.hpp"
#include "LListNode.hpp"
#include "Data.hpp"
using namespace std;

class LList {
  LListNode *head;
  int params[2];
  vector<string> *chap_names;
  vector<string> *part_names;

public:
  LList();
  ~LList();

  bool add(Word in, int chap, int part);
  bool add(Word *in, int chap, int part);
  list<Word>* get(int chap, int part);
  Data* get_data();
  void get_params(int *chaps, int *parts);
  int get_chap_length();
  int get_part_length();
  void set_chap_names(vector<string> _chap_names);
  void set_part_names(vector<string> _part_names);
  int size();
};

#endif
