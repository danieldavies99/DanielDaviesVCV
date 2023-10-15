#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
==============================================================================
    A Python module to convert all the svg source files into the manual pdf
     according to the following inkscape options:
    --without-gui
    --export-area-drawing
    For more inkscape options see: http://inkscape.org/doc/inkscape-man.html
    
    I've only used this on windows and I wrote it very badly. I'm basically
    certain this won't work on other OS's due to file path stuff that I've
    done lazily
==============================================================================
'''
import os
from subprocess import PIPE, run
from pypdf import PdfMerger
import re

__author__ = "Daniel Davies"
__version__ = "Revision: 0.1"
__date__ = "Date: 10/2023"
__license__ = "Python"

# config
inkscape_path = "C:\Program Files\Inkscape\\bin\\inkscape"
script_path = os.path.realpath(os.path.dirname(__file__))
svg_src_path = script_path + '\..\src'
pdf_dist_path = script_path + '\..\dist'
manual_file_path = script_path + '\..\daniel_davies_modular_manual.pdf'

# return a list of paths inside a directory
# with a given file extension
def getFileList(search_path, extension):
    file_list = []
    for path, subdirs, files in os.walk(search_path):
        for file in files:
            if file.endswith(extension):
                abspath_file = path + os.sep + file
                file_list.append(abspath_file)
    print('%i %s files found: %s' %(len(file_list), extension, search_path))
    return file_list
                
# ignore any files that dont match this pattern
# {a varying number of random characters}\{3 digit number}{random number of varying characters}.svg
def ignore_non_numbered_files(file_list):
    pattern = r'.*\d{3}.*\.svg'
    filtered_strings = [s for s in file_list if re.match(pattern, s)]
    num_ignored_files = len(file_list) - len(filtered_strings)
    print("Ignoring %i non-numbered file(s)" %num_ignored_files)
    return filtered_strings

# given an svg filename e.g yeet.svg
# return the same filename with the extension replaced with .pdf
def svg_file_name_to_pdf_file_name(svg_file_name):
    extension_removed = svg_file_name.split(".")[0]
    return extension_removed + '.pdf'

# given a list of svg paths
# convert to pdf files using
# inkscape's cli
def svg2pdf(list):
    """Convert all svg files to pdf according to specified options"""

    print ('\nConverting, please wait...\n')
    for file in list:
        print ('\nConverting file: %s' %file)
        svg_file_name = file.split('\\')[-1]
        pdf_file_name = svg_file_name_to_pdf_file_name(svg_file_name)
        output_file_name = pdf_dist_path + '\\' + pdf_file_name
        result = run(
            [
                inkscape_path,
                '--export-area-page',
                '--export-type=pdf',
                '--export-filename=' + output_file_name,
                file
            ],
            stdout=PIPE,
            stderr=PIPE,
            universal_newlines=True,
        )

        # if this script stops working
        # uncomment this line to see
        # inkscape errors:

        # print(result.returncode, result.stdout, result.stderr)

# given a list of pdf paths
# merge all pdfs into a single pdf file
def merge_pdfs(pdfs):
    print('merging pdfs')
    merger = PdfMerger()
    
    for pdf in pdfs:
        print('merging', pdf)
        merger.append(pdf)

    merger.write(manual_file_path)
    merger.close()

    print("PDF file generated", manual_file_path, "GG :)")

# convert page svgs to pdfs
# flatten pdfs into a single pdf
# profit
if __name__ == "__main__":
    print (__doc__)
    svg_files = getFileList(svg_src_path, ".svg")
    pruned_svg_files = ignore_non_numbered_files(svg_files)
    svg2pdf(pruned_svg_files)

    pdf_files = getFileList(pdf_dist_path, '.pdf')
    merge_pdfs(pdf_files)