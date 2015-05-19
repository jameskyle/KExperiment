#!/opt/local/bin/python
import os
import sys
import re
import fnmatch
PROJECT_NAME = "KExperiment"

source_reg = re.compile(".*\.(cpp|h)$")
task_reg = re.compile("^\s*/+\s*(TODO|FIXME|BUG|NOTE|HACK):?\s*(.*)$", re.I)

source_match = source_reg.match
task_match = task_reg.match

def main():
    output = os.path.join(os.getcwd(), "{0}.tasks".format(PROJECT_NAME))
    
    if len(sys.argv) < 2:
        sys.stderr.write("You must provide a project root path\n")
        exit(1)
    
    if len(sys.argv) > 2:
        output = os.path.abspath(sys.argv[2])
        
    root = os.path.abspath(sys.argv[1])
    matches = []
    types = {
            "todo":  "err",
            "fixme": "err",
            "bug":   "err",
            "note":  "info", # currently undefined
            "hack":  "warn"
    }
    
    for root, dirs, files in os.walk(root):
        paths = [os.path.join(root, f) for f in filter(source_match, files)]
        
        matches.extend(paths)
    
    tasks = []
    
    
    for source in matches:
        with open(source, 'r') as f:
            lines = f.readlines()
            for line in lines:
                m = task_match(line)
                if m:
                    base = os.path.relpath(source)
                    line_number = lines.index(line) + 1
                    t = types.get(m.group(1).lower(), "info")
                    desc = "{0}: {1}".format(m.group(1), m.group(2))
                    
                    task = "{base}\t{line}\t{type}\t{desc}"
                    tasks.append(task.format(base=base, line=line_number,
                                             type=t, desc=desc))
                                             
    with open(output, 'w') as f:
        f.write("\n".join(tasks))
    
if __name__ == "__main__":
    main()