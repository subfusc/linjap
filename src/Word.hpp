#ifndef WORD_HPP
#define WORD_HPP

#include <glibmm/ustring.h>
using namespace std;
using namespace Glib;

class Word {
  ustring wd1;
  ustring wd2;
  ustring wd2_alt;

public:
  Word(ustring _wd1, ustring _wd2, ustring _wd2_alt);
  Word(string _wd1, string _wd2, string _wd2_alt);
  Word(Word *in);
  ~Word();

  ustring get_wd1();
  ustring get_wd2();
  ustring get_wd2_alt();
};

#endif
