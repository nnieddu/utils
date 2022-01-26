#Ubuntu
sudo mkdir -p /etc/apt/backup_srcs/ 
wget https://raw.githubusercontent.com/nnieddu/utils/main/ubuntu/backup/sources.list
sudo mv -bi /etc/apt/sources.list /etc/apt/backup_srcs/
sudo mv -f sources.list /etc/apt/
# Update to same host os/ubuntu version : 
sudo sed -i "s/focal/$(lsb_release -c -s)/" /etc/apt/sources.list
sudo add-apt-repository universe
sudo add-apt-repository multiverse
sudo apt update