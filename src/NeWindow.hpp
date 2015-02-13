#ifndef NEWINDOW_HPP
#define NEWINDOW_HPP

#include "Engine.hpp"
#include "Data.hpp"
#include "Av.hpp"

#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <vector>
#include <sstream>

using namespace Gtk;
using namespace std;

class NeWindow : public Window
{
  // Variable
  Engine *en;

  // ColumRecord for this spesific window.
  class ModelColumns : public TreeModel::ColumnRecord
  {
  public:
    ModelColumns()
    { add(m_col_chap); add(m_col_part); 
      add(m_col_bools); add(m_col_name); }
    
    TreeModelColumn<int> m_col_chap;
    TreeModelColumn<int> m_col_part;
    TreeModelColumn<Glib::ustring> m_col_name;
    TreeModelColumn<bool> m_col_bools;
  };

  // Child Widgets
  ModelColumns columns;
  VBox vbox;
  ScrolledWindow swindow;
  TreeView tview;
  Glib::RefPtr<TreeStore> tmodel;
  HButtonBox bbox;
  Button b_cancel;
  Button b_ok;
  
  // Signal Handlers
  void on_button_cancel();
  void on_button_ok();
  
public:
  NeWindow(Engine *_en);
  ~NeWindow();

};

#endif
