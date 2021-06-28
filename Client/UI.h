/**
 * @file UI.h incluye la clase UI de la interfaz gráfica.
 */

#include <gtk/gtk.h>
#include "json.hpp"

using json = nlohmann::json;

class UI {
private:

    GtkBuilder      *builder = nullptr;

    GtkButton       *loginBut1 = nullptr;
    GtkButton       *loginQuitBut1 = nullptr;
    GtkLabel        *loginLabStat1 = nullptr;
    GtkEntry        *loginEntry1 = nullptr;
    GtkEntry        *loginEntry2 = nullptr;

    // main window
    GtkWidget       *window = nullptr;
    GtkNotebook     *notebook1 = nullptr;

    // info
    GtkButton       *updateNodesButton = nullptr;
    GtkLabel        *dispNodo1 = nullptr;
    GtkLabel        *dispNodo2 = nullptr;
    GtkLabel        *dispNodo3 = nullptr;
    GtkLabel        *usadoNodo1 = nullptr;
    GtkLabel        *usadoNodo2 = nullptr;
    GtkLabel        *usadoNodo3 = nullptr;
    GtkLabel        *totalNodo1 = nullptr;
    GtkLabel        *totalNodo2 = nullptr;
    GtkLabel        *totalNodo3 = nullptr;

    // pestaña de archivos
    GtkTextView     *fileContent1 = nullptr;
    GtkTextBuffer   *textBuffer1 = nullptr;
    GtkSearchEntry  *fileSearchBox1 = nullptr;
    GtkButton       *openFileButton1 = nullptr;
    GtkEntry        *fileNameEntry1 = nullptr;
    GtkComboBoxText *fileComboBox1 = nullptr;
    GtkButton       *addFileButton1 = nullptr;
    GtkLabel        *fileOpenedLabel = nullptr;
    GtkButton       *fileSearchButton = nullptr;
    GtkTextView     *openFileContent = nullptr;
    GtkTextBuffer   *textBuffer2 = nullptr;
    GtkLabel        *fileCreatedLabel = nullptr;
    GtkButton       *deleteSelectedFileButton = nullptr;

    // pestaña de raids
    GtkLabel        *activeLabRaid = nullptr;
    GtkLabel        *activeLabDisc1 = nullptr;
    GtkLabel        *activeLabDisc2 = nullptr;
    GtkLabel        *activeLabDisc3 = nullptr;
    GtkButton       *activeButDisc1 = nullptr;
    GtkButton       *activeButDisc2 = nullptr;
    GtkButton       *activeButDisc3 = nullptr;

public:

