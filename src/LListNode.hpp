#ifndef LLIST_NODE_HPP
#define LLIST_NODE_HPP

#include <list>
#include "Word.hpp"
#include "LLNNode.hpp"

class LListNode
{
  LListNode *pnext;
  LLNNode *head;

public:
  LListNode();
  ~LListNode();

  bool add(Word in, int part);
  bool has_next();
  LListNode* next();
  void set_next(LListNode *_next);
  list<Word>* get(int part);
  int size();
};

#endif
