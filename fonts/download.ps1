$FONTS = 0x14
$Path=".\fonts\DejaVuSansMono.ttf"
$objShell = New-Object -ComObject Shell.Application
$objFolder = $objShell.Namespace($FONTS)
$Fontdir = dir $Path
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
# All your available fonts are located here:
$T1key = 'HKLM:\Software\Microsoft\Windows NT\CurrentVersion\Fonts'

# But your Console fonts are located here:
$T2key = 'HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Console\TrueTypeFont'

Get-ItemProperty -Path $T2key
# To add more fonts, just add the new name like this: 
Set-ItemProperty -Path $T2key -Name '00000' -Value 'DejaVu Sans Mono'