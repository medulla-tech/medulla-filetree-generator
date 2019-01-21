Programme  create json tree Filesystem Hierarchy windows 
install in C:\\\\"Program Files"\\Pulse\\bin\\pulse-filetree-generator.exe

genere file in 'C:\\\\Program Files\\Pulse\\tmp\\treejson.json'


example section  [browserfile]  dans fichier agentconf.ini


[browserfile]
defaultdir = C:\\ProgramData\AVAST Software/Avast/log
rootfilesystem = C:\\ProgramData
listexclude = C:\\ProgramData\AVAST Software\Avast\log\, C:\\ProgramData\Google, c:\\Users,c:\\Windows,c:\\Program Files (x86),c:\\Python27,c:\\ProgramData,c:\\Documents and Settings,c:\\System Volume Information


exemple 
C:\\\\"Program Files"\\Pulse\\bin\\pulse-filetree-generator.exe c:\

genere dans C:\Users\jfk\AppData\Local\Temp\file.txt le json



Convention de nomage fichier windows.

CaractÃ¨res interdits et autres conventions de nommage des fichiers dans Windows : Les noms de fichiers ne peuvent pas utiliser n'importe quels caractÃ¨res ni avoir n'importe quelle longueur...
Assiste.com - CaractÃ¨res interdits dans les noms de fichiers Windows
CaractÃ¨res interdits dans les noms de fichiers WindowsCaractÃ¨res interdits dans les noms de fichiers WindowsCaractÃ¨res interdits dans les noms de fichiers Windows

Conventions et limitations dans le systÃ¨me de fichiers NTFS (" NT File System " - " New Technologie File System "), Ã  partir de Windows NT en 1993 :

    Nom suivi d'une extension Ã©ventuelle, sÃ©parÃ©e par un "." (un point)
    Longueur maximale du nom d'un fichier : 255 caractÃ¨res, extension incluse (mais, en ligne de commande, comme par exemple dans la boÃ®te d'invite de commande, vous ne pouvez crÃ©er que des noms de fichiers comportant au maximum 253 caractÃ¨res).

    Nombre de sous-niveaux maximum : 15

    Longueur maximale du chemin d'accÃ¨s complet Ã  un fichier : 260 caractÃ¨res (limite imposÃ©e par le shell de Windows - en thÃ©orie, la longueur maximale " approximative " (1) d'un chemin d'accÃ¨s complet est de 32.767 caractÃ¨res).


    Le caractÃ¨re antislash ( backslash - ) est le sÃ©parateur de chemins

    Les caractÃ¨res suivants sont rÃ©servÃ©s pour des usages spÃ©ciaux et ne doivent pas Ãªtre utilisÃ©s dans le nom lui-mÃªme :

        < (plus petit que; less than)
        > (plus grand que; greater than)
        : (deux points; colon)
        " (double appostrophe; double quote)
        / (slash; barre de fraction; forward slash)
        (antislash; backslash)
        | (barre verticale; vertical bar; pipe)
        ? (point d'interrogation; question mark)
        * (astÃ©risque; asterisk)

    Les caractÃ¨res non imprimables (les valeurs binaires dans l'intervalle 00 Ã  31) sont interdits. Toutefois, les caractÃ¨res de l'intervalle binaire 01 Ã  31 peuvent Ãªtre utilisÃ©s dans le nommage des chaÃ®nes ADS (Alternate Data Stream) (Fichiers totalement cachÃ©s attachÃ© Ã  un fichier visible).

    . reprÃ©sente le rÃ©pertoire courant
    .. reprÃ©sente le rÃ©pertoire parent

    RessourcesRessourcesRessources
    Cette section est vide ou insuffisante. Si vous avez des liens vers des ressources significatives, votre aide est la bienvenue, y compris s'il s'agit de votre propre site. AprÃ¨s approbation, ils seront ajouÃ©s ici. Assiste n'utilise pas le honteux attribut rel=â€nofollowâ€.
    (1) Naming Files, Paths, and Namespaces
    Informations gÃ©nÃ©rales sur les systÃ¨mes de fichiers FAT, HPFS et NTFS
    RequÃªtesRequÃªtesRequÃªtes
    Conventions de nommage des fichiers NTFS
    CaractÃ¨res rÃ©servÃ©s dans les noms de fichiers Windows
    Quels sont les caractÃ¨res autorisÃ©s dans les noms de fichiers Windows ?
    Quels sont les caractÃ¨res interdits dans les noms de fichiers Windows ?
    Les mots suivants ne doivent pas Ãªtre utilisÃ©s en tant que nom de fichier, avec ou sans extension :
    CON, PRN, AUX, NUL, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8, COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, et LPT9
