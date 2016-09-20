#!/bin/bash


my_name=$0


function setup_environment {
  bf=""
  n=""
  ORGANISATION="UNICAMP - Universidade Estadual de Campinas"
  URL="http://www.ccuec.unicamp.br/ccuec/redesemfio_eduroam"
  SUPPORT="sauccuec@unicamp.br"
if [ ! -z "$DISPLAY" ] ; then
  if which zenity 1>/dev/null 2>&1 ; then
    ZENITY=`which zenity`
  elif which kdialog 1>/dev/null 2>&1 ; then
    KDIALOG=`which kdialog`
  else
    if tty > /dev/null 2>&1 ; then
      if  echo $TERM | grep -E -q "xterm|gnome-terminal|lxterminal"  ; then
        bf="[1m";
        n="[0m";
      fi
    else
      find_xterm
      if [ -n "$XT" ] ; then
        $XT -e $my_name
      fi
    fi
  fi
fi
}

function split_line {
echo $1 | awk  -F '\\\\n' 'END {  for(i=1; i <= NF; i++) print $i }'
}

function find_xterm {
terms="xterm aterm wterm lxterminal rxvt gnome-terminal konsole"
for t in $terms
do
  if which $t > /dev/null 2>&1 ; then
  XT=$t
  break
  fi
done
}


function ask {
     T="eduroam CAT"
#  if ! [ -z "$3" ] ; then
#     T="$T: $3"
#  fi
  if [ ! -z $KDIALOG ] ; then
     if $KDIALOG --yesno "${1}\n${2}?" --title "$T" ; then
       return 0
     else
       return 1
     fi
  fi
  if [ ! -z $ZENITY ] ; then
     text=`echo "${1}" | fmt -w60`
     if $ZENITY --no-wrap --question --text="${text}\n${2}?" --title="$T" ; then
       return 0
     else
       return 1
     fi
  fi

  yes=S
  no=N
  yes1=`echo $yes | awk '{ print toupper($0) }'`
  no1=`echo $no | awk '{ print toupper($0) }'`

  if [ $3 == "0" ]; then
    def=$yes
  else
    def=$no
  fi

  echo "";
  while true
  do
  split_line "$1"
  read -p "${bf}$2 ${yes}/${no}? [${def}]:$n " answer
  if [ -z "$answer" ] ; then
    answer=${def}
  fi
  answer=`echo $answer | awk '{ print toupper($0) }'`
  case "$answer" in
    ${yes1})
       return 0
       ;;
    ${no1})
       return 1
       ;;
  esac
  done
}

function alert {
  if [ ! -z $KDIALOG ] ; then
     $KDIALOG --sorry "${1}"
     return
  fi
  if [ ! -z $ZENITY ] ; then
     $ZENITY --warning --text="$1"
     return
  fi
  echo "$1"

}

function show_info {
  if [ ! -z $KDIALOG ] ; then
     $KDIALOG --msgbox "${1}"
     return
  fi
  if [ ! -z $ZENITY ] ; then
     $ZENITY --info --width=500 --text="$1"
     return
  fi
  echo "$1"
}

function confirm_exit {
  if [ ! -z $KDIALOG ] ; then
     if $KDIALOG --yesno \"Tem a certeza que pretende desistir?\"  ; then
     exit 1
     fi
  fi
  if [ ! -z $ZENITY ] ; then
     if $ZENITY --question --text=\"Tem a certeza que pretende desistir?\" ; then
        exit 1
     fi
  fi
}



function prompt_nonempty_string {
  prompt=$2
  if [ ! -z $ZENITY ] ; then
    if [ $1 -eq 0 ] ; then
     H="--hide-text "
    fi
    if ! [ -z "$3" ] ; then
     D="--entry-text=$3"
    fi
  elif [ ! -z $KDIALOG ] ; then
    if [ $1 -eq 0 ] ; then
     H="--password"
    else
     H="--inputbox"
    fi
  fi


  out_s="";
  if [ ! -z $ZENITY ] ; then
    while [ ! "$out_s" ] ; do
      out_s=`$ZENITY --entry --width=300 $H $D --text "$prompt"`
      if [ $? -ne 0 ] ; then
        confirm_exit
      fi
    done
  elif [ ! -z $KDIALOG ] ; then
    while [ ! "$out_s" ] ; do
      out_s=`$KDIALOG $H "$prompt" "$3"`
      if [ $? -ne 0 ] ; then
        confirm_exit
      fi
    done  
  else
    while [ ! "$out_s" ] ; do
      read -p "${prompt}: " out_s
    done
  fi
  echo "$out_s";
}

