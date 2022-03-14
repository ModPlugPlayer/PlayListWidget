#pragma once

#include <QMainWindow>
#include <QUrl>
#include <QList>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

    class MainWindow : public QMainWindow
{
    Q_OBJECT

         public:
             MainWindow(QWidget *parent = nullptr);
            ~MainWindow();
         public slots:
             void onFileDropped(QUrl fileUrl, int droppedIndex);
             void onFilesDropped(QList<QUrl> fileUrls, int droppedIndex);

         private slots:
                 void on_Add_clicked();

             void on_Remove_clicked();

         private:
    Ui::MainWindow *ui;
};
