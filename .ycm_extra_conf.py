import os
import ycm_core

flags = [
'-x', 'c++',
'-std=c++11',
'-isystem', '/usr/lib/c++/v1',
'-I', '/usr/include/qt/QtCore/',
'-I', '/usr/include/qt/QtGui/',
'-I', '/usr/include/qt/QtWidgets/',
'-I', '/usr/include/qt/QtDesigner/',
'-Wall',
'-Wextra',
'-pedantic',
]

def DirectoryOfThisScript():
  return os.path.dirname(os.path.abspath(__file__))

def FlagsForFile(filename):
  return {
    'flags': flags,
    'do_cache': True
  }
