powershell:
$profiles = netsh wlan show profiles | Where-Object { $_ -match ':' } | ForEach-Object { ($_ -split ':')[1].Trim() }

foreach ($name in $profiles) {
    $details = netsh wlan show profile name="$name" key=clear
    $passwordLine = $details | Where-Object { $_ -match 'da Chave|Key' }
    if ($passwordLine) {
        $password = ($passwordLine -replace '.*:\s*', '').Trim()
        Write-Output "$name : $password"
    } else {
        Write-Output "$name : (sem senha)"
    }
}