    /**
     * @brief UI es el constructor de la clase UI.
     * @param argc
     * @param argv
     */
    UI(int &argc, char *argv[]) {
        gtk_init(&argc, &argv);

        this->builder = gtk_builder_new();

        gtk_builder_add_from_file(builder, "../glade/glade.glade", NULL);

        GTK_WIDGET(gtk_builder_get_object(builder, "loginWin"));
        loginBut1 = GTK_BUTTON(gtk_builder_get_object(builder, "loginBut1"));
        loginQuitBut1 = GTK_BUTTON(gtk_builder_get_object(builder, "loginQuitBut1"));
        loginLabStat1 = GTK_LABEL(gtk_builder_get_object(builder, "loginLabStat1"));
        loginEntry1 = GTK_ENTRY(gtk_builder_get_object(builder, "loginEntry1"));
        loginEntry2 = GTK_ENTRY(gtk_builder_get_object(builder, "loginEntry2"));

        // ventana principal
        window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
        notebook1 = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook1"));

        // info
        updateNodesButton = GTK_BUTTON(gtk_builder_get_object(builder, "updateNodesButton"));
        dispNodo1 = GTK_LABEL(gtk_builder_get_object(builder, "dispNodo1"));
        dispNodo2 = GTK_LABEL(gtk_builder_get_object(builder, "dispNodo2"));
        dispNodo3 = GTK_LABEL(gtk_builder_get_object(builder, "dispNodo3"));
        usadoNodo1 = GTK_LABEL(gtk_builder_get_object(builder, "usadoNodo1"));
        usadoNodo2 = GTK_LABEL(gtk_builder_get_object(builder, "usadoNodo2"));
        usadoNodo3 = GTK_LABEL(gtk_builder_get_object(builder, "usadoNodo3"));
        totalNodo1 = GTK_LABEL(gtk_builder_get_object(builder, "totalNodo1"));
        totalNodo2 = GTK_LABEL(gtk_builder_get_object(builder, "totalNodo2"));
        totalNodo3 = GTK_LABEL(gtk_builder_get_object(builder, "totalNodo3"));

        // archivero
        fileSearchBox1 = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "fileSearchBox1"));
        openFileButton1 = GTK_BUTTON(gtk_builder_get_object(builder, "openFileButton1"));
        fileContent1 = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "fileContent1"));
        textBuffer1 = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBuffer1"));
        fileComboBox1 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "fileComboBox1"));
        fileNameEntry1 = GTK_ENTRY(gtk_builder_get_object(builder, "fileNameEntry1"));
        addFileButton1 = GTK_BUTTON(gtk_builder_get_object(builder, "addFileButton1"));
        fileOpenedLabel = GTK_LABEL(gtk_builder_get_object(builder, "fileOpenedLabel"));
        fileSearchButton = GTK_BUTTON(gtk_builder_get_object(builder, "fileSearchButton"));
        openFileContent = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "openFileContent"));
        textBuffer2 = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBuffer2"));
        fileCreatedLabel = GTK_LABEL(gtk_builder_get_object(builder, "fileCreatedLabel"));
        deleteSelectedFileButton = GTK_BUTTON(gtk_builder_get_object(builder, "deleteSelectedFileButton"));

        // administrador de discos
        activeButDisc1 = GTK_BUTTON(gtk_builder_get_object(builder, "activeButDisc1"));
        activeButDisc2 = GTK_BUTTON(gtk_builder_get_object(builder, "activeButDisc2"));
        activeButDisc3 = GTK_BUTTON(gtk_builder_get_object(builder, "activeButDisc3"));
        activeLabDisc1 = GTK_LABEL(gtk_builder_get_object(builder, "activeLabDisc1"));
        activeLabDisc2 = GTK_LABEL(gtk_builder_get_object(builder, "activeLabDisc2"));
        activeLabDisc3 = GTK_LABEL(gtk_builder_get_object(builder, "activeLabDisc3"));
        activeLabRaid = GTK_LABEL(gtk_builder_get_object(builder, "activeLabRaid"));

        gtk_builder_connect_signals(builder, NULL);
    }

    /**
     * @brief getLoginBut1 retorna el botón para iniciar sesión.
     * @return GtkButton
     */
    GtkButton *getLoginBut1() const {
        return loginBut1;
    }

    /**
     * @brief getLoginQuitBut1 retorna el botón de salida en el login.
     * @return GtkButton
     */
    GtkButton *getLoginQuitBut1() const {
        return loginQuitBut1;
    }

    /**
     * @brief getLoginLabStat1 retorna el Label con el estado del inicio de sesión
     * @return GtkLabel
     */
    GtkLabel *getLoginLabStat1() const {
        return loginLabStat1;
    }

    /**
     * @brief getLoginEntry1 retorna la casilla con el nombre del usuario.
     * @return GtkEntry
     */
    GtkEntry *getLoginEntry1() const {
        return loginEntry1;
    }

    /**
     * @brief getLoginEntry2 retorna la casilla con el apellido del usuario.
     * @return GtkEntry
     */
    GtkEntry *getLoginEntry2() const {
        return loginEntry2;
    }
    /**
     * @brief getWindow retorna la ventaja principal.
     * @return GtkWidget
     */
    GtkWidget *getWindow() const {
        return window;
    }

    /**
     * @brief getNotebook1 retorna la ventana con pestaña.
     * @return GtkNotebook
     */
    GtkNotebook *getNotebook1() const {
        return notebook1;
    }

    /**
     * @brief getDispNodo1 retorna la disponibilidad del nodo-disco 1.
     * @return GtkLabel
     */
    GtkLabel *getDispNodo1() const {
        return dispNodo1;
    }

    /**
     * @brief getDispNodo2 retorna la disponibilidad del nodo-disco 2.
     * @return GtkLabel
     */
    GtkLabel *getDispNodo2() const {
        return dispNodo2;
    }

    /**
     * @brief getDispNodo3 retorna la disponibilidad del nodo-disco 3.
     * @return GtkLabel
     */
    GtkLabel *getDispNodo3() const {
        return dispNodo3;
    }

    /**
     * @brief getUsadoNodo1 retorna el uso del nodo-disco 1.
     * @return GtkLabel
     */
    GtkLabel *getUsadoNodo1() const {
        return usadoNodo1;
    }

    /**
     * @brief getUsadoNodo2 retorna el uso del nodo-disco 2.
     * @return GtkLabel
     */
    GtkLabel *getUsadoNodo2() const {
        return usadoNodo2;
    }

    /**
     * @brief getUsadoNodo3 retorna el uso del nodo-disco 3.
     * @return GtkLabel
     */
    GtkLabel *getUsadoNodo3() const {
        return usadoNodo3;
    }

    /**
     * @brief getTotaloNodo1 retorna el total del nodo-disco 1.
     * @return GtkLabel
     */
    GtkLabel *getTotalNodo1() const {
        return totalNodo1;
    }

    /**
     * @brief getTotaloNodo2 retorna el total del nodo-disco 2.
     * @return GtkLabel
     */
    GtkLabel *getTotalNodo2() const {
        return totalNodo2;
    }

    /**
     * @brief getTotaloNodo3 retorna el total del nodo-disco 3.
     * @return GtkLabel
     */
    GtkLabel *getTotalNodo3() const {
        return totalNodo3;
    }

    /**
     * @brief getFileContent1 retorna la caja con el contenido del archivo a guardar.
     * @return GtkTextView
     */
    GtkTextView *getFileContent1() const {
        return fileContent1;
    }

    /**
     * @brief getTextBuffer1 retorna el buffer de texto de fileContent1.
     * @return GtkTextBuffer
     */
    GtkTextBuffer *getTextBuffer1() const {
        return textBuffer1;
    }

    /**
     * @brief getFileSearchBox1 retorna la caja de búsqueda para nombres de archivos.
     * @return GtkSearchEntry
     */
    GtkSearchEntry *getFileSearchBox1() const {
        return fileSearchBox1;
    }

    /**
     * @brief getOpenFileButton1 retorna el botón para abrir el archivo.
     * @return
     */
    GtkButton *getOpenFileButton1() const {
        return openFileButton1;
    }

    /**
     * @brief getFileNameEntry1 retorna el nombre del archivo a guardar.
     * @return GtkEntry
     */
    GtkEntry *getFileNameEntry1() const {
        return fileNameEntry1;
    }

    /**
     * @brief getFileComboBox1 retorna la lista desplegable
     * @return GtkComboBoxText
     */
    GtkComboBoxText *getFileComboBox1() const {
        return fileComboBox1;
    }

    /**
     * @brief getAddFileButton1 retorna el  botón para crear un archivo.
     * @return GtkButton
     */
    GtkButton *getAddFileButton1() const {
        return addFileButton1;
    }

    /**
     * @brief getFileOpenedLabel retorna el Label que dice si el archivo se abrió o no.
     * @return GtkLabel
     */
    GtkLabel *getFileOpenedLabel() const {
        return fileOpenedLabel;
    }

    GtkLabel *getActiveLabRaid() const {
        return activeLabRaid;
    }

    GtkLabel *getActiveLabDisc1() const {
        return activeLabDisc1;
    }

    GtkLabel *getActiveLabDisc2() const {
        return activeLabDisc2;
    }

    GtkLabel *getActiveLabDisc3() const {
        return activeLabDisc3;
    }

    GtkButton *getActiveButDisc1() const {
        return activeButDisc1;
    }

    GtkButton *getActiveButDisc2() const {
        return activeButDisc2;
    }

    GtkButton *getActiveButDisc3() const {
        return activeButDisc3;
    }

    GtkButton *getFileSearchButton() const {
        return fileSearchButton;
    }

    GtkButton *getUpdateNodesButton() const {
        return updateNodesButton;
    }

    GtkTextView *getOpenFileContent() const {
        return openFileContent;
    }

    GtkTextBuffer *getTextBuffer2() const {
        return textBuffer2;
    }

    GtkLabel *getFileCreatedLabel() const {
        return fileCreatedLabel;
    }

    GtkButton *getDeleteSelectedFileButton() const {
        return deleteSelectedFileButton;
    }
};