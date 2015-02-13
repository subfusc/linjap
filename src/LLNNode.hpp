#ifndef LLNNODE_HPP
#define LLNNODE_HPP

#include <list>
#include "Word.hpp"

class LLNNode 
{
  LLNNode *pnext;
  list<Word> words;

public:
  LLNNode();
  ~LLNNode();
  
  bool add(Word in);
  bool has_next();
  LLNNode* next();
  void set_next(LLNNode *in);
  list<Word>* get();
  int size();
};

#endif
