#include <fstream>
#include "ClientSock.h"

#define RAID_SIZE 1073741824

#define MAIN_WIN_BIT_INDEX 0
#define LOGIN_WIN_BIT_INDEX 1
#define LOGGED_IN_BIT_INDEX 2
#define RAID_ACTIVE_BIT_INDEX 3
#define DISC1_ACTIVE_BIT_INDEX 4
#define DISC2_ACTIVE_BIT_INDEX 5
#define DISC3_ACTIVE_BIT_INDEX 6
#define ADDED_FILE_BIT_INDEX 7
#define ABORT_BIT_INDEX 8

#define CheckBit(data, n) ((data) & 1 << (n)) ? true : false
#define PrintBits(byte) { for (int8_t i=(sizeof(int16_t)*8) - 1; i>=0; i--) { printf("%d", CheckBit((byte), (i))); } printf("\n"); }
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
 * 7. archivo añadido
 * 8. detener espera
 */
int16_t boole = 0;

UI *ui = nullptr;

void LoggedIn(GtkButton *button, gpointer user_data);

void ButtonExit(GtkButton *button, gpointer user_data);

void UpdateNodes(GtkButton *button, gpointer user_data);

void DisconnectDisc1(GtkButton *button, gpointer user_data);
void WaitDisconnectDisc1();

void DisconnectDisc2(GtkButton *button, gpointer user_data);
void WaitDisconnectDisc2();

void DisconnectDisc3(GtkButton *button, gpointer user_data);
void WaitDisconnectDisc3();

void SearchFile(GtkButton *button, gpointer user_data);
void WaitFileNames();

void AddFile(GtkButton *button, gpointer user_data);
void WaitAddFile();

void ReadFile(GtkButton *button, gpointer user_data);
void WaitReadFile();

void DeleteFile(GtkButton *button, gpointer user_data);
void WaitDelete();

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
    g_signal_connect(ui->getFileSearchButton(), "clicked", G_CALLBACK(SearchFile), NULL);
    g_signal_connect(ui->getDeleteSelectedFileButton(), "clicked", G_CALLBACK(DeleteFile), NULL);
    g_signal_connect(ui->getUpdateNodesButton(), "clicked", G_CALLBACK(UpdateNodes), NULL);

    gtk_notebook_set_current_page(ui->getNotebook1(), 0);

    boole = SetBit(boole, TRUE, LOGIN_WIN_BIT_INDEX);

//    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 1));
//    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 2));
//    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 3));
//    gtk_widget_hide(gtk_notebook_get_nth_page(ui->getNotebook1(), 4));

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

void Wait() {
    int8_t count = 0;
    while (ClientSock::getInstance()->jsonFile == nullptr && count <= 50) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        count++;

        g_print("En espera, intento %d.\n", count);
    }
}

