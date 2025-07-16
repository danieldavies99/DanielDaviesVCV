#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
==============================================================================
    A Python module to convert human readable knot patterns into
    a string version that can be used by the module.

    See: KnotPattern c++ class.
==============================================================================
'''

__author__ = "Daniel Davies"
__version__ = "Revision: 0.1"
__date__ = "Date: 07/2025"
__license__ = "Python"


control_code_dict = {
    'shift_down': 'S',
    'shift_up': 's',
    'reset': 'R',
    'swap_12': '1',
    'swap_23': '2',
    'swap_34': '3',
    'swap_14': '4',
    'swap_13': '5',
    'swap_24': '6',
    'swap_1234': '7',
    'swap_1423': '8',
    'swap_1324': '9',
    'undo': 'U',
    'redo': 'u',
    'random': 'X'
}

# directional
readable_lists = [
  ['shift_down', 'shift_up'],
]

# undo_redo
readable_lists += [
  ['random', 'undo'],
  ['random', 'reset', 'undo'],
  ['swap_13', 'reset', 'undo'],
  ['swap_13', 'undo'],
  ['swap_1234', 'undo'],
  ['undo', 'redo', 'swap_24'],
  ['swap_14', 'reset', 'undo'],
  ['random', 'swap_14', 'shift_down', 'undo'],
  ['swap_1234', 'swap_1423', 'undo'],
  ['swap_1423', 'undo'],
  ['swap_34', 'random', 'swap_1234', 'undo'],
]

# symmetrical
readable_lists += [
  ['swap_1234', 'swap_1324'],
  ['swap_1234', 'swap_23'],
  ['swap_1234', 'swap_1423'],
  ['swap_1423', 'swap_13', 'swap_1234'],
  ['swap_1324', 'swap_13', 'swap_24'],
  ['swap_34', 'swap_13'],
  ['swap_14', 'swap_1234', 'swap_12', 'swap_24'],
  ['swap_1324', 'swap_14', 'swap_13'],
  ['swap_1324', 'swap_34'],
  ['swap_34', 'swap_12', 'swap_1234'],
  ['swap_24', 'swap_12'],
  ['swap_1423', 'swap_1234'],
  ['swap_24', 'swap_14', 'swap_1423'],
  ['swap_1234', 'swap_34'],
  ['swap_34', 'swap_1234'],
  ['swap_1324', 'swap_13', 'swap_14', 'swap_23'],
  ['swap_14', 'swap_1324'],
  ['swap_12', 'swap_1423'],
  ['swap_12', 'swap_14', 'swap_23'],
  ['swap_1324', 'swap_14'],
  ['swap_14', 'swap_13'],
  ['swap_24', 'swap_1234', 'swap_23'],
  ['swap_12', 'swap_13', 'swap_1234'],
  ['swap_34', 'swap_14'],
  ['swap_14', 'swap_23', 'swap_12'],
  ['swap_14', 'swap_1423'],
  ['swap_13', 'swap_12', 'swap_1324'],
  ['swap_1324', 'swap_23', 'swap_1423', 'swap_24'],
  ['swap_14', 'swap_24', 'swap_23'],
]

# rotational
readable_lists += [
  ['swap_1234', 'shift_up'],
  ['swap_1234', 'shift_down'],
  ['swap_1234', 'shift_up', 'swap_1234', 'shift_down'],
  ['swap_1423', 'shift_down', 'reset'],
  ['swap_1324', 'shift_up', 'swap_1234'],
  ['swap_14', 'shift_down', 'swap_13'],
  ['swap_13', 'shift_up', 'swap_23'],
  ['swap_24', 'shift_down', 'swap_12'],
  ['swap_12', 'shift_up', 'swap_34'],
  ['swap_13', 'shift_up', 'swap_13'],
  ['swap_1423', 'shift_up'],
  ['swap_1234', 'shift_up', 'shift_down'],
  ['swap_13', 'shift_down', 'swap_1423'],
  ['swap_13', 'shift_down', 'swap_14'],
  ['swap_23', 'shift_up', 'swap_12'],
  ['swap_1324', 'shift_down', 'swap_1324'],
]

# memory
readable_lists += [
  ['swap_14', 'reset', 'undo'],
  ['reset', 'swap_13', 'swap_12'],
  ['reset', 'swap_1234', 'swap_1324'],
  ['reset', 'shift_down', 'swap_12'],
  ['reset', 'swap_1423'],
  ['reset', 'swap_34', 'undo'],
  ['reset', 'swap_13', 'redo'],
  ['reset', 'undo', 'swap_13'],
  ['reset', 'swap_24', 'redo'],
  ['reset', 'swap_12', 'shift_down'],
  ['reset', 'swap_1234', 'redo'],
  ['reset', 'swap_1324', 'shift_up'],
  ['reset', 'swap_1423', 'swap_24'],
]

# musical
readable_lists += [
  ['swap_13', 'swap_24', 'swap_1234'],
  ['swap_13', 'shift_up', 'swap_23', 'reset'],
  ['swap_13', 'swap_23', 'swap_13', 'swap_23'],
  ['swap_12', 'swap_23', 'swap_34', 'swap_14'],
  ['shift_up', 'shift_down', 'swap_12', 'swap_34'],
  ['swap_24', 'swap_13', 'shift_up', 'shift_down'],
  ['shift_up', 'shift_down', 'reset'],
  ['swap_12', 'swap_13', 'swap_14', 'swap_23'],
  ['swap_1324', 'swap_1423', 'shift_up'],
  ['swap_14', 'shift_up', 'shift_down'],
  ['swap_23', 'swap_12', 'reset'],
  ['swap_34', 'shift_up', 'shift_down'],
  ['swap_1234', 'swap_24', 'swap_13'],
  ['swap_12', 'swap_24', 'swap_34'],
  ['swap_13', 'swap_1423', 'shift_up'],
  ['swap_14', 'swap_12', 'shift_down'],
]

# chaotic
readable_lists += [
  ['random', 'swap_13', 'reset'],
  ['random', 'swap_13', 'swap_1423'],
  ['random', 'swap_14'],
  ['random', 'swap_24', 'swap_1234'],
  ['random', 'swap_13', 'undo'],
  ['random', 'shift_up'],
  ['random', 'shift_down'],
  ['random', 'reset', 'swap_13'],
  ['random', 'undo', 'redo'],
  ['random', 'swap_24', 'shift_up'],
  ['random', 'swap_14', 'redo'],
  ['random', 'swap_1423', 'shift_down'],
  ['random', 'swap_13', 'swap_14'],
  ['random', 'swap_12', 'swap_34'],
  ['random', 'swap_1423', 'redo'],
  ['reset', 'random', 'undo'],
  ['random', 'random', 'random', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo'],
  ['random', 'reset', 'random', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo'],
  ['random', 'undo', 'redo', 'undo', 'redo'],
  ['random', 'shift_up', 'shift_up', 'shift_up', 'shift_down', 'shift_down', 'shift_down'],
  ['random', 'swap_12', 'swap_34', 'swap_12', 'swap_34'],
  ['random', 'reset', 'swap_1234'],
  ['random', 'reset', 'swap_24', 'swap_1234'],
  ['random', 'reset', 'random', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo'],
  ['random', 'random', 'undo', 'undo'],
  ['random',  'swap_13', 'swap_24', 'undo', 'undo', 'undo'],
  ['random',  'shift_up', 'shift_down', 'undo', 'undo', 'undo'],
  ['random',  'shift_up', 'shift_up', 'undo', 'undo', 'undo'],
  ['random',  'shift_down', 'shift_down', 'undo', 'undo', 'undo'],
  ['random',  'shift_down', 'shift_down', 'shift_down', 'undo', 'undo', 'undo', 'undo', 'redo', 'redo', 'redo', 'redo'],
  ['random',  'shift_down', 'shift_down', 'shift_down', 'undo', 'undo', 'undo', 'undo', 'random'],
  ['random',  'random', 'undo', 'redo'],
  ['random',  'swap_24', 'swap_24', 'swap_12', 'swap_12'],
  ['random',  'swap_1234', 'swap_1234', 'swap_1423', 'swap_1423'],
  ['random',  'swap_1234', 'swap_1234', 'swap_1423', 'swap_1423', 'random', 'undo', 'undo', 'redo', 'redo'],
  ['random',  'swap_24', 'swap_24', 'swap_12', 'swap_12', 'undo', 'undo', 'redo', 'redo'],
  ['swap_1234',  'random', 'undo', 'random', 'undo', 'redo', 'undo', 'swap_1234'],
  ['swap_1234',  'random', 'undo', 'random', 'undo', 'redo', 'undo', 'swap_1423'],
  ['swap_12', 'swap_34',  'random', 'undo', 'random', 'undo', 'redo', 'undo', 'swap_12', 'swap_34'],
  ['random', 'reset',  'undo', 'undo', 'redo', 'redo'],
  ['random', 'reset',  'undo', 'undo', 'redo', 'redo','undo', 'undo', 'redo', 'redo', 'undo', 'undo', 'redo', 'redo'],
  ['random', 'swap_1234',  'undo', 'undo', 'redo', 'redo','undo', 'undo', 'redo', 'redo', 'undo', 'undo', 'redo', 'redo'],
  ['random', 'swap_1423',  'undo', 'undo', 'redo', 'redo','undo', 'undo', 'redo', 'redo', 'undo', 'undo', 'redo', 'redo'],
]

# return a list of paths inside a directory
# with a given file extension
def mapReadableListToString(readable):
    res = ''
    for key in readable:
        if key in control_code_dict:
            res += control_code_dict[key]
        else:
            print("ERROR: " + key + " doesn't exist in the control_code_dict")
    return res


def main():
    print("num patterns: " + str(len(readable_lists)))
    for i in range(len(readable_lists)):
        code_string = 'KnotPattern("' + mapReadableListToString(readable_lists[i]) + '"),'
        print(code_string)

main()