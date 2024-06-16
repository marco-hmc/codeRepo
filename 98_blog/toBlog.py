# project: project_os
# project: project_network
# project: project_ccpp
# project: project_compile
# project: project_essay
# project: project_data

import sys

if __name__ == '__main__':
    sys.path[0]="/home/marco/0_codeRepo/98_blog"

import json
import os
from attrGetter import FileAttrHandler
import sys
import re
import re
import shutil

class ToBlogHandler:
    def __init__(self, confPath):
        with open(confPath, 'r') as f:
            config = json.load(f)
            self.noteDir = config['noteDir']
            self.projectName = config['projectName']
            self.targetDir = config['targetDir']
            self.targetCoverImgDir = config['targetCoverImgDir']            
            self.targetPostImgDir = config['targetPostImgDir']
        self.confPath =confPath

    def processAttr(self, file_path):
        attr_getter = FileAttrHandler(file_path, self.confPath)
        if attr_getter.title != "":
            attr_getter.writeAttr(self.targetDir)
            return True
        return False
    
    def dealWithImg(self, file_path):
        sourceImgDir = os.path.join(os.path.dirname(file_path), '_imgs')
        
        # needToCreateImgsDir = os.path.join(self.targetDir, os.path.relpath(os.path.dirname(file_path), os.path.dirname(self.noteDir)))
        # targetImgDir = os.path.join(needToCreateImgsDir, '_imgs')
        
        if os.path.exists(sourceImgDir):
            os.makedirs(self.targetPostImgDir, exist_ok=True)
            for root, dirs, files in os.walk(sourceImgDir):
                for file in files:
                    img_path = os.path.join(root, file)
                    shutil.copy(img_path, self.targetPostImgDir)
    
    def traverseFiles(self):
        for root, dirs, files in os.walk(self.noteDir):
            for file in files:
                # {d}_*.md, {d}.{d}_*.md
                if re.match(r'\d+(\.\d+)?_.*\.md$', file):
                    file_path = os.path.join(root, file)
                    if(self.processAttr(file_path)):
                        self.dealWithImg(file_path)
        pass
    

if __name__ == '__main__':
    handler = ToBlogHandler("/home/marco/0_codeRepo/98_blog/blogConf.json")
    handler.traverseFiles()
    pass
