pipeline {
    agent any

    environment {
        BUILD_DIR = 'build'
        RESULTS_DIR = 'codechecker-reports'
        COMPILE_DB = 'build/compile_commands.json'
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Configure') {
            steps {
                bat '''
                    cmake -S . -B %BUILD_DIR% ^
                        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                    cmake --build %BUILD_DIR% --config Release
                '''
            }
        }

        stage('Static Analysis') {
            steps {
                bat '''
                    if exist %RESULTS_DIR% rmdir /s /q %RESULTS_DIR%

                    CodeChecker analyze ^
                        %COMPILE_DB% ^
                        -o %RESULTS_DIR%
                '''
            }
        }

        stage('Store Results') {
            steps {
                bat '''
                    CodeChecker store ^
                        %RESULTS_DIR% ^
                        --name "Jenkins-%BUILD_NUMBER%"
                '''
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'codechecker-reports/**',
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
