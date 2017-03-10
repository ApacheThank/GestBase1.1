#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QInputDialog>
#include <QSqlDatabase>
#include <string>
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <QTextCodec>
#include <QSqlError>
#include "dialogconnect.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chargerBases();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonExit_clicked()
{
    qDebug()<<"MainWindow::on_pushButtonExit_clicked()";
    close();
}

// fonction qui charge les bases
void MainWindow::chargerBases()
{
    qDebug()<<"MainWindow::chargerBases()";
    QSqlQuery laRequete("show databases;");
    while(laRequete.next())
    {
        QString nomDb=laRequete.value(0).toString();
        ui->comboBoxBaseListe->addItem(nomDb);
    qDebug()<<nomDb;
    }
}

// fonction qui renvoie les tables de la base
void MainWindow::chargerTables()
{
    qDebug()<<"MainWindow::chargerTables()";
    int noLigne=0;
    QSqlQuery maRequete("show tables;");
    while(maRequete.next())
    {
    QSqlRecord fields = maRequete.record();
    for(int noField=0;noField<fields.count();noField++)
    {
        ui->tableWidgetTableListe->setColumnCount(fields.count());
        // on donne le nom de colonne
        ui->tableWidgetTableListe->setHorizontalHeaderItem(noField,new QTableWidgetItem(fields.fieldName(noField)));
        QString lesTables=maRequete.value(0).toString();
        qDebug()<<lesTables;
        QTableWidgetItem *mesTables = new QTableWidgetItem(lesTables);
        ui->tableWidgetTableListe->setRowCount(noLigne+1);
        ui->tableWidgetTableListe->setItem(noLigne,noField,mesTables);
        }
        //on passe à la ligne suivante
        noLigne++;
   }
}


// fonction qui renvoie les champs de la table
void MainWindow::chargerChamps()
{
    qDebug()<<"MainWindow::chargerChamps()";
    int noLigne=0;
    QTableWidgetItem *uneTable= ui->tableWidgetTableListe->currentItem();
    QString laTable= uneTable->data(Qt::DisplayRole).toString();
    QSqlQuery maRequete;
    QString texteRequete = "show fields from "+laTable+";";
    qDebug()<<texteRequete;
    maRequete.exec(texteRequete);
    QSqlRecord fields=maRequete.record();
    while(maRequete.next())
    {

    for(int noField=0; noField<fields.count();noField++){
        ui->tableWidgetChampListe->setColumnCount(fields.count());
        // on donne le nom de colonne
        ui->tableWidgetChampListe->setHorizontalHeaderItem(noField,new QTableWidgetItem(fields.fieldName(noField)));
        // recuperation de resultat
        QString resultat=maRequete.value(noField).toString();
        qDebug()<<resultat;
        QTableWidgetItem *Resultat = new QTableWidgetItem(resultat);
        ui->tableWidgetChampListe->setRowCount(noLigne+1);
        ui->tableWidgetChampListe->setItem(noLigne,noField,Resultat);
        }
        //on passe à la ligne suivante
        noLigne++;
   }
}


// fonction qui change la base lors de la changement dans comboBox
void MainWindow::on_comboBoxBaseListe_activated(const QString &arg1)
{
    qDebug()<<"MainWindow::on_comboBoxBaseListe_activated(const QString &arg1)";
    QString laBase= ui->comboBoxBaseListe->currentText();
    QSqlQuery laRequete;
    QString texteRequete = "use "+laBase+";";
    qDebug()<<texteRequete;
    laRequete.exec(texteRequete);
    chargerTables();
}


//fonction qui affiche les champs de la table lors de la selection
void MainWindow::on_tableWidgetTableListe_itemPressed(QTableWidgetItem *item)
{
    qDebug()<<"MainWindow::on_tableWidgetTableListe_itemPressed(QTableWidgetItem *item)";
    chargerChamps();
}



