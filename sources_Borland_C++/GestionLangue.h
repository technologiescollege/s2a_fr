//---------------------------------------------------------------------------

#ifndef GestionLangueH
#define GestionLangueH

#include <string>
#include <hash_map>
#include <Menus.hpp>
#include <vcl.h>
#include <ToolsAPI.hpp>
//---------------------------------------------------------------------------

typedef void (__fastcall(__closure*ptrOnClick))(TObject *);

class GestionLangue
{
private:
  std::hash_map<int,std::string> listLangues;
  std::string  fichier;
  int defaut;
  char separateur;
  std::vector<std::string> vectProp;
  void ChangeComponent(TComponent*, int);
  void __fastcall ChangeProp(TComponent*, String, String);
  void ChangePropStringList(TComponent*, std::string, std::string);
public :
  GestionLangue(){defaut = 0;};
  ~GestionLangue(){;};
  void Init(TMenuItem*, std::string, ptrOnClick);
  void Change(int);
};
#endif
