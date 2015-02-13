#include "LLNNode.hpp"

LLNNode::LLNNode()
{
  pnext = NULL;
}

LLNNode::~LLNNode() 
{
  ;
}

bool LLNNode::add(Word in)
{
  words.push_back(in);
  return true;
}

bool LLNNode::has_next()
{
  return pnext != NULL;
}

LLNNode* LLNNode::next() 
{
  return pnext;
}

void LLNNode::set_next(LLNNode *in)
{
  pnext = in;
}

list<Word>* LLNNode::get()
{
  return new list<Word>(words);
}

int LLNNode::size()
{
  return words.size();
}