// fonction qui execute la requete
void MainWindow::on_textEdit_textChanged()
{
    qDebug()<<"MainWindow::on_textEdit_textChanged()";
    // on nettoie la zone de résultat
    ui->tableWidgetResultat->clear();
    ui->tableWidgetResultat->setRowCount(0);
    ui->tableWidgetResultat->setColumnCount(0);
    QString requete = ui->textEdit->toPlainText();
    QSqlQuery laRequete=requete;
    bool Requete=laRequete.exec();
    qDebug()<<Requete;
    if(Requete==true) {
        ui->pushButtonAddToHistory->setEnabled(true);
        int nbLigne=0;
        ui->colorButton->setStyleSheet("QPushButton { background-color: green; border: none; }");
        // compte les colonnes de requête
        QSqlRecord enregistrement =laRequete.record();
        // ui->textEdit->setStyleSheet("QWidget { background-color: green; }");
        // tant que la requete n'est pas fini on boucle ligne par ligne
        while(laRequete.next()) {
            //for(int noLigne=0;noLigne<count)
            // pour chaque colonne de ligne on boucle
            for(int noChamp=0;noChamp < enregistrement.count();noChamp++)
            {
                // notre table recois le nombre de colonnes et les affiche
                ui->tableWidgetResultat->setColumnCount(enregistrement.count());
                // on donne le nom de colonne
                ui->tableWidgetResultat->setHorizontalHeaderItem(noChamp,new QTableWidgetItem(enregistrement.fieldName(noChamp)));
                // recuperation de resultat
                QString resultat=laRequete.value(noChamp).toString();
            qDebug()<<resultat;
            QTableWidgetItem *Resultat = new QTableWidgetItem(resultat);
            ui->tableWidgetResultat->setRowCount(nbLigne+1);
            ui->tableWidgetResultat->setItem(nbLigne,noChamp,Resultat);
            qDebug()<<Resultat;
            }
            nbLigne++;
        }
    } else
    {
     ui->pushButtonAddToHistory->setEnabled(false);
     ui->colorButton->setStyleSheet("QPushButton { background-color: red; border: none; }");
    }
}



void MainWindow::on_pushButtonAddToHistory_clicked()
{
    qDebug()<<"MainWindow::on_pushButtonAjouterRequete_clicked()";
    QString requete = ui->textEdit->toPlainText();
    QSqlQuery laRequete=requete;
    bool Requete=laRequete.exec();
    qDebug()<<Requete;
    if(Requete==true) {
        // on enregistre la requete dans la liste
        QListWidgetItem *LaRequete = new QListWidgetItem(requete);
        // on verifie est-ce qu'il déja existe dans notre list
        //if(requeteListe != LaRequete) {
            // s'il n'existe pas on l'ajoute dans la liste
        ui->listWidgetHistory->addItem(LaRequete);
        //}
    }else {

    }
}

void MainWindow::on_pushButtonSave_clicked()
{
    qDebug()<<"MainWindow::on_pushButtonEnregistrer_clicked()";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",tr("All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
        QTextStream out(&file);
        for(int row=1; row<ui->listWidgetHistory->count();row++)
        {
            QString requete= ui->listWidgetHistory->item(row)->text();
            out<<requete<<"\n";
        }
    //QMessageBox::information(this,tr("Your file has been saved"));
   }
}


void MainWindow::on_pushButtonLoad_clicked()
{
    qDebug()<<"MainWindow::on_pushButtonLoad_clicked()";
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("All Files (*.*)"));
    if (fileName.isEmpty())
         return;
    else {QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;}
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        qDebug() << "read output - " << line;
        QListWidgetItem *Str = new QListWidgetItem(line);
        ui->listWidgetHistory->addItem(Str);
        }
}
}

void MainWindow::on_pushButtonExport_clicked()
{
    qDebug()<<"MainWindow::on_pushButtonExport_clicked()";
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",tr("CSV Files(*.csv)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
        QTextStream out(&file);
        int noLigne=0;
        int nbLigne=ui->tableWidgetResultat->rowCount();
        while(noLigne<nbLigne) {
        for(int colonne=0; colonne<ui->tableWidgetResultat->columnCount();colonne++)
        {
            QString requete= ui->tableWidgetResultat->item(noLigne,colonne)->text();
            out<<requete<<";";
        }
        out<<"\n";
        noLigne++;
    }
}
}

void MainWindow::on_listWidgetHistory_doubleClicked(const QModelIndex &index)
{
   qDebug()<<"MainWindow::on_listWidgetHistory_doubleClicked(const QModelIndex &index)";
   ui->textEdit->clear();
   QListWidgetItem *Requete=ui->listWidgetHistory->currentItem();
   QString requete = Requete->data(Qt::DisplayRole).toString();
   ui->textEdit->setText(requete);
}

void MainWindow::on_colorButton_clicked()
{
    qDebug()<<"MainWindow::on_colorButton_clicked()";
    QString texte=ui->textEdit->toPlainText();
    QSqlQuery requete;
    bool laRequete=requete.exec(texte);
    if(laRequete==false) {
    QString error= requete.lastError().text();
    qDebug()<<error;
    QTableWidgetItem *Error= new QTableWidgetItem(error);
    ui->tableWidgetResultat->setColumnCount(1);
    ui->tableWidgetResultat->setRowCount(1);
    ui->tableWidgetResultat->setHorizontalHeaderItem(0,new QTableWidgetItem("Error"));
    qDebug()<<Error;
    ui->tableWidgetResultat->setColumnWidth(0,500);
    ui->tableWidgetResultat->setItem(0,0,Error);
    }
}
