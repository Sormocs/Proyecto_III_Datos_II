#include "UI.h"
#include <string>

UI *ui = nullptr;

void on_but1_clicked(GtkButton *button, gpointer user_data);

void on_window_destroy();

void Run() {


    g_signal_connect((ui->getWindow()), "destroy", G_CALLBACK(on_window_destroy), NULL);



    g_object_unref(ui->getBuilder());

    gtk_widget_show(ui->getWindow());
    gtk_main();
}

void SetInstance(UI* n_ui){
    ui = n_ui;
}

void on_window_destroy() {
    gtk_main_quit();
}

void on_but1_clicked(GtkButton *button, gpointer user_data) {
    gtk_label_set_text(ui->getLoginLabStat1(), "Bienvenido/a.");
}