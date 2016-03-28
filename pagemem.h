#ifndef PAGE_MEM_H
#define PAGE_MEM_H

struct page_mem{
    Gtk::Label* nameLabel;
    Gtk::Button* closeButton;

    Gtk::ScrolledWindow* scrolledWindow;
    Gtk::TextView* textView;
};

#endif
