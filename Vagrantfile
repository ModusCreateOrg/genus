# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # Use this for testing different Linux installs interactively, e.g.:
  #
  #    vagrant ssh -c /vagrant/scripts/build.sh
  #  
  #config.vm.box = "archlinux/archlinux"
  config.vm.box = "bento/ubuntu-18.04"
  config.vm.synced_folder "../creative-engine", "/creative-engine"
end
