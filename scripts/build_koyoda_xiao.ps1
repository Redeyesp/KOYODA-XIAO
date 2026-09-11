$ErrorActionPreference = "Stop"

Write-Host "KOYODA-XIAO M0.1"
Write-Host "Target: Waveshare ESP32-S3-Touch-AMOLED-1.75"
Write-Host "Expected ESP-IDF: v6.0.2"
Write-Host ""

if (-not $env:IDF_PATH) {
    throw "IDF_PATH is not set. Open an ESP-IDF v6.0.2 PowerShell first."
}

python scripts/build.py waveshare/esp32-s3-touch-amoled-1.75 `
    --name esp32-s3-touch-amoled-1.75 `
    --language th-TH `
    --wake-word disabled

if ($LASTEXITCODE -ne 0) {
    throw "KOYODA-XIAO build failed."
}

Write-Host ""
Write-Host "Build passed."
Write-Host "Merged firmware: build\merged-binary.bin"
