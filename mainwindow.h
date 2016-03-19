#ifndef GTKMM_WINDOW_H
#define GTKMM_WINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    void FillBuffers();
    void AddCommandLine();
    void AddTabs();
    void AddTextView();
    void AddCompletionSet();

    //Signal handlers:
    void OnButtonBuffer1();
    void OnButtonBuffer2();
    void OnButtonRun();
    void OnCommand();

    //See the comment in the implementation:
    //bool on_completion_match(const Glib::ustring& key, const Gtk::TreeModel::const_iterator& iter)


    //Tree model columns, for the EntryCompletion's filter model:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelColumns()
        { add(m_col_id); add(m_col_name); }

        Gtk::TreeModelColumn<unsigned int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };

    ModelColumns m_Columns;

    typedef std::map<int, Glib::ustring> type_actions_map;
    type_actions_map m_CompletionActions;


    //Child widgets:
    Gtk::Box m_vBox;
    Gtk::Box m_hBox;

    //Toolbar
    Gtk::Entry m_entry;
    Gtk::Button m_buttonRun;

    //TextView
    Gtk::ScrolledWindow m_scrolledWindow;
    Gtk::TextView m_textView;

    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1, m_refTextBuffer2;

    Gtk::ButtonBox m_buttonBox;
    Gtk::Button m_buttonBuffer1, m_buttonBuffer2;
};

#endif //GTKMM_WINDOW_H
