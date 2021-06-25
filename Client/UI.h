#include <gtk/gtk.h>

#define CheckBit(data, n) ((data) & 1UL << (n)) ? 1 : 0
#define SetBit(data, n) *(data) |= 1UL << (n)

class UI {
private:

    /* Orden de bits en boole
     *
     * 0. ventana principal activa
     * 1. ventana login activa
     * 2. sesión iniciada
     */
    int8_t boole =  0;

    GtkBuilder      *builder = nullptr;

    // login
    GtkWidget       *loginWin = nullptr;
    GtkButton       *loginBut1 = nullptr;
    GtkButton       *loginQuitBut1 = nullptr;
    GtkLabel        *loginLabStat1 = nullptr;
    GtkEntry        *loginEntry1 = nullptr;
    GtkEntry        *loginEntry2 = nullptr;

    // main window
    GtkWidget       *window = nullptr;
    GtkNotebook     *notebook1 = nullptr;
    GtkEntry        *dispNodo1 = nullptr;
    GtkEntry        *dispNodo2 = nullptr;
    GtkEntry        *dispNodo3 = nullptr;
    GtkEntry        *usadoNodo1 = nullptr;
    GtkEntry        *usadoNodo2 = nullptr;
    GtkEntry        *usadoNodo3 = nullptr;
    GtkEntry        *totalNodo1 = nullptr;
    GtkEntry        *totalNodo2 = nullptr;
    GtkEntry        *totalNodo3 = nullptr;
    GtkTreeView     *fileTree1 = nullptr;
    GtkListStore    *fileList1 = nullptr;
    GtkTextView     *fileContent1 = nullptr;
    GtkTextBuffer   *textBuffer1 = nullptr;
    GtkEntry        *fileNameEntry1 = nullptr;
    GtkTextView     *fileContent2 = nullptr;
    GtkTextBuffer   *textBuffer2 = nullptr;
    GtkButton       *addFileButton1 = nullptr;


public:
    UI(int &argc, char *argv[]) {
        gtk_init(&argc, &argv);

        this->builder = gtk_builder_new();

        gtk_builder_add_from_file(builder, "../glade/glade.glade", NULL);

        loginWin = GTK_WIDGET(gtk_builder_get_object(builder, "loginWin"));
        loginBut1 = GTK_BUTTON(gtk_builder_get_object(builder, "loginBut1"));
        loginQuitBut1 = GTK_BUTTON(gtk_builder_get_object(builder, "loginQuitBut1"));
        loginLabStat1 = GTK_LABEL(gtk_builder_get_object(builder, "loginLabStat1"));
        loginEntry1 = GTK_ENTRY(gtk_builder_get_object(builder, "loginEntry1"));
        loginEntry2 = GTK_ENTRY(gtk_builder_get_object(builder, "loginEntry2"));

        // ventana principal
        window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

        notebook1 = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook1"));

        dispNodo1 = GTK_ENTRY(gtk_builder_get_object(builder, "dispNodo1"));
        dispNodo2 = GTK_ENTRY(gtk_builder_get_object(builder, "dispNodo2"));
        dispNodo3 = GTK_ENTRY(gtk_builder_get_object(builder, "dispNodo3"));

        usadoNodo1 = GTK_ENTRY(gtk_builder_get_object(builder, "usadoNodo1"));
        usadoNodo2 = GTK_ENTRY(gtk_builder_get_object(builder, "usadoNodo2"));
        usadoNodo3 = GTK_ENTRY(gtk_builder_get_object(builder, "usadoNodo3"));

        totalNodo1 = GTK_ENTRY(gtk_builder_get_object(builder, "totalNodo1"));
        totalNodo2 = GTK_ENTRY(gtk_builder_get_object(builder, "totalNodo2"));
        totalNodo3 = GTK_ENTRY(gtk_builder_get_object(builder, "totalNodo3"));

        fileTree1 = GTK_TREE_VIEW(gtk_builder_get_object(builder, "fileTree1"));

        fileList1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "fileList1"));

        fileContent1 = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "fileContent1"));
        textBuffer1 = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBuffer1"));

        fileNameEntry1 = GTK_ENTRY(gtk_builder_get_object(builder, "fileNameEntry1"));

        fileContent2 = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "fileContent2"));
        textBuffer2 = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBuffer2"));

        addFileButton1 = GTK_BUTTON(gtk_builder_get_object(builder, "addFileButton1"));

        gtk_builder_connect_signals(builder, NULL);
    }

    int8_t getBoole() const {
        return boole;
    }

    void setBoole(int8_t boole) {
        UI::boole = boole;
    }

    GtkBuilder *getBuilder() const {
        return builder;
    }

    void setBuilder(GtkBuilder *builder) {
        UI::builder = builder;
    }

    GtkWidget *getLoginWin() const {
        return loginWin;
    }

    void setLoginWin(GtkWidget *loginWin) {
        UI::loginWin = loginWin;
    }

    GtkButton *getLoginBut1() const {
        return loginBut1;
    }

    void setLoginBut1(GtkButton *loginBut1) {
        UI::loginBut1 = loginBut1;
    }

    GtkButton *getLoginQuitBut1() const {
        return loginQuitBut1;
    }

    void setLoginQuitBut1(GtkButton *loginQuitBut1) {
        UI::loginQuitBut1 = loginQuitBut1;
    }

    GtkLabel *getLoginLabStat1() const {
        return loginLabStat1;
    }

    void setLoginLabStat1(GtkLabel *loginLabStat1) {
        UI::loginLabStat1 = loginLabStat1;
    }

    GtkEntry *getLoginEntry1() const {
        return loginEntry1;
    }

    void setLoginEntry1(GtkEntry *loginEntry1) {
        UI::loginEntry1 = loginEntry1;
    }

    GtkEntry *getLoginEntry2() const {
        return loginEntry2;
    }

    void setLoginEntry2(GtkEntry *loginEntry2) {
        UI::loginEntry2 = loginEntry2;
    }

    GtkWidget *getWindow() const {
        return window;
    }

    void setWindow(GtkWidget *window) {
        UI::window = window;
    }

    GtkNotebook *getNotebook1() const {
        return notebook1;
    }

    void setNotebook1(GtkNotebook *notebook1) {
        UI::notebook1 = notebook1;
    }

    GtkEntry *getDispNodo1() const {
        return dispNodo1;
    }

    void setDispNodo1(GtkEntry *dispNodo1) {
        UI::dispNodo1 = dispNodo1;
    }

    GtkEntry *getDispNodo2() const {
        return dispNodo2;
    }

    void setDispNodo2(GtkEntry *dispNodo2) {
        UI::dispNodo2 = dispNodo2;
    }

    GtkEntry *getDispNodo3() const {
        return dispNodo3;
    }

    void setDispNodo3(GtkEntry *dispNodo3) {
        UI::dispNodo3 = dispNodo3;
    }

    GtkEntry *getUsadoNodo1() const {
        return usadoNodo1;
    }

    void setUsadoNodo1(GtkEntry *usadoNodo1) {
        UI::usadoNodo1 = usadoNodo1;
    }

    GtkEntry *getUsadoNodo2() const {
        return usadoNodo2;
    }

    void setUsadoNodo2(GtkEntry *usadoNodo2) {
        UI::usadoNodo2 = usadoNodo2;
    }

    GtkEntry *getUsadoNodo3() const {
        return usadoNodo3;
    }

    void setUsadoNodo3(GtkEntry *usadoNodo3) {
        UI::usadoNodo3 = usadoNodo3;
    }

    GtkEntry *getTotalNodo1() const {
        return totalNodo1;
    }

    void setTotalNodo1(GtkEntry *totalNodo1) {
        UI::totalNodo1 = totalNodo1;
    }

    GtkEntry *getTotalNodo2() const {
        return totalNodo2;
    }

    void setTotalNodo2(GtkEntry *totalNodo2) {
        UI::totalNodo2 = totalNodo2;
    }

    GtkEntry *getTotalNodo3() const {
        return totalNodo3;
    }

    void setTotalNodo3(GtkEntry *totalNodo3) {
        UI::totalNodo3 = totalNodo3;
    }

    GtkTreeView *getFileTree1() const {
        return fileTree1;
    }

    void setFileTree1(GtkTreeView *fileTree1) {
        UI::fileTree1 = fileTree1;
    }

    GtkListStore *getFileList1() const {
        return fileList1;
    }

    void setFileList1(GtkListStore *fileList1) {
        UI::fileList1 = fileList1;
    }

    GtkTextView *getFileContent1() const {
        return fileContent1;
    }

    void setFileContent1(GtkTextView *fileContent1) {
        UI::fileContent1 = fileContent1;
    }

    GtkTextBuffer *getTextBuffer1() const {
        return textBuffer1;
    }

    void setTextBuffer1(GtkTextBuffer *textBuffer1) {
        UI::textBuffer1 = textBuffer1;
    }

    GtkEntry *getFileNameEntry1() const {
        return fileNameEntry1;
    }

    void setFileNameEntry1(GtkEntry *fileNameEntry1) {
        UI::fileNameEntry1 = fileNameEntry1;
    }

    GtkTextView *getFileContent2() const {
        return fileContent2;
    }

    void setFileContent2(GtkTextView *fileContent2) {
        UI::fileContent2 = fileContent2;
    }

    GtkTextBuffer *getTextBuffer2() const {
        return textBuffer2;
    }

    void setTextBuffer2(GtkTextBuffer *textBuffer2) {
        UI::textBuffer2 = textBuffer2;
    }

    GtkButton *getAddFileButton1() const {
        return addFileButton1;
    }

    void setAddFileButton1(GtkButton *addFileButton1) {
        UI::addFileButton1 = addFileButton1;
    }
};
