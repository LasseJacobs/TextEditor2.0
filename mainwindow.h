#ifndef GTKMM_WINDOW_H
#define GTKMM_WINDOW_H

#include <gtkmm.h>
#include <string>
#include <vector>
#include "commandhandler.h"

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

    //Interface
    void SetCurrentBuffer(std::string content);
    std::string GetCurrentBuffer() const;
    std::string GetCurrentFileName() const;

    void Log(const char* message);
    void ErrorLog(const char* message);

protected:
    //Functions
    void AddNewTab();
    void AddTextView(Gtk::Box* box);
    //GUI
    void AddCommandLine();
    void AddTabs();
    void AddCompletionSet();
    void AddStatusBar();

    //Signal handlers:
    void OnNoteBookSwitchPage(Gtk::Widget* page, guint page_num);
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
    Gtk::Box m_statusBox;

    //Toolbar
    Gtk::Entry m_entry;
    Gtk::Button m_buttonRun;

    //TextView
    Gtk::Notebook m_notebook;

    //Status
    Gtk::Label m_outputLog;
    CommandHandler m_cmdHandler;
};

#endif //GTKMM_WINDOW_H
