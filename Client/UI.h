#include <gtk/gtk.h>


class UI {
private:
    GtkBuilder      *builder = nullptr;
    GtkWidget       *window = nullptr;
    GtkEntry        *entry1 = nullptr;
    GtkEntry        *entry2 = nullptr;
    GtkButton       *but1 = nullptr;
    GtkButton       *but2 = nullptr;

public:
    UI() = default;

    GtkBuilder* getBuilder() { return builder; }

    GtkWidget *getWindow() const {return window;}

    GtkEntry *getEntry1() const {return entry1;}

    GtkEntry *getEntry2() const {return entry2;}

    GtkButton *getBut1() const {return but1;}

    GtkButton *getBut2() const {return but2;}

    void setBuilder(GtkBuilder *builder) {UI::builder = builder;}

    void setWindow(GtkWidget *window) {UI::window = window;}

    void setEntry1(GtkEntry *entry1) {UI::entry1 = entry1;}

    void setEntry2(GtkEntry *entry2) {UI::entry2 = entry2;}

    void setBut1(GtkButton *but1) {UI::but1 = but1;}

    void setBut2(GtkButton *but2) {UI::but2 = but2;}
};