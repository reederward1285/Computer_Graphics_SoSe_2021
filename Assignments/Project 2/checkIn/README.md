__author__ = "David Melamend, Reeder Ward, Majbrit Schoettner"
__email__ = "dmelamed@stud.hs-bremen.de, rward@stud.hs-bremen.de, mshoettner@stud.hs-bremen.de"
__title__ = "Implement Toolchain for .OBJ Objects in PyQt5 GUI to Create a 3D Modelling Software"
__course__ = "Computer Graphics"

Install requirements by running these bash commands:
```
sudo apt-get -y install python3
sudo apt-get -y install python3-pip
sudo pip3 install virtualenv
python3 -m venv PYTHON_ENV
source PYTHON_ENV/bin/activate
sudo apt-get -y install python3 python3-pip
pip3 install pyqt5 numpy matplotlib
```

Then, run the program:
```
./start.sh
```

Now that the program is fully installed, just run these commands from the linux command line to run the program:
```
source PYTHON_ENV/bin/activate
./start.sh
```

And after you stop the program,
```
deactivate
```
to turn off the python virtual environment.