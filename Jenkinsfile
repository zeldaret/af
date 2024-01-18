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
                sh 'python3 -m venv .venv'
                sh '''. .venv/bin/activate
                python3 -m pip install -U -r requirements.txt
                '''
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
                sh '''. .venv/bin/activate
                bash -c "make WARNINGS_CHECK=1 -j setup 2> >(tee tools/warnings_count/warnings_setup_new.txt)"
                '''
            }
        }
        stage('Check setup warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh setup"'
            }
        }
        stage('Lib') {
            steps {
                sh '''. .venv/bin/activate
                bash -c "make WARNINGS_CHECK=1 -j lib 2> >(tee tools/warnings_count/warnings_lib_new.txt)"
                '''
            }
        }
        stage('Check Lib warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh lib"'
            }
        }
        stage('Extract') {
            steps {
                sh '''. .venv/bin/activate
                bash -c "make WARNINGS_CHECK=1 -j extract 2> >(tee tools/warnings_count/warnings_extract_new.txt)"
                '''
            }
        }
        stage('Check extraction warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh extract"'
            }
        }
        stage('Build') {
            steps {
                sh '''. .venv/bin/activate
                bash -c "make WARNINGS_CHECK=1 -j uncompressed 2> >(tee tools/warnings_count/warnings_uncompressed_new.txt)"
                '''
            }
        }
        stage('Check build uncompressed warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh uncompressed"'
            }
        }
        stage('Build compressed') {
            steps {
                sh '''. .venv/bin/activate
                bash -c "make WARNINGS_CHECK=1 -j compressed 2> >(tee tools/warnings_count/warnings_compress_new.txt)"
                '''
            }
        }
        stage('Check compress warnings') {
            steps {
                sh 'bash -c "./tools/warnings_count/compare_warnings.sh compress"'
            }
        }
        stage('Upload to Frogress') {
            when {
                branch 'main'
            }
            steps {
                sh '''. .venv/bin/activate
                python3 ./tools/upload_frogress.py jp --apikey $FROGRESS_KEY
                '''
            }
        }
    }
    post {
        failure {
            sh 'cat tools/check_format.txt tools/warnings_count/warnings_setup_new.txt tools/warnings_count/warnings_lib_new.txt tools/warnings_count/warnings_extract_new.txt tools/warnings_count/warnings_uncompressed_new.txt tools/warnings_count/warnings_compress_new.txt'
        }
        always {
            cleanWs()
        }
    }
}
