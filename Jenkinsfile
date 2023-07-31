pipeline {
    agent {
        label 'af'
    }

    environment {
        FROGRESS_KEY = credentials('af_frogress_key')
    }

    options {
        ansiColor('xterm')
    }

    stages {
        stage('Check formatting') {
            steps {
                echo 'Checking formatting...'
                sh 'bash -c "tools/check_format.sh 2>&1 >(tee tools/check_format.txt)"'
            }
        }
        stage('Install Python dependencies') {
            steps {
                echo 'Installing Python dependencies'
                sh 'python3 -m pip install -r requirements.txt -U'
            }
        }
        stage('Copy ROM') {
            steps {
                echo 'Setting up ROM...'
                sh 'cp /usr/local/etc/roms/af.jp.z64 baserom.jp.z64'
            }
        }
        stage('Setup') {
            steps {
                sh 'bash -c "make -j setup"'
            }
        }
        stage('Lib') {
            steps {
                sh 'bash -c "make -j lib"'
            }
        }
        stage('Extract') {
            steps {
                sh 'bash -c "make -j extract"'
            }
        }
        stage('Build') {
            steps {
                sh 'bash -c "make -j uncompressed"'
            }
        }
        stage('Build compressed') {
            steps {
                sh 'bash -c "make -j compressed"'
            }
        }
        stage('Upload to Frogress') {
            when {
                branch 'main'
            }
            steps {
                sh 'python3 ./tools/upload_frogress.py jp --apikey $FROGRESS_KEY'
            }
        }
    }
    post {
        failure {
            sh 'cat tools/check_format.txt'
        }
        always {
            cleanWs()
        }
    }
}
