//---------------------------------------------------------------------------


#pragma hdrstop

#include "GestionLangue.h"
#include <tinyxml.h>
#include <Classes.hpp>
#include <TypInfo.hpp>
#include <vector>
#include <sstream>
//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace std;

void GestionLangue::ChangeComponent(TComponent* prmComposant, int prmLangue)
{
  TiXmlElement *elem;
  TiXmlElement *caption;
  TiXmlDocument doc(fichier.c_str());
  TiXmlHandle hdl(&doc);
  string type;
  unsigned int i;
  int j;
  if((doc.LoadFile()) && (prmComposant->Name != ""))
  {
    for(i=0;i<vectProp.size();i++)
    {
      elem = hdl.FirstChildElement().FirstChildElement("Labels").FirstChildElement(prmComposant->Name.c_str()).FirstChildElement(vectProp[i].c_str()).FirstChildElement(listLangues[prmLangue].c_str()).ToElement();
      if(elem != NULL)
        if(elem->GetText())
        {
          if(vectProp[i] == "Items")
          {
            if((caption = hdl.FirstChildElement().FirstChildElement("Labels").FirstChildElement(prmComposant->Name.c_str()).ToElement()) != NULL)
              ChangePropStringList(prmComposant,elem->GetText(),caption->Attribute("type"));
          }else
            ChangeProp(prmComposant,vectProp[i].c_str(),elem->GetText());
        }
    }
    for(j=0;j<prmComposant->ComponentCount;j++)
    {
      ChangeComponent(prmComposant->Components[j],prmLangue);
    }
    if((elem = hdl.FirstChildElement().FirstChildElement("Labels").FirstChildElement(prmComposant->Name.c_str()).ToElement()) != NULL)
    {
      type = elem->Attribute("type");
      if(type == "TMenuItem")
      {
        TMenuItem *pMenuItem = dynamic_cast< TMenuItem* > (prmComposant);
        for(j=0;j<pMenuItem->Count;j++)
        {
          ChangeComponent(pMenuItem->Items[j],prmLangue);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall GestionLangue::ChangeProp(TComponent* pControl, String Property_Name, String AValue)
{
	try
	{
		if (pControl != NULL)  //On test si le pointeur sur le composant n'est pas NULL
		{
			//On test si la propriété est accessible
			if (IsPublishedProp(pControl, Property_Name))
      {
        try
        {
          SetPropValue(pControl, Property_Name, AValue);  //Modification de la propriété
        }
        catch(EPropertyError &propError){}
      }
    }
  }
  catch(...){}
}

void GestionLangue::ChangePropStringList(TComponent* pControl, string AValue, string typeComponant)
{
  TStrings * contenu;
  istringstream iss(AValue);
  string ligne;
  if(typeComponant == "TComboBox")
    contenu = (dynamic_cast <TComboBox*> (pControl))->Items;
  else if(typeComponant == "TRadioGroup")
    contenu = (dynamic_cast <TRadioGroup*> (pControl))->Items;
  else
    return;
  contenu->Clear();
  while ( std::getline( iss, ligne, separateur ) )
  {
    contenu->Add(ligne.c_str());
  }
}
//---------------------------------------------------------------------------

void GestionLangue::Init(TMenuItem* prmMenu, string prmFichier, ptrOnClick prmFonctionClick)
{
  TiXmlElement *elem;
  TiXmlElement *caption;
  TiXmlDocument doc(prmFichier.c_str());
  TiXmlHandle hdl(&doc);
  string langueXml;
  string nameXml;
  string propriete;
  TMenuItem * menuLangue;
  bool defautXml;
  int i = 0;
  fichier = prmFichier;
  if(doc.LoadFile())
  {
    elem = hdl.FirstChildElement().FirstChildElement("Parametre").ToElement();
    if(elem != NULL)
      separateur = elem->Attribute("Separateur")[0];
    elem = hdl.FirstChildElement().FirstChildElement("Parametre").FirstChildElement("Proprietes").FirstChildElement("Propriete").ToElement();
    while(elem != NULL)
    {
      propriete = elem->GetText() ;
      vectProp.push_back(propriete);
      elem = elem->NextSiblingElement("Propriete");
    }
    elem = hdl.FirstChildElement().FirstChildElement("Langues").FirstChildElement("Langue").ToElement();
    listLangues.clear();
    while(elem != NULL)
    {
      langueXml = elem->Attribute("index");
      defautXml = (string(elem->Attribute("default")) == string("1"));
      nameXml   = elem->Attribute("name");
      listLangues[i] = langueXml;
      if(defautXml == true)
        defaut = i;
      menuLangue = new TMenuItem(prmMenu);
      menuLangue->Name = nameXml.c_str();
      menuLangue->Tag = i;
      menuLangue->OnClick = (TNotifyEvent)prmFonctionClick;
      prmMenu->Add(menuLangue);
      elem = elem->NextSiblingElement("Langue");
      i++;
    }
  }
  Change(defaut);
}
//---------------------------------------------------------------------------

void GestionLangue::Change(int prmLangue)
{
  int i;
  for(i=0;i<Application->ComponentCount;i++)
  {
    ChangeComponent(Application->Components[i],prmLangue);
  }
}
//---------------------------------------------------------------------------
