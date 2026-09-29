pipeline {
    agent any

    environment {
        MSBUILD = "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe"

        PYTHON_DIR = "${WORKSPACE}\\Python"
        PYTHON_EXE = "${WORKSPACE}\\Python\\python.exe"

        PYTHON_VERSION = "3.12.10"
        PYTHON_ZIP = "${WORKSPACE}\\python.zip"
        PYTHON_URL = "https://www.python.org/ftp/python/3.12.10/python-3.12.10-embed-amd64.zip"

        GET_PIP = "${WORKSPACE}\\get-pip.py"
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Setup Portable Python') {
            steps {
                powershell '''
                    Write-Host "Setting up portable Python..."

                    if (!(Test-Path $env:PYTHON_DIR)) {
                        New-Item -ItemType Directory -Path $env:PYTHON_DIR -Force | Out-Null
                    }

                    if (!(Test-Path $env:PYTHON_EXE)) {
                        Write-Host "Downloading Python $env:PYTHON_VERSION..."

                        Invoke-WebRequest `
                            -Uri $env:PYTHON_URL `
                            -OutFile $env:PYTHON_ZIP

                        Expand-Archive `
                            -Path $env:PYTHON_ZIP `
                            -DestinationPath $env:PYTHON_DIR `
                            -Force

                        Remove-Item $env:PYTHON_ZIP -Force
                    }

                    Write-Host "Python version:"
                    & $env:PYTHON_EXE --version
                '''
            }
        }

        stage('Install CodeChecker') {
            steps {
                powershell '''
                    Write-Host "Installing pip into portable Python..."

                    Invoke-WebRequest `
                        -Uri "https://bootstrap.pypa.io/get-pip.py" `
                        -OutFile $env:GET_PIP

                    & $env:PYTHON_EXE $env:GET_PIP --no-warn-script-location

                    if ($LASTEXITCODE -ne 0) {
                        throw "pip installation failed."
                    }

                    Write-Host "Installing CodeChecker..."

                    & $env:PYTHON_EXE -m pip install --upgrade codechecker

                    if ($LASTEXITCODE -ne 0) {
                        throw "CodeChecker installation failed."
                    }

                    Write-Host "Checking CodeChecker..."

                    & $env:PYTHON_EXE -m CodeChecker version

                    if ($LASTEXITCODE -ne 0) {
                        throw "CodeChecker verification failed."
                    }
                '''
            }
        }

        stage('Check MSBuild') {
            steps {
                powershell '''
                    Write-Host "Checking MSBuild..."

                    if (!(Test-Path $env:MSBUILD)) {
                        throw "MSBuild not found: $env:MSBUILD"
                    }

                    & $env:MSBUILD -version
                '''
            }
        }
    }
}
