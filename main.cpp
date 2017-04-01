#include <iostream>
#include <gtkmm.h>
#include "graff.h"
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{

   Glib::RefPtr<Gtk::Application>
   app =Gtk::Application::create(argc, argv,"org.gtkmm.examples.base");

    Glib::RefPtr<Gtk::Builder> kurucu = Gtk::Builder::create_from_file("C:\\Users\\tugrul\\Desktop\\prolabson\\arayuz.glade");



    Gtk::Window* pencere;
    kurucu->get_widget("window1",pencere);

    Gtk::Entry* boyut_entry;
    kurucu->get_widget("entry1",boyut_entry);

    Gtk::Entry* dugum_entry;
    kurucu->get_widget("entry2",dugum_entry);

    Gtk::Button* buton;
    kurucu->get_widget("button1",buton);

    Gtk::Label* hata_mesaji;
    kurucu->get_widget("label5",hata_mesaji);

    Gtk::Label* kruskal_mesaj;
    kurucu->get_widget("label3",kruskal_mesaj);

    Gtk::TextView *kruskal_text;
    kurucu->get_widget("textview2", kruskal_text);



    buton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(&buton_tiklama), boyut_entry,dugum_entry,hata_mesaji,kruskal_mesaj,kruskal_text));

    return app->run(*pencere);

}
