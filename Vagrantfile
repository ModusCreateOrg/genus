# -*- mode: ruby -*-
# vi: set ft=ruby :

box = ENV[BOX] || "bento/ubuntu-18.04"
# To build with arch linux, run:
#      BOX=archlinux/archlinux vagrant up
Vagrant.configure("2") do |config|
  # Use this for testing different Linux installs interactively, e.g.:
  #
  #    vagrant ssh -c /vagrant/scripts/build.sh
  #  
  config.vm.box = box
  config.vm.synced_folder "../creative-engine", "/creative-engine"
end
