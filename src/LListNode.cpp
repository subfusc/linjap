#include "LListNode.hpp"

LListNode::LListNode()
{
  pnext = NULL;
  head = new LLNNode();
}

LListNode::~LListNode()
{
  LLNNode *ce = head;
  while(ce->has_next()){
    LLNNode *tmp = ce;
    ce = ce->next();
    delete tmp;
  }
  delete ce;
}

bool LListNode::add(Word in, int part)
{
  int x = 0;
  LLNNode *ce = head;

  for (; x < part; x++) {
    if (ce->has_next()) {
      ce = ce->next();
    } else {
      ce->set_next(new LLNNode());
      ce = ce->next();
    }
  }
  ce->add(in);
  return true;
}

bool LListNode::has_next()
{
  return pnext != NULL;
}

LListNode* LListNode::next() 
{
  return pnext;
}

void LListNode::set_next(LListNode *_next)
{
  pnext = _next;
}

list<Word>* LListNode::get(int part)
{
  int x = 0;
  LLNNode *ce = head;

  for (; x < part; x++) {
    if (ce->has_next()) {
      ce = ce->next();
    } else {
      return NULL;
    }
  }
  return ce->get();
}

int LListNode::size()
{
  int x = 0;
  LLNNode *ce = head;
  
  while(ce->has_next()){
    x += ce->size();
    ce = ce->next();
  }
  
  x += ce->size();
  return x;
}
