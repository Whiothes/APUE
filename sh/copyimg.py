import os
import re
import shutil

srcdir = "/Users/zhoush/Dropbox/Calibre Library/W. Richard Stevens/Advanced Programming in the UNIX Environment (5)/APUE/OEBPS/html/graphics"
dstdir = "/Users/zhoush/Documents/Notes/books/system/APUE/"

files = (file for file in os.listdir(srcdir)
         if os.path.isfile(os.path.join(srcdir, file))
         and re.search("^[0-9]{2}fig.*?jpg", file))

for f in files:
    objdir = os.path.join(dstdir, "Chapter" + f[:2])
    if not os.path.isdir(objdir):
        if os.path.exists(objdir):
            os.remove(objdir)
            os.mkdir(objdir)
    shutil.copy2(os.path.join(srcdir, f), objdir)
