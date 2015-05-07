//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#pragma hdrstop

#include <windows.h>

using namespace std;  //pour les traductions
#include <tinyxml.h>

#include <IniFiles.hpp> //pour le fichier INI

#include "s2a_scratch2_arduino.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfaceS2A *InterfaceS2A;
TIniFile *INI = new TIniFile(ExtractFilePath(Application->ExeName)+ "s2a.ini");
//listes pour récupérer le contenu du fichier INI
int port=2;
int choix_langue;
AnsiString locate_scratch2="Scratch 2.exe";
AnsiString locate_librairie;
AnsiString locate_project;
AnsiString locate_doc;
//listes pour les menus dynamiques
TStringList *Examples = new TStringList;
TStringList *Biblio = new TStringList;
TStringList *Aides = new TStringList;
TStringList *Docs = new TStringList;
TStringList *Extensions1 = new TStringList;
TStringList *Extensions2 = new TStringList;

//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::InitINI()
{
  //écriture dans le fichier INI des variables utiles
  INI->WriteInteger("port COM", "port", 3);      //port par défaut pour initialiser
  INI->WriteString("locate Scratch2", "locate_scratch2", "Scratch 2.exe"); //chemin par défaut pour initialiser
  INI->WriteInteger("langue", "langue", 0); //dans le fichier label.xml, à la balise <Langues>, cela correspond au n° du rang de la langue
  //dossiers à utiliser pour les documents
  INI->WriteString("locate Librairie", "locate_librairie", ExtractFilePath(Application->ExeName) + "bibliotheque\\"); //chemin par défaut pour initialiser
  INI->WriteString("locate Project", "locate_project", ExtractFilePath(Application->ExeName) + "projets\\"); //chemin par défaut pour initialiser
  INI->WriteString("locate Documentation", "locate_doc", ExtractFilePath(Application->ExeName) + "documentation\\"); //chemin par défaut pour initialiser
}
//---------------------------------------------------------------------------
__fastcall TInterfaceS2A::TInterfaceS2A(TComponent* Owner)
	: TForm(Owner)
{
  //vérification de l'existence du fichier INI, sinon le recréé
  if (!FileExists(ExtractFilePath(Application->ExeName)+ "s2a.ini"))
	 InitINI();
  //lecture du fichier INI
  port=INI->ReadInteger("port COM", "port", 4);
  choix_langue=INI->ReadInteger("langue", "langue", 0);
  locate_scratch2=INI->ReadString("locate Scratch2", "locate_scratch2", "Scratch 2.exe");
  locate_librairie=INI->ReadString("locate Librairie", "locate_librairie", ExtractFilePath(Application->ExeName) + "bibliotheque\\");
  locate_project=INI->ReadString("locate Project", "locate_project", ExtractFilePath(Application->ExeName) + "projets\\");
  locate_doc=INI->ReadString("locate Documentation", "locate_doc", ExtractFilePath(Application->ExeName) + "documentation\\");

  //nettoie le champ du TEdit et y place la valeur lue dans le INI
  Edit1->Clear();
  //procédure de contrôle si le fichier INI est mal rempli
  port=INI->ReadInteger("port COM", "port", 3);
  Edit1->Text=IntToStr(port);

  Extensions1->Add(".sb2");
  // Appel à Search, avec pour liste des fichiers, les items des listes Bibilo & Examples.
  SearchEx(locate_librairie, Extensions1, Biblio,0);
  SearchEx(locate_project, Extensions1, Examples,1);
  delete Extensions1;
  Extensions2->Add(".pdf");
  Extensions2->Add(".odt");
  Extensions2->Add(".lnk");
  Extensions2->Add(".url");
  Extensions2->Add(".html");
  Extensions2->Add(".htm");  
  // Appel à SearchDocs, avec pour liste des fichiers les items de Documentation.
  SearchDocs(locate_doc, Extensions2, Docs,2);
  delete Extensions2;

  //appel à la procédure pour gérer les langues
  AnsiString file = ExtractFilePath(Application->ExeName) + "label.xml";
  langue = new GestionLangue;
  langue->Init(InterfaceS2A->Langue1,file.c_str(),(ptrOnClick)&Langue1Click);
  //après l'initialisation des langues, le système pioche la langue précédemment sélectionnée
  langue->Change(choix_langue);
}
//-------------------------recherche des fichiers sb2 pour les lister dans le menu Fichier--------------------------------------------------
void __fastcall TInterfaceS2A::SearchEx(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu)
{
  TSearchRec Infos_fichier;
  TMenuItem *NewItem = new TMenuItem(this);
  if (!FindFirst(FilePath+"*.*", faAnyFile, Infos_fichier))
  do
  {
	for (int i = 0 ; i < Extensions->Count ; i++)
	{
	  if (ExtractFileExt(Infos_fichier.Name).LowerCase() == Extensions->Strings[i].LowerCase())
	  {
		//ajout dans la liste d'une ligne avec le chemin+nom du fichier trouvé
		ListeFichiers->Add(ExpandFileName(Infos_fichier.Name));
		//nettoie le nom de fichier de son extension sb2 pour le nom seul du fichier, sans le chemin
		AnsiString CleanName = StringReplace(Infos_fichier.Name, ".sb2", "",TReplaceFlags() << rfReplaceAll);
		//rajout d'entrées dans le menu
		NewItem = new TMenuItem(this);
		NewItem->Caption = CleanName;
		NewItem->Name = CleanName;
		//stockage du chemin complet + nom de fichier pour la fonction ExempleClick
		NewItem->Hint = FilePath + Infos_fichier.Name.c_str();
		NewItem->OnClick=ExempleClick;
		//rajout au bon endroit de l'entrée dans le menu
		MainMenu1->Items->Items[0]->Items[RangMenu]->Add(NewItem);
	  }
	}
  }
  while(!FindNext(Infos_fichier));
  FindClose(Infos_fichier);
}
//---------------------associer chaque entrée dynamique dans Biblio & Exemples à leur lancement-------------------
void __fastcall TInterfaceS2A::ExempleClick(TObject *Sender)
{
AnsiString CheminNomFichier;
ofstream fichier_s2("scratch2.bat", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		if(fichier_s2)
		{
			   //récupération des infos de l'entrée TMenu qui a déclenché cette fonction
			   CheminNomFichier=static_cast<TMenuItem*>(Sender)->Hint;
			   fichier_s2 << "@echo off\nbreak ON\nrem fichiers BAT et fork créés par Sébastien CANET\ncls\nSET currentpath=%~dp1\nSET dossier_scratch="<< '"' << locate_scratch2.c_str() << '"'<< "\nstart %dossier_scratch% " << '"' << CheminNomFichier.c_str() << '"';
			   fichier_s2.close();
		}
		else ShowMessage(Popup->Items->Strings[0]);
ShellExecute(0, 0, "scratch2.bat", 0, 0 , SW_HIDE );
}
//-------------------------recherche des fichiers de docs pour les lister dans les menus Aide & Documentation---------------
void __fastcall TInterfaceS2A::SearchDocs(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu)
{
  TSearchRec Infos_fichier;
  TMenuItem *NewItem = new TMenuItem(this);
  if (!FindFirst(FilePath+"*.*", faAnyFile, Infos_fichier))
  do
  {
	for (int i = 0 ; i < Extensions->Count ; i++)
	{
	  if (ExtractFileExt(Infos_fichier.Name).LowerCase() == Extensions->Strings[i].LowerCase())
	  {
		//ajout dans la liste d'une ligne avec le chemin+nom du fichier trouvé
		ListeFichiers->Add(ExpandFileName(Infos_fichier.Name));
		//nettoie le nom de fichier de son extension pour le nom seul du fichier, sans le chemin
		AnsiString CleanName = StringReplace(Infos_fichier.Name, Extensions->Strings[i].LowerCase(), "",TReplaceFlags() << rfReplaceAll);
		//rajout d'entrées dans le menu
		NewItem = new TMenuItem(this);
		NewItem->Caption = Infos_fichier.Name;
		NewItem->Name = CleanName;
		//stockage du chemin complet + nom de fichier pour la fonction ExempleClick
		NewItem->Hint = FilePath + Infos_fichier.Name.c_str();
		NewItem->OnClick=DocsClick;
		//rajout au bon endroit de l'entrée dans le menu
		MainMenu1->Items->Items[RangMenu]->Add(NewItem);
	  }
	}
  }
  while(!FindNext(Infos_fichier));
  FindClose(Infos_fichier);
}
//---------------------associer chaque entrée dynamique dans Biblio & Exemples à leur lancement-------------------
void __fastcall TInterfaceS2A::DocsClick(TObject *Sender)
{
//récupération des infos de l'entrée TMenu qui a déclenché cette fonction
AnsiString CheminNomFichier=static_cast<TMenuItem*>(Sender)->Hint;

ShellExecute(0, 0, CheminNomFichier.c_str(), 0, 0 , SW_HIDE );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::A_proposClick(TObject *Sender)
{
ShellExecute(0, 0, "https://github.com/technologiescollege/s2a_fr", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Siteofficieldes2a1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://mryslab.blogspot.fr/", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::AllerplusloinBlocklyDuino1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://www.technologiescollege.fr/blockly@rduino", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::PrparerArduino1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\1.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Utilisation1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\2.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::N4Principesdeprogrammation1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\3.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::N3Mmentodescommandes1Click(TObject *Sender)
{
ShellExecute(0, 0, ".\\aide\\4.pdf", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Wiki1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://tic.technologiescollege.fr/wiki", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::ScratchEnLigneClick(TObject *Sender)
{
ShellExecute(0, 0, "http://scratch.mit.edu/projects/editor/", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Button2Click(TObject *Sender)
{
ofstream fichier_s2("scratch2.bat", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		if(fichier_s2)
		{
				fichier_s2 << "@echo off\nbreak ON\nrem fichiers BAT et fork créés par Sébastien CANET\ncls\nSET currentpath=%~dp1\nSET dossier_scratch="<< '"' << locate_scratch2.c_str() << '"'<< "\nstart %dossier_scratch% " << '"' << locate_librairie.c_str() << "fichier_depart_s2a.sb2" << '"' ;
				fichier_s2.close();
		}
		else ShowMessage(Popup->Items->Strings[1]);
ShellExecute(0, 0, "scratch2.bat", 0, 0 , SW_HIDE );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Button1Click(TObject *Sender)
{
port=this->Edit1->Text.ToInt();
INI->WriteInteger("port COM", "port", port);
ofstream fichier_s2a("s2a_cmd.bat", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		if(fichier_s2a)
		{
				fichier_s2a << "@echo off\nbreak ON\nrem fichiers BAT et fork créés par Sébastien CANET\nSET currentpath=%~dp1\ncd %currentpath%s2a\ncls\n.\\Python\\python.exe s2a.py COM" << port;
				fichier_s2a.close();
		}
		else ShowMessage(Popup->Items->Strings[2]);
ShellExecute(0, 0, "s2a_cmd.bat", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Quitter1Click(TObject *Sender)
{
InterfaceS2A->Close();
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::OuvrirClick(TObject *Sender)
{
if (Open_s2->Execute()==true) locate_scratch2=Open_s2->FileName.c_str();
//écriture dans le fichier INI
//DeleteKey("locate Scratch2", "locate_scratch2");
INI->WriteString("locate Scratch2", "locate_scratch2", locate_scratch2);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::Edit1KeyPress(TObject *Sender, char &Key)
{
  if (Key < '0' || Key >'9')
	{
	ShowMessage(Popup->Items->Strings[3]);
	Key=NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::Apropos1Click(TObject *Sender)
{
ShowMessage(Popup->Items->Strings[4]);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::Gestionnairedepriphriques1Click(TObject *Sender)
{
ShellExecute(0, 0, "devmgmt.msc", 0, 0 , SW_HIDE );
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::Langue1Click(TObject *Sender)
{
INI->WriteInteger("langue", "langue", ((TMenuItem*)Sender)->Tag);
langue->Change(((TMenuItem*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::InitClick(TObject *Sender)
{
DeleteFile("s2a.ini");
InitINI();
//nettoie le champ du TEdit et y place la valeur lue dans le INI
Edit1->Clear();
//procédure de contrôle si le fichier INI est mal rempli
port=INI->ReadInteger("port COM", "port", 3);
Edit1->Text=IntToStr(port);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::SiteofficielArduino1Click(TObject *Sender)
{
ShellExecute(0, 0, "http://arduino.cc/en/Main/Software", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::lchargerlesdrivers1Click(TObject *Sender)
{
ShellExecute(0, 0, "https://github.com/technologiescollege/drivers", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TInterfaceS2A::Localiserledossierexemples1Click(TObject *Sender)
{
if (OpenDialog->Execute()==true) locate_librairie=ExtractFilePath(OpenDialog->FileName);
//écriture dans le fichier INI
INI->WriteString("locate Librairie", "locate_librairie", locate_librairie);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::Localiserledossierprojets1Click(TObject *Sender)
{
if (OpenDialog->Execute()==true) locate_project=ExtractFilePath(OpenDialog->FileName);
//écriture dans le fichier INI
INI->WriteString("locate Project", "locate_project", locate_project);
}
//---------------------------------------------------------------------------

void __fastcall TInterfaceS2A::Localiserledossierdocumentation1Click(
      TObject *Sender)
{
if (OpenDialog->Execute()==true) locate_doc=ExtractFilePath(OpenDialog->FileName);
//écriture dans le fichier INI
INI->WriteString("locate Documentation", "locate_doc", locate_doc);
}
//---------------------------------------------------------------------------
