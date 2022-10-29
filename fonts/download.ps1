# On définie la police que l'on veut installer
$FONTS = 0x14
$Path=".\fonts\DejaVuSansMono.ttf"
$objShell = New-Object -ComObject Shell.Application
$objFolder = $objShell.Namespace($FONTS)
$Fontdir = dir $Path
# Installation de la police en verifiant qu'elle n'existe pas déjà
foreach($File in $Fontdir) {
    if(!($file.name -match "pfb$"))
    {
        $try = $true
        $installedFonts = @(Get-ChildItem c:\windows\fonts | Where-Object {$_.PSIsContainer -eq $false} | Select-Object basename)
        $name = $File.baseName

        foreach($font in $installedFonts)
        {
            $font = $font -replace "_", ""
            $name = $name -replace "_", ""
            if($font -match $name)
            {
                $try = $false
            }
        }
        if($try)
        {
            $objFolder.CopyHere($File.fullname)
        }
    }
}
# Emplacement de l'ensemble des polices instalées sur la machine :
$T1key = 'HKLM:\Software\Microsoft\Windows NT\CurrentVersion\Fonts'

# Emplacement de l'ensemble des polices instalées pour la console windows :
$T2key = 'HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Console\TrueTypeFont'

# Affichage de l'ensemble des polices déjà installées
Get-ItemProperty -Path $T2key

# Ajout de la nouvelle police pour la console dans un nouvelle valeur chaîne : 
Set-ItemProperty -Path $T2key -Name '00000' -Value 'DejaVu Sans Mono'

# Notez que si l'utilisateur à déjà installé des polices avec cette valeur chaîne la commande ne marchera pas
# Il faut alors changer le nom de la valeur chaîne dans la commande