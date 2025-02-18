%define debug_package %{nil}

%define tarname		medulla-filetree-generator
%define git                    SHA
%define use_git         1
%define branch integration
%define filetree_version 0.2

Summary:	Medulla Filetree Generator
Name:		medulla-filetree-generator
Version:	0.2
%if ! %use_git
Release:        1%{?dist}
%else
Release:        0.%git.1%{?dist}
%endif

BuildRequires:  gcc-c++

Source0:        %name-%version.tar.bz2
License:	MIT

Group:		Development/Python
Url:		http://www.siveo.net

%description
Pulse Filetree Generator is an utility that create a XML file with the
computer files. 
This allow to speed up Pulse filetransfert feature.

#--------------------------------------------------------------------

%package -n     pulse-filetree-generator
Summary:        Tools used to help debugging medulla
Group:          System/Servers

%description -n pulse-filetree-generator
Medulla Filetree Generator is an utility that create a XML file with the
computer files.
This allow to speed up Medulla filetransfert feature.

%files -n pulse-filetree-generator
%_var/lib/pulse2/clients/lin/deb/pulse-agent-linux/usr/sbin/pulse-filetree-generator
%_var/lib/pulse2/clients/lin/rpm/package/SOURCES/pulse-filetree-generator
%_var/lib/pulse2/clients/mac/pulse-filetree-generator
%_var/lib/pulse2/clients/win/pulse-filetree-generator.exe

%prep
%setup -q -n %name

%build
# Nothing to do

%install
mkdir -p %buildroot%_var/lib/pulse2/clients/win
cp windows/bin/pulse-filetree-generator.exe %buildroot%_var/lib/pulse2/clients/win
mkdir -p %buildroot%_var/lib/pulse2/clients/lin
g++ -O3 -std=c++11 linux_macos/pulse-filetree-generator.cpp -o pulse-filetree-generator
mkdir -p %buildroot%_var/lib/pulse2/clients/lin/deb/pulse-agent-linux/usr/sbin
cp pulse-filetree-generator %buildroot%_var/lib/pulse2/clients/lin/deb/pulse-agent-linux/usr/sbin
chmod +x %buildroot%_var/lib/pulse2/clients/lin/deb/pulse-agent-linux/usr/sbin/pulse-filetree-generator
mkdir -p %buildroot%_var/lib/pulse2/clients/lin/rpm/package/SOURCES
cp pulse-filetree-generator %buildroot%_var/lib/pulse2/clients/lin/rpm/package/SOURCES
chmod +x %buildroot%_var/lib/pulse2/clients/lin/rpm/package/SOURCES/pulse-filetree-generator
mkdir -p %buildroot%_var/lib/pulse2/clients/mac
mv pulse-filetree-generator %buildroot%_var/lib/pulse2/clients/mac
chmod +x %buildroot%_var/lib/pulse2/clients/mac/pulse-filetree-generator   
