//---------------------------------------------------------------------------

#ifndef s2aH
#define s2aH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include <IniFiles.hpp>
#include <string>
#include "GestionLangue.h"
//---------------------------------------------------------------------------

class TInterfaceS2A : public TForm
{
__published:	// Composants gérés par l'EDI
	TMainMenu *MainMenu1;
	TMenuItem *Quitter1;
	TMenuItem *A_propos;
	TImage *Image1;
	TImage *Image2;
	TButton *Button1;
	TButton *Button2;
	TButton *ScratchEnLigne;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	TMenuItem *AllerplusloinBlocklyDuino1;
	TMenuItem *Wiki1;
	TMenuItem *Documentation1;
	TMenuItem *PrparerArduino1;
	TMenuItem *Utilisation1;
	TMenuItem *N3Mmentodescommandes1;
	TLabel *Label4;
	TLabel *Label5;
	TOpenDialog *Open_s2;
	TMenuItem *Ouvrir;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Aide1;
	TMenuItem *Apropos1;
	TMenuItem *Fichier;
	TMenuItem *N3;
	TMenuItem *ExemplesScratch2;
	TMenuItem *Siteofficieldes2a1;
	TMenuItem *N4Principesdeprogrammation1;
	TMenuItem *Gestionnairedepriphriques1;
	TMenuItem *Outils1;
	TMenuItem *Bibliothque;
	TMenuItem *Langue1;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *Init;
	TTimer *HintTimer;
	void __fastcall InitINI();
	void __fastcall A_proposClick(TObject *Sender);
	void __fastcall AllerplusloinBlocklyDuino1Click(TObject *Sender);
	void __fastcall PrparerArduino1Click(TObject *Sender);
	void __fastcall Utilisation1Click(TObject *Sender);
	void __fastcall N3Mmentodescommandes1Click(TObject *Sender);
	void __fastcall Wiki1Click(TObject *Sender);
	void __fastcall ScratchEnLigneClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Quitter1Click(TObject *Sender);
	void __fastcall OuvrirClick(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall Apropos1Click(TObject *Sender);
	void __fastcall Siteofficieldes2a1Click(TObject *Sender);
	void __fastcall N4Principesdeprogrammation1Click(TObject *Sender);
	void __fastcall Gestionnairedepriphriques1Click(TObject *Sender);
	void __fastcall SearchEx(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu);
	void __fastcall SearchDocs(AnsiString FilePath, TStringList * Extensions, TStrings * ListeFichiers, int RangMenu);
	void __fastcall ExempleClick(TObject *Sender);
	void __fastcall DocsClick(TObject *Sender);
	void __fastcall InitClick(TObject *Sender);
private:	// Déclarations de l'utilisateur
	TLabel * interLabel ;
	TButton * interButton ;
	TInterfaceS2A * interInterfaceS2A ;
	TGroupBox * interGroupeBox ;
	TComboBox * interComboBox ;
	TCheckBox * interCheckBox ;
	TRadioGroup * interRadioGroupe ;
	TMenuItem * interMenuItem ;
	GestionLangue * langue;
public:		// Déclarations de l'utilisateur
	void __fastcall Langue1Click(TObject *Sender);
	__fastcall TInterfaceS2A(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterfaceS2A *InterfaceS2A;
//---------------------------------------------------------------------------
#endif
