#!/usr/bin/env groovy
pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
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
