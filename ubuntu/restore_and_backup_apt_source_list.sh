#Ubuntu
sudo mkdir -p /etc/apt/backup_srcs/ 
wget https://gist.githubusercontent.com/ninieddu/utils/ubuntu/backup/sources.list
sudo mv -b /etc/apt/sources.list /etc/apt/backup_srcs/sources.list.bak
sudo mv -fb sources.list /etc/apt/sources.list 
# Update to same host os/ubuntu version : 
sudo sed -i "s/focal/$(lsb_release -c -s)/" /etc/apt/sources.list
sudo add-apt-repository universe
sudo add-apt-repository multiverse
sudo apt update