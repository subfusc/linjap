#include "Mode_eng_jap.hpp"
#include <iostream>

Mode_eng_jap::Mode_eng_jap(LList *_db)
{
  db = _db;
  last = NULL;
  session = NULL;
}

Mode_eng_jap::~Mode_eng_jap()
{
  if (last) delete last;
  if (session) delete session;
}

void Mode_eng_jap::new_session(vector<Av> in)
{
    Mode::new_session(in);
}

ustring* Mode_eng_jap::start()
{
  cout << "start" << endl;
  last = session->pop();
  cout << "pop" << endl;
  
  ustring* return_string = new ustring[4];
  return_string[0] = last->get_wd1();
  return_string[1] = "";
  return_string[2] = "";
  return_string[3] = "nc";
  return return_string;
}

ustring* Mode_eng_jap::next(ustring lword)
{
  ustring* return_string = new ustring[4];

  switch (equals(lword)) {
  case 0: return_string[1] = last->get_wd2_alt(); return_string[3] = "c"; break;
  case 1: return_string[1] = last->get_wd2(); return_string[3] = "c"; break;
  case 2: 
    wrong(last); 
    return_string[1] = last->get_wd2_alt();
    return_string[3] = "nc";
    break;
  case 3: 
    wrong(last);
    return_string[1] = last->get_wd2(); 
    return_string[3] = "nc"; 
    break;
  default: 
    std::cerr << "something is wrong in the equals function" << std::endl;
    return_string[1] = ""; return_string[3] = "nc"; break;
  }
  
  delete last;
  
  Word *next;
  if (session->size()) {
    next = session->pop();
    last = next;
    return_string[0] = next->get_wd1();
  } else {
    last = NULL;
    return_string[0] = "End of Session";
  }
  
  
  return_string[2] = lword;
  
  return return_string;
}

/* Check if the in string contains kana characters only.
 * @param: ustring last_word - Ustring representation of the string last written by the user.
 * @return: boolean - contains only kana.
 */
bool Mode_eng_jap::kana(ustring lword)
{
    if ((lword.bytes()) % 3 == 0){
	const char * larr = lword.c_str();
	int x;
	for (x = 0; (unsigned int) x < lword.bytes(); x += 3) {
	    if ( ((int) larr[x]) != -29) return false;
	}
	return true;
    }
    return false;
}

/* Check if input and last word is the same.
 * @param: ustring last_word - Ustring representation of the string last written by the user.
 * @return: int - Returns 0 on equal w/kanji, returns 1 on equal w/kana only, returns 2 on false w/kanji, returns 3 on false w/kana only.
 */
int Mode_eng_jap::equals(ustring lword) 
{
    if (kana(lword)) {
	ustring last_wd = last->get_wd2();//Get last corret word hir/kat
	if (lword.bytes() != last_wd.bytes()) return 3;
	const char* u_c_str = lword.c_str();
	const char* l_cor_c_str = last_wd.c_str();
	int place;
	for  (place = 0; (unsigned int) place < lword.bytes(); place++) {
	    if (u_c_str[place] != l_cor_c_str[place]) return 3;
	}
	return 1;

    } else {
	ustring last_wd_kji = last->get_wd2_alt(); //Get last corret Kanji
	if (lword.bytes() != last_wd_kji.bytes()) return 2;
	cout << "Checking Kanji" << endl;
	const char* u_c_str = lword.c_str();
	const char* l_cor_kji = last_wd_kji.c_str();

	int place;
	for (place = 0; (unsigned int) place < last_wd_kji.bytes(); place++) {
	    if (u_c_str[place] != l_cor_kji[place]) return 2;
	} 
	return 0;
    }    
}