void NameEdited(GtkEntry* entry, gpointer user_data) {
    std::string temp = gtk_entry_get_text(ui->getLoginEntry1());

    if (!temp.empty()) gtk_widget_set_sensitive((GtkWidget *)ui->getLoginBut1(), true);
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

void UpdateNodes(GtkButton *button, gpointer user_data) {
    json temp = json();
    temp["DISCONNECT"] = "NO";
    temp["ADD_FILE"]["NAME"] = "NO";
    temp["ADD_FILE"]["CONTENT"] = "NO";
    temp["READ_FILE"] = "NO";
    temp["SEARCH_FILE"] = "NO";
    temp["DELETE_FILE"] = "NO";
    temp["UPDATE"] = true;
    ClientSock::getInstance()->Send(temp.dump());

    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {

        gtk_label_set_text(ui->getDispNodo1(), "N/A");
        gtk_label_set_text(ui->getDispNodo2(), "N/A");
        gtk_label_set_text(ui->getDispNodo3(), "N/A");

        gtk_label_set_text(ui->getUsadoNodo1(), "N/A");
        gtk_label_set_text(ui->getUsadoNodo2(), "N/A");
        gtk_label_set_text(ui->getUsadoNodo3(), "N/A");

    } else {

        gtk_label_set_text(ui->getDispNodo1(), ClientSock::getInstance()->jsonFile["UPDATE"]["Node1"]["Available"].get<std::string>().c_str());
        gtk_label_set_text(ui->getDispNodo2(), ClientSock::getInstance()->jsonFile["UPDATE"]["Node2"]["Available"].get<std::string>().c_str());
        gtk_label_set_text(ui->getDispNodo3(), ClientSock::getInstance()->jsonFile["UPDATE"]["Node3"]["Available"].get<std::string>().c_str());

        gtk_label_set_text(ui->getUsadoNodo1(), ClientSock::getInstance()->jsonFile["UPDATE"]["Node1"]["Used"].get<std::string>().c_str());
        gtk_label_set_text(ui->getUsadoNodo2(), ClientSock::getInstance()->jsonFile["UPDATE"]["Node2"]["Used"].get<std::string>().c_str());
        gtk_label_set_text(ui->getUsadoNodo3(), ClientSock::getInstance()->jsonFile["UPDATE"]["Node3"]["Used"].get<std::string>().c_str());
    }

}

void DisconnectDisc1(GtkButton *button, gpointer user_data) {

    // intercambia conexión del disco
    json temp = json();
    temp["DISCONNECT"] = "DISC1";
    temp["ADD_FILE"]["NAME"] = "NO";
    temp["ADD_FILE"]["CONTENT"] = "NO";
    temp["READ_FILE"] = "NO";
    temp["SEARCH_FILE"] = "NO";
    temp["DELETE_FILE"] = "NO";
    temp["UPDATE"] = false;
    ClientSock::getInstance()->Send(temp.dump());

    WaitDisconnectDisc1();

    if (CheckBit(boole, DISC1_ACTIVE_BIT_INDEX)) {

        boole = SetBit(boole, false, DISC1_ACTIVE_BIT_INDEX);
        gtk_button_set_label(ui->getActiveButDisc1(), "Desconectar");
    }

    else{
        boole = SetBit(boole, false, DISC1_ACTIVE_BIT_INDEX);
        gtk_button_set_label(ui->getActiveButDisc1(), "Conectar");
    }
}

void WaitDisconnectDisc1() {
    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {

        boole = SetBit(boole, false, DISC1_ACTIVE_BIT_INDEX);

    } else {
        boole = SetBit(boole, ClientSock::getInstance()->jsonFile["DISC_STATE"]["DISC1"].get<bool>(), DISC1_ACTIVE_BIT_INDEX);
    }
    ClientSock::getInstance()->jsonFile = nullptr;
}

void DisconnectDisc2(GtkButton *button, gpointer user_data) {

    // intercambia conexión del disco
    json temp = json();
    temp["DISCONNECT"] = "DISC2";
    temp["DISC_STATE"] = "NO";
    temp["ADD_FILE"]["NAME"] = "NO";
    temp["ADD_FILE"]["CONTENT"] = "NO";
    temp["READ_FILE"] = "NO";
    temp["SEARCH_FILE"] = "NO";
    temp["DELETE_FILE"] = "NO";
    temp["UPDATE"] = false;
    ClientSock::getInstance()->Send(temp.dump());

    WaitDisconnectDisc2();

    if (CheckBit(boole, DISC2_ACTIVE_BIT_INDEX)) {

        boole = SetBit(boole, false, DISC2_ACTIVE_BIT_INDEX);
        gtk_button_set_label(ui->getActiveButDisc2(), "Desconectar");
    }

    else{
        boole = SetBit(boole, false, DISC2_ACTIVE_BIT_INDEX);
        gtk_button_set_label(ui->getActiveButDisc2(), "Conectar");
    }
}

void WaitDisconnectDisc2() {
    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {

        boole = SetBit(boole, false, DISC2_ACTIVE_BIT_INDEX);

    } else {
        boole = SetBit(boole, ClientSock::getInstance()->jsonFile["DISC_STATE"]["DISC2"].get<bool>(), DISC2_ACTIVE_BIT_INDEX);
    }
    ClientSock::getInstance()->jsonFile = nullptr;
}

void DisconnectDisc3(GtkButton *button, gpointer user_data) {

    // intercambia conexión del disco
    json temp = json();
    temp["DISCONNECT"] = "DISC3";
    temp["DISC_STATE"] = "NO";
    temp["ADD_FILE"]["NAME"] = "NO";
    temp["ADD_FILE"]["CONTENT"] = "NO";
    temp["READ_FILE"] = "NO";
    temp["SEARCH_FILE"] = "NO";
    temp["DELETE_FILE"] = "NO";
    temp["UPDATE"] = false;
    ClientSock::getInstance()->Send(temp.dump());

    WaitDisconnectDisc3();

    if (CheckBit(boole, DISC3_ACTIVE_BIT_INDEX)) {

        boole = SetBit(boole, false, DISC3_ACTIVE_BIT_INDEX);
        gtk_button_set_label(ui->getActiveButDisc3(), "Desconectar");
    }

    else{
        boole = SetBit(boole, false, DISC3_ACTIVE_BIT_INDEX);
        gtk_button_set_label(ui->getActiveButDisc3(), "Conectar");
    }
}

void WaitDisconnectDisc3() {
    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {

        boole = SetBit(boole, false, DISC3_ACTIVE_BIT_INDEX);

    } else {
        boole = SetBit(boole, ClientSock::getInstance()->jsonFile["DISC_STATE"]["DISC3"].get<bool>(), DISC3_ACTIVE_BIT_INDEX);
    }
    ClientSock::getInstance()->jsonFile = nullptr;
}

void AddFile(GtkButton *button, gpointer user_data) {
    std::string fileName = gtk_entry_get_text(ui->getFileNameEntry1());

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(ui->getTextBuffer1(), &start, &end);
    std::string fileContent = gtk_text_buffer_get_text(ui->getTextBuffer1(), &start, &end, false);

    if (fileName.empty() || fileContent.empty()) {

        gtk_label_set_text(ui->getFileCreatedLabel(), "Debe tener nombre y contenido");

    } else {

        json temp = json();

        temp["DISCONNECT"] = "NO";
        temp["DISC_STATE"] = "NO";
        temp["ADD_FILE"]["NAME"] = fileName;
        temp["ADD_FILE"]["CONTENT"] = fileContent;
        temp["READ_FILE"] = "NO";
        temp["SEARCH_FILE"] = "NO";
        temp["DELETE_FILE"] = "NO";
        temp["UPDATE"] = false;

        ClientSock::getInstance()->Send(temp);

        WaitAddFile();
    }
}

void WaitAddFile(){
    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {

        gtk_label_set_text(ui->getFileCreatedLabel(), "Error al guardar");

    } else {

        if (ClientSock::getInstance()->jsonFile["SAVED"].get<bool>()) gtk_label_set_text(ui->getFileCreatedLabel(), "Archivo guardado");
    }

}

void ReadFile(GtkButton *button, gpointer user_data) {

    if (gtk_combo_box_get_active(((GtkComboBox*)ui->getFileComboBox1())) == -1) {
        gtk_label_set_text(ui->getFileOpenedLabel(), "Seleccione un archivo");
    } else {

        std::string fileName = gtk_combo_box_text_get_active_text(ui->getFileComboBox1());

        g_print("%s", fileName.c_str());

        json temp = json();

        temp["DISCONNECT"] = "NO";
        temp["DISC_STATE"] = "NO";
        temp["ADD_FILE"]["NAME"] = "NO";
        temp["ADD_FILE"]["CONTENT"] = "NO";
        temp["READ_FILE"] = fileName;
        temp["SEARCH_FILE"] = "NO";
        temp["DELETE_FILE"] = "NO";
        temp["UPDATE"] = false;

        ClientSock::getInstance()->Send(temp.dump());

        WaitReadFile();
    }
}

void WaitReadFile() {

    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {

        gtk_label_set_text(ui->getFileOpenedLabel(), "Error al cargar archivo");

    } else {

        std::string content = ClientSock::getInstance()->jsonFile["Archivos"]["data"].get<std::string>();

        gtk_text_buffer_set_text(gtk_text_view_get_buffer(ui->getOpenFileContent()), content.c_str(), content.length());
    }
    ClientSock::getInstance()->jsonFile = nullptr;
}

void SearchFile(GtkButton *button, gpointer user_data) {
    std::string nombre = gtk_entry_get_text(&ui->getFileSearchBox1()->parent);
    if (nombre.empty()) {
        gtk_label_set_text(ui->getFileOpenedLabel(), "Debe introducir un nombre");

    } else {
        g_print("Hay texto, dice %s", nombre.c_str());
        json temp = json();

        temp["DISCONNECT"] = "NO";
        temp["DISC_STATE"] = "NO";
        temp["ADD_FILE"]["NAME"] = "NO";
        temp["ADD_FILE"]["CONTENT"] = "NO";
        temp["READ_FILE"] = "NO";
        temp["SEARCH_FILE"] = nombre;
        temp["DELETE_FILE"] = "NO";
        temp["UPDATE"] = false;

        ClientSock::getInstance()->Send(temp.dump());
        gtk_label_set_text(ui->getFileOpenedLabel(), "Búsqueda exitosa");

        WaitFileNames();
    }
}

void WaitFileNames() {
    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {
        gtk_label_set_text(ui->getFileOpenedLabel(), "Error en la búsqueda");
    } else {

        gtk_combo_box_text_remove_all(ui->getFileComboBox1());

        for (int i = 0; i < ClientSock::getInstance()->jsonFile["Archivos"]["size"].get<int>(); ++i) {

            std::string tempS = ClientSock::getInstance()->jsonFile["Archivos"][std::to_string(i)].get<std::string>();

            gtk_combo_box_text_insert(ui->getFileComboBox1(), i, nullptr, tempS.c_str());
        }
    }
    ClientSock::getInstance()->jsonFile = nullptr;
}

void DeleteFile(GtkButton *button, gpointer user_data) {
    if (gtk_combo_box_get_active(((GtkComboBox*)ui->getFileComboBox1())) == -1) {
        gtk_label_set_text(ui->getFileOpenedLabel(), "Seleccione un archivo");
    } else {
        json temp = json();

        temp["DISCONNECT"] = "NO";
        temp["DISC_STATE"] = "NO";
        temp["ADD_FILE"]["NAME"] = "NO";
        temp["ADD_FILE"]["CONTENT"] = "NO";
        temp["READ_FILE"] = "NO";
        temp["SEARCH_FILE"] = "NO";
        temp["DELETE_FILE"] = gtk_combo_box_text_get_active_text(ui->getFileComboBox1());
        temp["UPDATE"] = false;

        ClientSock::getInstance()->Send(temp.dump());

        WaitDelete();
    }
}

void WaitDelete() {
    Wait();

    if (ClientSock::getInstance()->jsonFile == nullptr) {
        gtk_label_set_text(ui->getFileOpenedLabel(), "Error al borrar");

    } else {
        if (ClientSock::getInstance()->jsonFile["DELETED"].get<bool>())
            gtk_label_set_text(ui->getFileOpenedLabel(), "Borrado con éxito");
    }
    ClientSock::getInstance()->jsonFile = nullptr;
}