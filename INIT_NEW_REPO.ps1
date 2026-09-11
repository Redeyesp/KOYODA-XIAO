$ErrorActionPreference = "Stop"

Write-Host "Initializing KOYODA-XIAO as a NEW Git repository..."

if (Test-Path ".git") {
    Write-Host ".git already exists; skipping git init."
} else {
    git init
    git branch -M main
}

git add -A
git commit -m "Start KOYODA-XIAO integration baseline"

Write-Host ""
Write-Host "Local repository initialized."
Write-Host "After creating an EMPTY GitHub repo named KOYODA-XIAO, run:"
Write-Host ""
Write-Host "  git remote add origin https://github.com/Redeyesp/KOYODA-XIAO.git"
Write-Host "  git push -u origin main"
