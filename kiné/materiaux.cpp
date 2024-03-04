#include "materiaux.h"
#include<QString>
#include<QSqlQuery>
#include<qDebug>
Materiaux::Materiaux()
{
    //constructeurs par défaut pour initialiser les attributs de la classe
 id=0;
 libelle="";
 localisation ="";
 categorie="";
 quantite=0;


}

//constructeurs paramétrés
Materiaux::Materiaux(int id,QString libelle,QString localisation,QString categorie,int quantite,QDate dateAjouter)
{
    this->id=id;
    this->libelle=libelle;
    this->localisation=localisation;
    this->categorie=categorie;
    this->quantite=quantite;
    this->dateAjouter=dateAjouter;


}
//get
 int Materiaux::get_id()
 {
     return id;
 }
 QString Materiaux::get_libelle()
 {
     return libelle;
 }
 QString Materiaux::get_localisation()
 {
     return localisation;
 }
 QString Materiaux::get_categorie()
 {
     return categorie;
 }
 int Materiaux::get_quantite()
 {
     return quantite;
 }
 QDate Materiaux::get_dateAjout()
 {
     return dateAjouter;
 }

 //set

 void Materiaux::set_id(int id)
 {
     this->id=id;

 }

 void Materiaux::set_libelle(QString libelle)
 {
     this->libelle=libelle;

 }

 void Materiaux::set_localisation(QString localisation)
 {
     this->localisation=localisation;

 }

 void Materiaux::set_categorie(QString categorie)
 {
     this->categorie=categorie;

 }

 void Materiaux::set_quantite(int quantite)
 {
     this->quantite=quantite;

 }
 void Materiaux::set_dateAjout(QDate dateAjouter)
 {
     this->dateAjouter=dateAjouter;

 }

 bool Materiaux::ajouterMateriaux()
 {
     QSqlQuery query;
     //convertir id to string
     QString idString=QString::number(id);
      //convertir quantite to string
     QString quantiteString=QString::number(quantite);
     //REQUETE
     query.prepare("insert into materiaux(id,libelle,localisation,categorie,quantite,dateAjout)" "values(:id,:libelle,:localisation,:categorie,:quantite,:dateAjout)");

             query.bindValue(":id", idString);
             query.bindValue(":libelle", libelle);
             query.bindValue(":localisation", localisation);
             query.bindValue(":categorie", categorie);
             query.bindValue(":quantite", quantiteString);
             query.bindValue(":dateAjout", dateAjouter);
                 return query.exec();

 }

 bool Materiaux::supprimerMateriaux(int id)
 {
      QSqlQuery query;
       QString idString=QString::number(id);
       query.prepare("delete from materiaux where id=:id");
                     //bindValue id =>idstring
       query.bindValue(":id",idString);
                return query.exec();
 }

 bool Materiaux::modifierMateriaux(int id)
 {
     QSqlQuery query;
     //convertir id to string
     QString idString=QString::number(id);
      //convertir quantite to string
     QString quantiteString=QString::number(quantite);
     //REQUETE
     query.prepare("update materiaux set  libelle=:libelle , localisation=:localisation , categorie=:categorie , quantite=:quantite , dateAjout=:dateAjout where id=:id");

         query.bindValue(":id", idString);
         query.bindValue(":libelle", libelle);
         query.bindValue(":localisation", localisation);
         query.bindValue(":categorie", categorie);
         query.bindValue(":quantite", quantiteString);
         query.bindValue(":dateAjout", dateAjouter);
            return query.exec();
 }

 QSqlQueryModel* Materiaux::selectMateriauxById(int id)
 {
     QSqlQueryModel* model = new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT * FROM materiaux WHERE id = :id");
     query.bindValue(":id", id);
     if(query.exec())
     {
         model->setQuery(query);
         if(model->rowCount() == 1) // Check if exactly one row is returned
         {
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("libelle"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("localisation"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantite"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("dateAjout"));
             return model;
         }
         else
         {
             qDebug() << "Error: No row or more than one row returned for id:" << id;
             delete model;
             return nullptr;
         }
     }
     else
     {
         qDebug() << "Query execution failed.";
         delete model;
         return nullptr;
     }
 }

 QSqlQueryModel* Materiaux::afficherMateriaux()
  {
      //affichage dans un tableau QSqlQueryModel
      QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("select * from materiaux");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("libelle"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("localisation"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantite"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("dateAjout"));
      return model;

  }














