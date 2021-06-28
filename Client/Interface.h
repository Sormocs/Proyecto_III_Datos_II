#include <fstream>
#include "UI.h"

#define RAID_SIZE 1073741824

#define MAIN_WIN_BIT_INDEX 0
#define LOGIN_WIN_BIT_INDEX 1
#define LOGGED_IN_BIT_INDEX 2
#define RAID_ACTIVE_BIT_INDEX 3
#define DISC1_ACTIVE_BIT_INDEX 4
#define DISC2_ACTIVE_BIT_INDEX 5
#define DISC3_ACTIVE_BIT_INDEX 6

#define CheckBit(data, n) ((data) & 1 << (n)) ? 1 : 0
#define PrintBits(byte) { for (int8_t i=(sizeof(int8_t)*8) - 1; i>=0; i--) { printf("%d", CheckBit((byte), (i))); } printf("\n"); }
#define SetBit(data, value, n) ((value)) ? ((data) | 1 << (n)) : ((data) & ~(1 << (n)))
#define ToggleBit(data, n) (CheckBit((data), (n))) ? SetBit((data), false, (n)) : SetBit((data), true, (n))

/* Orden de bits en boole
 *
 * 0. ventana principal activa
 * 1. ventana login activa
 * 2. sesión iniciada
 * 3. RAID activo
 * 4. disco1 activo
 * 5. disco2 activo
 * 6. disco3 activo
 */
int8_t boole = 0;

UI *ui = nullptr;

void LoggedIn(GtkButton *button, gpointer user_data);

void ButtonExit(GtkButton *button, gpointer user_data);

void DisconnectDisc1(GtkButton *button, gpointer user_data);
void DisconnectDisc2(GtkButton *button, gpointer user_data);
void DisconnectDisc3(GtkButton *button, gpointer user_data);

void AddFile(GtkButton *button, gpointer user_data);

void ReadFile(GtkButton *button, gpointer user_data);

void NameEdited(GtkEntry* entry, gpointer user_data);

void Exit();

void Run() {

    g_signal_connect(ui->getWindow(), "destroy", G_CALLBACK(Exit), NULL);
    g_signal_connect(ui->getLoginBut1(), "clicked", G_CALLBACK(LoggedIn), NULL);
    g_signal_connect(ui->getLoginQuitBut1(), "clicked", G_CALLBACK(ButtonExit), NULL);
    g_signal_connect(ui->getLoginEntry1(), "insert-text", G_CALLBACK(NameEdited), NULL);
    g_signal_connect(ui->getActiveButDisc1(), "clicked", G_CALLBACK(DisconnectDisc1), NULL);
    g_signal_connect(ui->getActiveButDisc2(), "clicked", G_CALLBACK(DisconnectDisc2), NULL);
    g_signal_connect(ui->getActiveButDisc3(), "clicked", G_CALLBACK(DisconnectDisc3), NULL);
    g_signal_connect(ui->getOpenFileButton1(), "clicked", G_CALLBACK(ReadFile), NULL);
    g_signal_connect(ui->getAddFileButton1(), "clicked", G_CALLBACK(AddFile), NULL);

    gtk_notebook_set_current_page(ui->getNotebook1(), 0);

    boole = SetBit(boole, TRUE, LOGIN_WIN_BIT_INDEX);

    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 1));
    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 2));
    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 3));
    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 4));

    gtk_widget_set_sensitive((GtkWidget*)(ui->getLoginBut1()), false);

    gtk_widget_show(ui->getWindow());
    gtk_main();
}

void SetInstance(UI* n_ui){
    ui = n_ui;
}

void ButtonExit(GtkButton *button, gpointer user_data) {
    gtk_main_quit();
}

void Exit() {
    gtk_main_quit();
}

void LoggedIn(GtkButton *button, gpointer user_data) {

    gtk_widget_show(gtk_notebook_get_nth_page(ui->getNotebook1(), 1));
    gtk_widget_show(gtk_notebook_get_nth_page(ui->getNotebook1(), 2));
    gtk_widget_show(gtk_notebook_get_nth_page(ui->getNotebook1(), 3));
    gtk_widget_show(gtk_notebook_get_nth_page(ui->getNotebook1(), 4));

    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 0));

    boole = SetBit(boole, false, LOGIN_WIN_BIT_INDEX);
    boole = SetBit(boole, true, MAIN_WIN_BIT_INDEX);
    boole = SetBit(boole, true, LOGGED_IN_BIT_INDEX);

}

void DisconnectDisc1(GtkButton *button, gpointer user_data) {

    // intercambia conexión del disco

    boole = ToggleBit(boole, DISC1_ACTIVE_BIT_INDEX);

    if (CheckBit(boole, DISC1_ACTIVE_BIT_INDEX)) gtk_button_set_label(ui->getActiveButDisc1(), "Desconectar");

    else gtk_button_set_label(ui->getActiveButDisc1(), "Conectar");
}

void DisconnectDisc2(GtkButton *button, gpointer user_data) {
    // intercambia conexión del disco

    boole = ToggleBit(boole, DISC2_ACTIVE_BIT_INDEX);

    if (CheckBit(boole, DISC2_ACTIVE_BIT_INDEX)) gtk_button_set_label(ui->getActiveButDisc2(), "Desconectar");

    else gtk_button_set_label(ui->getActiveButDisc2(), "Conectar");
}

void DisconnectDisc3(GtkButton *button, gpointer user_data) {
    // intercambia conexión del disco

    boole = ToggleBit(boole, DISC3_ACTIVE_BIT_INDEX);

    if (CheckBit(boole, DISC3_ACTIVE_BIT_INDEX)) gtk_button_set_label(ui->getActiveButDisc3(), "Desconectar");

    else gtk_button_set_label(ui->getActiveButDisc3(), "Conectar");
}

void NameEdited(GtkEntry* entry, gpointer user_data) {
    std::string temp = gtk_entry_get_text(ui->getLoginEntry1());

    if (!temp.empty()) gtk_widget_set_sensitive((GtkWidget *)ui->getLoginBut1(), true);
}

void AddFile(GtkButton *button, gpointer user_data) {
    const char* temp = reinterpret_cast<const char *>(gtk_entry_get_text(ui->getFileNameEntry1()));

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(ui->getTextBuffer1(), &start, &end);

    std::ofstream file;
    file.open("../" + (std::string) temp +".txt");
    file << gtk_text_buffer_get_text(ui->getTextBuffer1(), &start, &end, false);
    file.close();
    free((void *) temp);
}

void ReadFile(GtkButton *button, gpointer user_data) {

//    std::ifstream file;
//    file.open("../" + gtk_combo_box_text_get_active_text(ui->getFileComboBox1()) + ".txt");

    g_print("%s", gtk_combo_box_text_get_active_text(ui->getFileComboBox1()));
}