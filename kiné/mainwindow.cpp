#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiaux.h"
#include<QMessageBox>
#include <QMessageBox>
#include <QIntValidator>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QTableView>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   Materiaux M;

    ui->setupUi(this);
    ui->tableView->setModel(M.afficherMateriaux());
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));

    ui->le_quantite->setValidator(new QIntValidator(0, 9999999, this));


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();
    QString nom=ui->le_libelle->text();
    QString localisation=ui->le_localisation->text();
    QString categorie = ui->le_categorie->currentText();
    int quantite=ui->le_quantite->text().toInt();
    QDate dateAjouter = ui->le_dateAjouter->date();
    Materiaux M(id,nom, localisation, categorie, quantite, dateAjouter);
    bool test=M.ajouterMateriaux();
    if(test)
   {
        ui->tableView->setModel(M.afficherMateriaux());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->le_id->clear();
     ui->le_libelle->clear();
     ui->le_localisation->clear();
     ui->le_categorie->setCurrentIndex(0);
     ui->le_quantite->clear();
     ui->le_dateAjouter->clear();


   }
    else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_modifier_clicked()
{


        int id = ui->le_id->text().toInt();
        QString libelle = ui->le_libelle->text();
        QString localisation = ui->le_localisation->text();
        QString categorie = ui->le_categorie->currentText();
        int quantite = ui->le_quantite->text().toInt();
        QDate dateAjouter = ui->le_dateAjouter->date();

        Materiaux M(id, libelle, localisation, categorie, quantite, dateAjouter);

        bool test = M.modifierMateriaux(id);
        if (test) {
            // Rafraîchir le modèle de TableView pour refléter les modifications
            ui->tableView->setModel(M.afficherMateriaux());
            QMessageBox::information(this, tr("Modification réussie"),
                                     tr("La ligne a été modifiée avec succès."),
                                     QMessageBox::Ok);
        } else {
            QMessageBox::critical(this, tr("Erreur de modification"),
                                  tr("La modification de la ligne a échoué."),
                                  QMessageBox::Ok);
        }

        // Effacer les champs après la modification
        ui->le_id->clear();
        ui->le_libelle->clear();
        ui->le_localisation->clear();
        ui->le_categorie->setCurrentIndex(0); // Réinitialiser la sélection de la catégorie
        ui->le_quantite->clear();
        ui->le_dateAjouter->setDate(QDate::currentDate()); // Réinitialiser la date
    }






void MainWindow::on_supprimer_clicked()
{


   QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                             tr("Veuillez sélectionner une ligne à supprimer."),
                             QMessageBox::Ok);
        return;
    }


    int id = selectedRows.at(0).data().toInt();
   Materiaux M;

   bool test=M.supprimerMateriaux(id);
   if(test)
  {
      ui->tableView->setModel(M.selectMateriauxById(id));//refresh
     QMessageBox::information(nullptr, QObject::tr("ok"),
     QObject::tr("suppression effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView->setModel(M.selectMateriauxById(id));//refresh
  }
   else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("suppression non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_4_clicked()
{
    Materiaux M;
    ui->tableView->setModel(M.afficherMateriaux());//refresh

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{


       // Get data from the selected index
        int id = index.sibling(index.row(), 0).data().toInt(); // Column 4 (quantite)
        QString libelle = index.sibling(index.row(), 1).data().toString(); // Column 1 (nom)
        QString localisation = index.sibling(index.row(), 2).data().toString(); // Column 2 (localisation)
        QString categorie = index.sibling(index.row(), 3).data().toString(); // Column 3 (categorie)
        int quantite = index.sibling(index.row(), 4).data().toInt(); // Column 4 (quantite)
        QDate dateAjouter = index.sibling(index.row(), 5).data().toDate(); // Column 5 (dateAjouter)

        // Populate line edit fields with the retrieved data
        ui->le_id->setText(QString::number(id));
        ui->le_libelle->setText(libelle);
        ui->le_localisation->setText(localisation);
        ui->le_categorie->setCurrentText(categorie);
        ui->le_quantite->setText(QString::number(quantite));
        ui->le_dateAjouter->setDate(dateAjouter);
}
