import sys
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path)
sys.path.append(dir_path + "/lgrammar")

from lsystem_parse import parse
from lsystem_class import Lsystem