function user_cred {
  PASSWORD="a"
  PASSWORD1="b"

  if ! USER_NAME=`prompt_nonempty_string 1 "introduza o seu userid"` ; then
    exit 1
  fi

  while [ "$PASSWORD" != "$PASSWORD1" ]
  do
    if ! PASSWORD=`prompt_nonempty_string 0 "introduza a sua password"` ; then
      exit 1
    fi
    if ! PASSWORD1=`prompt_nonempty_string 0 "repita a sua password"` ; then
      exit 1
    fi
    if [ "$PASSWORD" != "$PASSWORD1" ] ; then
      alert "as passwords não coincidem"
    fi
  done
}
setup_environment
show_info "Este instalador foi criado para a/o ${ORGANISATION}\n\nMais informações e comentários:\n\nEMAIL: ${SUPPORT}\nWWW: ${URL}\n\nInstalador criado com software do projecto GEANT."
if ! ask "Este instalador só funcionará correctamente se for membro de ${bf}UNICAMP - Universidade Estadual de Campinas.${n}" "Continue" 1 ; then exit; fi
if [ -d $HOME/.cat_installer ] ; then
   if ! ask "A diretoria $HOME/.cat_installer já existe; alguns dos ficheiros podem ser sobrepostos. " "Continue" 1 ; then exit; fi
else
  mkdir $HOME/.cat_installer
