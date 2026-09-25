pipeline {
    agent any

    environment {
        MSBUILD = "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe"
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Check Tools') {
            steps {
                powershell '''
                    Write-Host "Checking MSBuild..."

                    if (!(Test-Path $env:MSBUILD)) {
                        throw "MSBuild not found: $env:MSBUILD"
                    }

                    & $env:MSBUILD -version

                    Write-Host ""
                    Write-Host "Checking CodeChecker..."

                    CodeChecker version

                    if ($LASTEXITCODE -ne 0) {
                        throw "CodeChecker is not available."
                    }

                    Write-Host ""
                    Write-Host "All required tools are available."
                '''
            }
        }
    }
}
