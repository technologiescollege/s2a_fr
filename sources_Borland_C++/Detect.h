//---------------------------------------------------------------------------

#ifndef DetectH
#define DetectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TestCarte : public TThread
{
  typedef struct tagTHREADNAME_INFO
  {
    DWORD dwType;     // doit être 0x1000
    LPCSTR szName;    // pointeur sur le nom (dans l'espace d'adresse de l'utilisateur)
    DWORD dwThreadID; // ID de thread (-1=thread de l'appelant)
    DWORD dwFlags;    // réservé pour une future utilisation, doit être zéro
  } THREADNAME_INFO;
private:
  void SetName();
protected:
	void __fastcall Execute();
public:
	__fastcall TestCarte(bool CreateSuspended);
	void __fastcall Scan_Arduino();
};
//---------------------------------------------------------------------------
#endif
