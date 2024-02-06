Orignal Package by Jocelyn.
Archived to GitHub by OzzyOuzo.

Compilation is OK using win10 u can test your generated smc images (smcMaker) through Geepee32 (0.44) or Mame (recent, see Mame subfolder)

Below orginal post from the author:



voilà, le strict minimum pour compiler avec GCC.



  visual-mingw32 [http://visual-mingw.sourceforge.net], gcc [http://gcc.gnu.org], Scite [http://www.scintilla.org]  et cygwin [http://www.cygwin.com] sont sous licence GNU.


 Le package est à installer sous c:\minigp32
et mettre c:\minigp32\bin dans le path.



Test:


 * lancer apps/visual_mingw32
    
		>Ouvrir un projet (l'example3 apparait )
		>Build
		
	Une fois la compil ok, aller dans "here your projects/example3" et lancer:
		
		>b2gp32.bat

 * si vous ne souhaiter pas utiliser visual_mingw32,
un make.bat se trouve dans le répertoire de l'exemple3.
  L'exemple3 est un des exemple extrait de la SDK officiel de Gamepark.
  
    [Si vous ne vous etes pas encore procurer la SDK:
	
	http://www.gameparkdev.co.kr/ ,bouton PDS, SDK est en gras 
		dans le bas vous avez des pages de 1 à 3, choisissez la troisième.]



 Les librairies de compilation sont 
de Dark Fader et le GCC 3.04 aussi, donc tous mes remerciements
à Dark [http://darkfader.net/gp32.]

visual_mingw32 lors de la création du makefile, ajoute
des lignes de debug à la fin. Il faut aller dans le makefile
et retirer ces lignes, ou alors une erreur apparait.

 Si vous souhaitez une transformation de l'objet en fxe, sous
 le makefile :
 
<< 
 all:	$(TARGET)
<<
   
    DEVIENT
	
>>	
 all:	$(TARGET)
		objcopy -O binary example3.exe clown.gxb
		b2fxe clown.gxb "C:\Program Files\gp32\clown.fxe"
>>

  Sincèrement, Jocelyn.

 toute question: unplugandplay@free.Fr