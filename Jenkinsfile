```groovy
pipeline {
    agent any

    environment {
        // Visual Studio / MSBuild
        MSBUILD = "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe"

        // C++ project
        PROJECT      = "login.vcxproj"
        BUILD_CONFIG = "Production"
        PLATFORM     = "x64"

        // CodeChecker
        CODECHECKER_RESULTS = "codechecker-reports"
        CODECHECKER_BUILD   = "codechecker-build"

        // CodeChecker server
        CODECHECKER_SERVER = "http://localhost:8001"
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
                '''
            }
        }

        stage('Build') {
            steps {
                powershell '''
                    Write-Host "Building $env:PROJECT..."

                    & $env:MSBUILD $env:PROJECT `
                        /p:Configuration=$env:BUILD_CONFIG `
                        /p:Platform=$env:PLATFORM `
                        /m

                    if ($LASTEXITCODE -ne 0) {
                        throw "Build failed."
                    }

                    Write-Host "Build completed successfully."
                '''
            }
        }

        stage('Static Analysis') {
            steps {
                powershell '''
                    Write-Host "Running CodeChecker analysis..."

                    if (Test-Path $env:CODECHECKER_RESULTS) {
                        Remove-Item `
                            $env:CODECHECKER_RESULTS `
                            -Recurse `
                            -Force
                    }

                    if (Test-Path $env:CODECHECKER_BUILD) {
                        Remove-Item `
                            $env:CODECHECKER_BUILD `
                            -Recurse `
                            -Force
                    }

                    New-Item `
                        -ItemType Directory `
                        -Path $env:CODECHECKER_BUILD `
                        -Force | Out-Null

                    CodeChecker log `
                        -b "& '$env:MSBUILD' '$env:PROJECT' /p:Configuration=$env:BUILD_CONFIG /p:Platform=$env:PLATFORM /m" `
                        -o "$env:CODECHECKER_BUILD\\compile_commands.json"

                    if ($LASTEXITCODE -ne 0) {
                        throw "CodeChecker failed to capture the build."
                    }

                    CodeChecker analyze `
                        "$env:CODECHECKER_BUILD\\compile_commands.json" `
                        -o "$env:CODECHECKER_RESULTS"

                    if ($LASTEXITCODE -ne 0) {
                        throw "CodeChecker analysis failed."
                    }

                    Write-Host "Static analysis completed."
                '''
            }
        }

        stage('Store Results') {
            steps {
                powershell '''
                    Write-Host "Storing CodeChecker results..."

                    CodeChecker store `
                        "$env:CODECHECKER_RESULTS" `
                        --name "ipsatestci-$env:BUILD_NUMBER" `
                        --url "$env:CODECHECKER_SERVER"

                    if ($LASTEXITCODE -ne 0) {
                        throw "Failed to store CodeChecker results."
                    }

                    Write-Host "Results stored successfully."
                '''
            }
        }
    }

    post {
        always {
            archiveArtifacts `
                artifacts: 'codechecker-reports/**', `
                allowEmptyArchive: true
        }

        success {
            echo 'Build and static analysis completed successfully.'
        }

        failure {
            echo 'Build or static analysis failed.'
        }
    }
}
```
