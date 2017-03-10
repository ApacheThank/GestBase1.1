#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVector>
#include <QDebug>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QTextStream>
#include <QSqlRecord>
 #include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    /**
     * @brief on_pushButtonExit_clicked
     * button to close the program
     */
    void on_pushButtonExit_clicked();
    /**
     * @brief chargerBases
     * load the databases of the user
     */
    void chargerBases();
    /**
     * @brief chargerTables
     * load the tables of selected database
     */
    void chargerTables();
    /**
     * @brief chargerChamps
     * load the fields of selected table
     */
    void chargerChamps();
    /**
     * @brief on_comboBoxBaseListe_activated
     * get the current database name and allows to effect the function
     * chargerTables for selected database
     * @param arg1 return the value of item activated
     */
    void on_comboBoxBaseListe_activated(const QString &arg1);
    /**
     * @brief on_tableWidgetTableListe_itemPressed
     * @param item call to function chargerChamps and get fields for item pressed
     */
    void on_tableWidgetTableListe_itemPressed(QTableWidgetItem *item);
    /**
     * @brief on_textEdit_textChanged
     * the entered text get like a query and then verify
     * is the requete true shows the result, and could be added to query history
     */
    void on_textEdit_textChanged();
    /**
     * @brief on_pushButtonAddToHistory_clicked
     * add the correct query to history
     */
    void on_pushButtonAddToHistory_clicked();
    /**
     * @brief on_pushButtonSave_clicked
     * save the query history
     */
    void on_pushButtonSave_clicked();
    /**
     * @brief on_pushButtonLoad_clicked
     * load the file
     */
    void on_pushButtonLoad_clicked();
    /**
     * @brief on_pushButtonExport_clicked
     * allows to export the result in file csv
     */
    void on_pushButtonExport_clicked();
    /**
     * @brief on_listWidgetHistory_doubleClicked
     * @param index return the value of listWidgetHistory
     * and put him in the textEdit
     */
    void on_listWidgetHistory_doubleClicked(const QModelIndex &index);

    void on_colorButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
