#include "NeWindow.hpp"

NeWindow::NeWindow(Engine *_en)
  :b_cancel(Stock::CANCEL),
   b_ok(Stock::OK)
{
  cout << "NeWindow::NeWindow(Engine)" << endl;
  // Set variables
  en = _en;
  
  // Set window properties
  set_title("Linjap 2 :: New Session");
  set_border_width(5);
  set_default_size(400, 300);
  //set_icon_from_file("src/jping.png");

  // Get data from the db
  Data *data; 
  if((data = en->get_data())) { 
    
    // Packing widgets
    swindow.add(tview);
    swindow.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);    

    // Create Tree Model
    tmodel = TreeStore::create(columns);
    tview.set_model(tmodel);

    // Fill the Tree
    TreeModel::Row row;
    TreeModel::Row crow;
    vector<string> *chap_names = data->get_chap_names();
    vector<string> *part_names = data->get_part_names();
    int x, y;
    
    for (x = 0; x < data->length_x(); x++) {
      for (y = 0; y < data->length_y(); y++) {
	if (y == 0) {
	  if (data->get_place(x, y)) {
	    row = *(tmodel->append());
	    row[columns.m_col_chap] = x + 1;
	    row[columns.m_col_part] = y;
	    if ((unsigned int) x < chap_names->size()) {
	      string cname = chap_names->at(x);
	      if (cname.size() > 0) {
		row[columns.m_col_name] = cname;
	      } else {
		ostringstream oss;
		oss << "Chapter " << (x + 1);
		row[columns.m_col_name] = oss.str();
	      }
	    } else {
	      ostringstream oss;
	      oss << "Chapter " << (x + 1);
	      row[columns.m_col_name] = oss.str();
	    }
	  } else break;
	} else {
	  if (data->get_place(x, y)) {
	    crow = *(tmodel->append(row.children()));
	    crow[columns.m_col_chap] = x + 1;
	    crow[columns.m_col_part] = y;
	    if ((unsigned int) (y - 1) < part_names->size()) {
	      string pname = part_names->at(y - 1);
	      if (pname.size() > 0) {
		crow[columns.m_col_name] = pname;
	      } else {
		ostringstream oss;
		oss << "Part " << (x + 1);
		crow[columns.m_col_name] = oss.str();
	      }
	    } else {
	      ostringstream oss;
	      oss << "Part " << (x + 1);
	      crow[columns.m_col_name] = oss.str();
	    }}}}}
    
    tview.append_column("Chapter", columns.m_col_chap);
    tview.append_column("Name", columns.m_col_name);
    tview.append_column_editable("Add", columns.m_col_bools);
    tview.append_column("Part", columns.m_col_part);
    vbox.pack_start(swindow);
  } else {
    //tmodel = NULL;
    vbox.pack_start(*(new Label("NO DICT LOADED YET")), PACK_SHRINK);
  }
  
  bbox.pack_start(b_ok, PACK_SHRINK);
  bbox.pack_start(b_cancel, PACK_SHRINK);

  vbox.pack_start(bbox, PACK_SHRINK);

  add(vbox);

  // Set Widget Properties
  bbox.set_border_width(5);
  bbox.set_layout(BUTTONBOX_END);

  // Connect Signals
  b_cancel.signal_clicked().connect(sigc::mem_fun(*this,
						  &NeWindow::on_button_cancel));
  b_ok.signal_clicked().connect(sigc::mem_fun(*this,
					      &NeWindow::on_button_ok));

  show_all_children();
  delete data;
  
}

NeWindow::~NeWindow()
{
  ;
}

typedef TreeModel::Children t_ch;
typedef TreeModel::Row t_row;

void NeWindow::on_button_ok()
{
  cout << "Ok Button Pressed" << endl;
  if (!tmodel) {
    hide();
    return;
  }

  vector<Av> vec;
  t_ch ch = tmodel->children();
  for (t_ch::iterator iter = ch.begin();
       iter != ch.end(); ++iter)
    {
      cout << "Iterating" << endl;
      t_row row = *iter;

      if (row[columns.m_col_bools]) {
	cout << "adding iter" << endl;
	Av tmp;
	tmp.chapter = row[columns.m_col_chap] - 1;
	tmp.part = row[columns.m_col_part] - 1;
	vec.push_back(tmp);
      } else {
	
	t_ch rch = row.children();
	
	for (t_ch::iterator riter = rch.begin();
	     riter != rch.end(); ++riter)
	  {
	    cout << "Riterating" << endl;
	    t_row rrow = *riter;

	    if (rrow[columns.m_col_bools]) {
	      cout << "adding riter" << endl;
	      Av tmp;
	      tmp.chapter = rrow[columns.m_col_chap] - 1;
	      tmp.part = rrow[columns.m_col_part] - 1;
	      vec.push_back(tmp);
	    }
	  }
      }
    }

  cout << "Vec Size: " << vec.size() << endl;
  for (int x = 0; (unsigned int) x < vec.size(); x++) {
    cout << "vec[" << x << "] = " << vec[x].chapter <<
      ", " << vec[x].part << "." << endl;
  }
  
  
  en->prepare_session(vec);
  hide();
}

void NeWindow::on_button_cancel()
{
  cout << "Cancel Button Pressed" << endl;
  hide();
}
