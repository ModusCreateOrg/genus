#!/usr/bin/env groovy
pipeline {
    agent any

    stages {
        stage('Clean') {
            steps {
                sh 'git clean -fdx'
            }
        }
        stage('Checkout Libs') {
            steps {
                dir('creative-engine') {
                   git branch: 'master', url: 'git@github.com:ModusCreateOrg/creative-engine'
                }
            }
        }
        stage('Build') {
            steps {
                sh "scripts/docker-build.sh"
            }
        }
    }
}
