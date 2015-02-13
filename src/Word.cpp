#include "Word.hpp"

Word::Word(ustring _wd1, ustring _wd2, ustring _wd2_alt)
{
  wd1 = _wd1;
  wd2 = _wd2;
  wd2_alt = _wd2_alt;
}

Word::Word(string _wd1, string _wd2, string _wd2_alt)
{
  wd1 = _wd1;
  wd2 = _wd2;
  wd2_alt = _wd2_alt;
}

Word::Word(Word *in) 
{
  wd1 = in->get_wd1();
  wd2 = in->get_wd2();
  wd2_alt = in->get_wd2_alt();
}

Word::~Word() 
{
  ;
}

ustring Word::get_wd1()
{
  return wd1;
}

ustring Word::get_wd2()
{
  return wd2;
}

ustring Word::get_wd2_alt()
{
  return wd2_alt;
}
