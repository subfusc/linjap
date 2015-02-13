#include "LList.hpp"
#include <iostream>
using namespace std;

LList::LList()
{
  head = new LListNode();
  params[0] = 0;
  params[1] = 0;
  chap_names = NULL;
  part_names = NULL;
}

LList::~LList()
{
  if (chap_names) delete chap_names;
  if (part_names) delete part_names;
  LListNode *ce = head;

  while (ce->has_next()) {
    LListNode *tmp = ce;
    ce = ce->next();
    delete tmp;
  }
  delete ce;
}

bool LList::add(Word in, int chap, int part)
{
  cout << "Add: " << chap << ", " << part << endl;

  int x = 0;
  LListNode *ce = head;

  for (; x < chap; x++) {
    if (ce->has_next()) {
      ce = ce->next();
    } else {
      ce->set_next(new LListNode());
      ce = ce->next();
  }}

  ce->add(in, part);
  if (chap > params[0]) params[0] = chap;
  if (part > params[1]) params[1] = part;
  return true;
}

bool LList::add(Word *in, int chap, int part)
{
  return this->add(*in, chap, part);
}

list<Word>* LList::get(int chap, int part)
{
  int x = 0;
  LListNode *ce = head;

  if (chap > params[0] || part > params[1]) return NULL;
  for (; x < chap; x++) {
    ce = ce->next();
  }
  
  return ce->get(part);
}

Data* LList::get_data()
{
  if (params[0] == 0 && params[1] == 0) {
    cout << "Returning NULL" << endl;
    return NULL;
  }

  int x, y;
  LListNode *ce = head;
  Data *rdata = new Data(params[0] + 1, params[1] + 2);
  
  rdata->set_chap_names(*chap_names);
  rdata->set_part_names(*part_names);

  for (x = 0; x < params[0] + 1; x++) {
    if (ce->size()) {
      rdata->set_place(x, 0);
      for (y = 1; y < params[1] + 2; y++) {
	list<Word> *tmp = ce->get(y - 1);
	if (tmp) {
	  cout << tmp->size() << endl;
	  if (tmp->size()) rdata->set_place(x, y);
	  delete tmp;
	}
      }
    }
    ce = ce->next();
  }

  return rdata;
}

void LList::get_params(int *chaps, int *parts)
{
  *chaps = params[0];
  *parts = params[1];
}

void LList::set_chap_names(vector<string> _chap_names)
{
  chap_names = new vector<string>(_chap_names);
}

void LList::set_part_names(vector<string> _part_names)
{
  part_names = new vector<string>(_part_names);
}

int LList::get_chap_length() 
{
  return params[0];
}

int LList::get_part_length()
{
  return params[1];
}

int LList::size() 
{
  int x = 0;
  LListNode *ce = head;
  
  while(ce->has_next()){
    x += ce->size();
    ce = ce->next();
  }
  
  x += ce->size();
  return x;
}