fi
# save certificates
echo "-----BEGIN CERTIFICATE-----
MIIEUDCCAzigAwIBAgIBATANBgkqhkiG9w0BAQUFADCBljELMAkGA1UEBhMCQlIx
DDAKBgNVBAoTA1JOUDEPMA0GA1UEChMGSUNQRURVMQ4wDAYDVQQLEwVHT1BBQzEX
MBUGA1UEAxMOQUMgUmFpeiBJQ1BFRFUxCzAJBgNVBAgTAkRGMREwDwYDVQQHEwhC
cmFzaWxpYTEfMB0GCSqGSIb3DQEJARYQZ29wYWNAaWNwLmVkdS5icjAeFw0wODEx
MTExNjMyMTVaFw0zMzExMTExNjMyMTVaMIGWMQswCQYDVQQGEwJCUjEMMAoGA1UE
ChMDUk5QMQ8wDQYDVQQKEwZJQ1BFRFUxDjAMBgNVBAsTBUdPUEFDMRcwFQYDVQQD
Ew5BQyBSYWl6IElDUEVEVTELMAkGA1UECBMCREYxETAPBgNVBAcTCEJyYXNpbGlh
MR8wHQYJKoZIhvcNAQkBFhBnb3BhY0BpY3AuZWR1LmJyMIIBIjANBgkqhkiG9w0B
AQEFAAOCAQ8AMIIBCgKCAQEAxNzNR2uhRDcKWFq//wCOYvT/LU3BgrDA51cznr8f
6bPENcCYLEoDktg5iZC8hhsF8cEs3kq2quq3uFrxydg65VlwautsLDFRnLvYxY8B
UPgdqiyCEW/mz2qmC1RVJab42rXHJWhwEPpIW1NxRXF/O5EtXPs0A6/YsAcJWPzG
4Oyl6TrlI240Ebct0t0+I6b2ilUu+GIJ2rKkXHkVL+M/Du5gtwXVrt9nD02O/KG6
enXbF8C3gzwkrzDOfOKSX91YS+tFCS/8UBUPUHEtr15JMBr9VEulbDS/wt4cbIWG
yeWJBeFw1gBbVWz5At3UlX8hQhO8R3IOvoQZwkowHsOypwIDAQABo4GmMIGjMBsG
A1UdEQQUMBKBEGdvcGFjQGljcC5lZHUuYnIwHQYDVR0OBBYEFIgfPUG1APRpeK2n
ZZuq75+canikMAwGA1UdEwQFMAMBAf8wSgYDVR0fBEMwQTA/oD2gO4Y5aHR0cDov
L3d3dy5pY3AuZWR1LmJyL3JlcG9zaXRvcmlvL2FjLXJhaXovbGNyLWFjLXJhaXou
Y3JsMAsGA1UdDwQEAwIBBjANBgkqhkiG9w0BAQUFAAOCAQEAfHm+YlYg57/tP7g9
ieSf6ZqLyYwRVurImYJTodsbCX1yMwxZaCGNabZQTnb3DCCkwWJDyXmkjCsyNbvh
0CnBPI41L6Z4/lKlJIupWCKgTqOf2BWFVXkI5ZDhzIWzANDCmL1x5ETWrHAfzXDE
aKIqyUaiyS+HRUSRf6upfF1nyWXSf2VSNsCNgyZ9iUeyceCGNFmy4FbecoOmVK8n
ZBdU56biHIMzdXYSPdMNBFgBGFBD/L3HcLyMqxiiRBGZXitah5tr1mkNCgJbInUO
uat+qoWu9Ekj+ne6lkhK0hdWmclUVsc44jNVoCelJuIVTX/KwGDXIlNodfHTOHwT
hP7Sgg==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIDXzCCAkegAwIBAgILBAAAAAABIVhTCKIwDQYJKoZIhvcNAQELBQAwTDEgMB4G
A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjMxEzARBgNVBAoTCkdsb2JhbFNp
Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDkwMzE4MTAwMDAwWhcNMjkwMzE4
MTAwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMzETMBEG
A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI
hvcNAQEBBQADggEPADCCAQoCggEBAMwldpB5BngiFvXAg7aEyiie/QV2EcWtiHL8
RgJDx7KKnQRfJMsuS+FggkbhUqsMgUdwbN1k0ev1LKMPgj0MK66X17YUhhB5uzsT
gHeMCOFJ0mpiLx9e+pZo34knlTifBtc+ycsmWQ1z3rDI6SYOgxXG71uL0gRgykmm
KPZpO/bLyCiR5Z2KYVc3rHQU3HTgOu5yLy6c+9C7v/U9AOEGM+iCK65TpjoWc4zd
QQ4gOsC0p6Hpsk+QLjJg6VfLuQSSaGjlOCZgdbKfd/+RFO+uIEn8rUAVSNECMWEZ
XriX7613t2Saer9fwRPvm2L7DWzgVGkWqQPabumDk3F2xmmFghcCAwEAAaNCMEAw
DgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFI/wS3+o
LkUkrk1Q+mOai97i3Ru8MA0GCSqGSIb3DQEBCwUAA4IBAQBLQNvAUKr+yAzv95ZU
RUm7lgAJQayzE4aGKAczymvmdLm6AC2upArT9fHxD4q/c2dKg8dEe3jgr25sbwMp
jjM5RcOO5LlXbKr8EpbsU8Yt5CRsuZRj+9xTaGdWPoO4zzUhw8lo/s7awlOqzJCK
6fBdRoyV3XpYKBovHd7NADdBj+1EbddTKJd+82cEHhXXipa0095MJ6RMG3NzdvQX
mcIfeg7jLQitChws/zyrVQ4PkX4268NXSb7hLi18YIvDQVETI53O9zJrlAGomecs
Mx86OyXShkDOOyyGeMlhLxS67ttVb9+E7gUJTb0o2HLO02JQZR7rkpeDMdmztcpH
WD9f
-----END CERTIFICATE-----
" > $HOME/.cat_installer/ca.pem
function run_python_script {
PASSWORD=$( echo "$PASSWORD" | sed "s/'/\\\'/g" )
python << EOF > /dev/null 2>&1
#-*- coding: utf-8 -*-
import dbus
import re
import sys
import uuid
import os

class EduroamNMConfigTool:

    def connect_to_NM(self):
        #connect to DBus
        try:
            self.bus = dbus.SystemBus()
        except dbus.exceptions.DBusException:
            print "Can't connect to DBus"
            sys.exit(2)
        #main service name
        self.system_service_name = "org.freedesktop.NetworkManager"
        #check NM version
        nm_version = self.check_nm_version()
        if nm_version == "0.9":
            self.settings_service_name = self.system_service_name
            self.connection_interface_name = "org.freedesktop.NetworkManager.Settings.Connection"
            #settings proxy
            sysproxy = self.bus.get_object(self.settings_service_name, "/org/freedesktop/NetworkManager/Settings")
            #settings intrface
            self.settings = dbus.Interface(sysproxy, "org.freedesktop.NetworkManager.Settings")
        elif nm_version == "0.8":
            #self.settings_service_name = "org.freedesktop.NetworkManagerUserSettings"
            self.settings_service_name = "org.freedesktop.NetworkManager"
            self.connection_interface_name = "org.freedesktop.NetworkManagerSettings.Connection"
            #settings proxy
            sysproxy = self.bus.get_object(self.settings_service_name, "/org/freedesktop/NetworkManagerSettings")
            #settings intrface
            self.settings = dbus.Interface(sysproxy, "org.freedesktop.NetworkManagerSettings")
        else:
            print "This Network Manager version is not supported"
            sys.exit(2)

    def check_opts(self):
        self.cacert_file = '${HOME}/.cat_installer/ca.pem'
        self.pfx_file = '${HOME}/.cat_installer/user.p12'
        if not os.path.isfile(self.cacert_file):
            print "Certificate file not found, looks like a CAT error"
            sys.exit(2)

    def check_nm_version(self):
        try:
            proxy = self.bus.get_object(self.system_service_name, "/org/freedesktop/NetworkManager")
            props = dbus.Interface(proxy, "org.freedesktop.DBus.Properties")
            version = props.Get("org.freedesktop.NetworkManager", "Version")
        except dbus.exceptions.DBusException:
            version = "0.8"
        if re.match(r'^0\.9', version):
            return "0.9"
        if re.match(r'^0\.8', version):
            return "0.8"
        else:
            return "Unknown version"

    def byte_to_string(self, barray):
        return "".join([chr(x) for x in barray])


    def delete_existing_connections(self, ssid):
        "checks and deletes earlier connections"
        try:
            conns = self.settings.ListConnections()
        except dbus.exceptions.DBusException:
            print "DBus connection problem, a sudo might help"
            exit(3)
        for each in conns:
            con_proxy = self.bus.get_object(self.system_service_name, each)
            connection = dbus.Interface(con_proxy, "org.freedesktop.NetworkManager.Settings.Connection")
            try:
               connection_settings = connection.GetSettings()
               if connection_settings['connection']['type'] == '802-11-wireless':
                   conn_ssid = self.byte_to_string(connection_settings['802-11-wireless']['ssid'])
                   if conn_ssid == ssid:
                       connection.Delete()
            except dbus.exceptions.DBusException:
               pass

    def add_connection(self,ssid):
        s_con = dbus.Dictionary({
            'type': '802-11-wireless',
            'uuid': str(uuid.uuid4()),
            'permissions': ['user:$USER'],
            'id': ssid 
        })
        s_wifi = dbus.Dictionary({
            'ssid': dbus.ByteArray(ssid),
            'security': '802-11-wireless-security'
        })
        s_wsec = dbus.Dictionary({
            'key-mgmt': 'wpa-eap',
            'proto': ['rsn',],
            'pairwise': ['ccmp',],
            'group': ['ccmp', 'tkip']
        })
        s_8021x = dbus.Dictionary({
            'eap': ['ttls'],
            'identity': '$USER_NAME',
            'ca-cert': dbus.ByteArray("file://" + self.cacert_file + "\0"),
            'subject-match': 'unicamp.br',
            'password': '$PASSWORD',
            'phase2-auth': 'pap',
            'anonymous-identity': 'anonymous@unicamp.br',
        })
        s_ip4 = dbus.Dictionary({'method': 'auto'})
        s_ip6 = dbus.Dictionary({'method': 'auto'})
        con = dbus.Dictionary({
            'connection': s_con,
            '802-11-wireless': s_wifi,
            '802-11-wireless-security': s_wsec,
            '802-1x': s_8021x,
            'ipv4': s_ip4,
            'ipv6': s_ip6
        })
        self.settings.AddConnection(con)

    def main(self):
        self.check_opts()
        ver = self.connect_to_NM()
        self.delete_existing_connections('eduroam')
        self.add_connection('eduroam')

if __name__ == "__main__":
    ENMCT = EduroamNMConfigTool()
    ENMCT.main()
EOF
}
function create_wpa_conf {
  cat << EOFW >> $HOME/.cat_installer/cat_installer.conf

  network={
    ssid="eduroam"
    key_mgmt=WPA-EAP
    pairwise=CCMP
    group=CCMP TKIP
    eap=TTLS
    ca_cert="${HOME}/.cat_installer/ca.pem"
    identity="${USER_NAME}"
    subject_match="unicamp.br"
    phase2="auth=PAP"
    password="${PASSWORD}"
    anonymous_identity="anonymous@unicamp.br"
  }
  EOFW
  chmod 600 $HOME/.cat_installer/cat_installer.conf
}
#prompt user for credentials
  user_cred
  if python run_python_script ; then
   show_info "Instalação realizada com sucesso"
else
   show_info "Configuração através do Network Manager falhou, a gerar o ficheiro de configuração wpa_supplicant.conf"
if [ -f $HOME/.cat_installer/cat_installer.conf ] ; then
  if ! ask "O ficheiro $HOME/.cat_installer/cat_installer.conf já existe; será sobreposto. " "Continue" 1 ; then confirm_exit; fi
  rm $HOME/.cat_installer/cat_installer.conf
  fi
   create_wpa_conf
   show_info "Resultado armazenado em $HOME/.cat_installer/cat_installer.conf"
fi
