#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Contact.h"
#include "ContactManager.h"
#include "buttonhandler.h"
#include "FileHandler.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_idOfDelete_editingFinished();

private:
    ContactManager manager;
    Ui::MainWindow *ui;
    ButtonHandler *buttonHandler;
    void connections();
};
#endif // MAINWINDOW_H
