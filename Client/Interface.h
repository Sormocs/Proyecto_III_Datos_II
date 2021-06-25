#include "UI.h"
#include <string>

auto* ui = new UI();

void on_but1_clicked(GtkButton *button, gpointer user_data) {
    g_print("Bienvenido, %s.", gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(ui->getBuilder(), "entry1"))));
}

void on_window_destroy() {
    gtk_main_quit();
}

void Run(int& argc, char *argv[]) {


    gtk_init(&argc, &argv);

    ui->setBuilder(gtk_builder_new());
    gtk_builder_add_from_file (ui->getBuilder(), "../glade/glade.glade", NULL);

    ui->setWindow(GTK_WIDGET(gtk_builder_get_object(ui->getBuilder(), "window")));
    gtk_builder_connect_signals(ui->getBuilder(), NULL);

    ui->setEntry1(GTK_ENTRY(gtk_builder_get_object(ui->getBuilder(), "entry1")));
    ui->setEntry2(GTK_ENTRY(gtk_builder_get_object(ui->getBuilder(), "entry2")));

    ui->setBut1(GTK_BUTTON(gtk_builder_get_object(ui->getBuilder(), "but1")));
    ui->setBut2(GTK_BUTTON(gtk_builder_get_object(ui->getBuilder(), "but2")));

    g_signal_connect((ui->getWindow()), "destroy", G_CALLBACK(on_window_destroy), NULL);

    g_signal_connect((ui->getBut1()), "clicked", G_CALLBACK(on_but1_clicked), NULL);
    g_signal_connect((ui->getBut2()), "clicked", G_CALLBACK(on_window_destroy), NULL);

    g_object_unref(ui->getBuilder());

    gtk_widget_show(ui->getWindow());
    gtk_main();
}

