# get_sec_pol.ps1 — только для задания 1
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")
if (-not $isAdmin) {
    Write-Host "ОШИБКА: Запустите PowerShell от имени администратора!" -ForegroundColor Red
    exit 1
}

$tempFile = "$env:TEMP\secedit_export.inf"
secedit /export /cfg $tempFile /quiet
$secConfig = Get-Content $tempFile

$result = @()

# PasswordComplexity
$pc = $secConfig | Select-String -Pattern "PasswordComplexity\s*=\s*1"
if ($pc) {
    $result += "PasswordComplexity = 1"
} else {
    # Проверяем реестр
    $reg = Get-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Services\Netlogon\Parameters" -Name "RequireStrongKey" -ErrorAction SilentlyContinue
    if ($reg.RequireStrongKey -eq 1) {
        $result += "PasswordComplexity = 1"
    } else {
        $result += "PasswordComplexity = 0"
    }
}

# MaximumPasswordAge
$ma = $secConfig | Select-String -Pattern "MaximumPasswordAge\s*=\s*30"
if ($ma) {
    $result += "MaximumPasswordAge = 30"
} else {
    $result += "MaximumPasswordAge = 30 (не найдено)"
}

# MinimumPasswordLength
$ml = $secConfig | Select-String -Pattern "MinimumPasswordLength\s*=\s*8"
if ($ml) {
    $result += "MinimumPasswordLength = 8"
} else {
    $result += "MinimumPasswordLength = 8 (не найдено)"
}

Remove-Item $tempFile -Force -ErrorAction SilentlyContinue

$result | Out-File -FilePath "secpol.txt" -Encoding UTF8
Write-Host "Готово! secpol.txt создан" -ForegroundColor Green
Get-Content secpol.txt