#!/opt/local/bin/python

import yaml
import os

def setup_template():
    template = """
#ifndef COMPONENTTEMPLATES_H
#define COMPONENTTEMPLATES_H
#include <QMap>
#include <QString>
#include <QList>

struct ComponentTemplates
{
  ComponentTemplates() {
    QMap<QString, QString>* map;
"""

    return template

def finalize_template(template):
    template += """
  }
  
  ~ComponentTemplates() {
    QMap<QString, QString>* map;
    QString key;
    
    while(!c_list.isEmpty())
    {
      map = c_list.takeLast();
      delete map;
    }
  }
  QList< QMap<QString, QString>* > c_list;

};
#endif
"""
    return template

def write_template(template):
    f = open("ComponentTemplates.h", "w")
    print >>f, template

def main():
    template = setup_template()
    data = yaml.load(open("components.yml"))
    
    for comp in data:
        f = os.path.abspath(comp["file"])
        desc = [l.strip() for l in comp["description"].split("\n")]
        desc = "\\n".join(desc)
        
        st =  '    map = new QMap<QString, QString>;\n'
        st += '    (*map)["description"] = "{desc}";\n'.format(desc=desc)
        st += '    (*map)["name"] = "{name}";\n'.format(name=comp["name"])
        st += '    (*map)["label"] = "{label}";\n'.format(label=comp["label"])
        st += '    (*map)["type"] = "{type}";\n'.format(type=comp["type"])
        st += '    (*map)["durationMSecs"] = "{dur}";\n'.format(dur=comp["durationMSecs"])
        st += '    (*map)["file"] = "{file}";\n'.format(file=f)
        
        if comp.has_key("audio"):
            st += '    (*map)["audio"] = "{audio}";\n'.format(audio=comp["audio"])

        elif comp.has_key("children"):
            st += '    (*map)["children"] = "{c}";\n'.format(c=comp["children"])

        elif comp.has_key("text"):
            st += '    (*map)["text"] = "{txt}";\n'.format(txt=comp["text"])
        
        elif comp.has_key("video"):
            st += '    (*map)["video"] = "{vid}";\n'.format(vid=comp["video"])

        if comp.has_key("delay"):
            st += '    (*map)["delay"] = "{delay}";\n'.format(delay=comp["delay"])

        st += '    c_list.append(map);\n\n'

        template += st

    template = finalize_template(template)
    
    write_template(template)

if __name__ == "__main__":
    main()
