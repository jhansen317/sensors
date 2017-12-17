# Server code and configuration

Server Installation:

	-> % uname -a
	Linux ice-station-zebra 4.10.0-32-generic #36-Ubuntu SMP Tue Aug 8 12:10:06 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
	-> % lsb_release -a
	No LSB modules are available.
	Distributor ID:	Ubuntu
	Description:	Ubuntu 17.04
	Release:	17.04
	Codename:	zesty

Dependencies:

    -> % wget https://bootstrap.pypa.io/get-pip.py
    -> % sudo python get-pip.py

    -> % sudo apt-get install apache2 libapache2-mod-wsgi mongodb mosquitto mosquitto-clients build-essential python-dev

Python packages in requirements.txt

    -> % sudo pip install -r requirements.txt

