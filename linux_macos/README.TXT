Programme  create json tree Filesystem Hierarchy linux 
make install in /usr/sbin/pulse-filetree-generator
genere file in "/tmp/treejson.json"

g++ -O3 pulse-filetree-generator.cpp -o /usr/sbin/pulse-filetree-generator


./pulse-filetree-generator -r / -o /tmp/azerty.txt -h
Usage : 
	command : ./pulse-filetree-generator

	mandatory parameter :
		 -r "root file system"

	optional parameters :
		 -f "file configuration"   /etc/pulse-xmpp-agent/agentconf.ini par default
		 -o "file output"          /tmp/file.txt par default

	Example :
	./pulse-filetree-generator -r "/" -o "/tmp/azerty.txt" -f "etc/pulse-xmpp-agent/agentconf.ini"

	 definir listexclude dans fichier de configuration section browserfile
example :
[browserfile]
defaultdir = /tmp
rootfilesystem = /tmp
listexclude = /usr, /lib,/boot,/cdrom,/dev,/lib32,/lib64,/lost+found,/media,/mnt,/opt,/partage,/proc,/root,/run,/sbin,/snap,/somewhere,/srv,/sys

