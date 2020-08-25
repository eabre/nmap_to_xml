#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#define MAXU 2048

#define MY_ENCODING "ISO-8859-1"

int i= 0;
void save_to_file(xmlDoc *doc, char *file_name) {
  xmlChar *xmlbuff;
  int buffersize;
  FILE *fp;

  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);

  fp = fopen(file_name, "w+");
  fprintf(fp, xmlbuff);
  fclose(fp);
}
void setElementAttribute(xmlNodePtr element, char* attribName, char* attribValue)
{
    xmlSetProp(element, BAD_CAST attribName, BAD_CAST attribValue);
}
xmlNodePtr addChild(xmlNodePtr parent, char* name, char* value)
{
    return xmlNewChild(parent, NULL, BAD_CAST name, BAD_CAST value);
}
xmlNodePtr createRoot(xmlDocPtr doc, char* name)
{
    xmlNodePtr root;
    root = xmlNewNode(NULL, BAD_CAST name);
    xmlDocSetRootElement(doc, root);
    return root;
}
int row_saver(char  texter[MAXU], char row[MAXU])
{

    int k = 0;
    while(1)
    {
        if(texter[i] != '\n')
        {
            row[k]= texter[i];
            i++;
            k++;

        }
        else
        {
            i++;
            k=0;
            break;
        }
    }
    return i;
}

int main() {
    int q = 0;
    char cv[64];
    char ct[64];
    char Node_name[64];
    int j= 0, k= 0, w = 0, row_num = 0, char_num = 0;
    char row_tot[MAXU][MAXU]; //total rows of text
    xmlDoc *doc = NULL;
    xmlNode* new_node= NULL;
    xmlNode* root_element = NULL;

    FILE* fp;
    char texter[10192];
    int count = 0;

    fp= fopen("nmap_test.txt","r");
    if(fp == NULL)
    {
            printf("Could not find nmap_test.txt\n");
            return -1;
    }

    while (1)
    {
            texter[count]= fgetc(fp);
            if(texter[count] == '\n')
            {
                row_num++;

            }
            count++;
            if(feof(fp))
            {
                break;
            }
    }

    count= 0;
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
    memset(row_tot, 0x00, sizeof (row_tot));
    while(j< row_num)
    {
        k= row_saver(texter, row_tot[j]);
        j++;
    }
    j= 0;
    doc = xmlNewDoc(BAD_CAST "1.0");
    char root_name[]= "root";
    root_element = createRoot(doc,root_name);
    xmlDocSetRootElement(doc, root_element);
    memset(root_name, 0x00, sizeof (root_name));
    memset(Node_name, 0x00, sizeof (Node_name));
    while(j< row_num)
    {
        while(row_tot[j][char_num] != ' ')
        {
            Node_name[char_num]= row_tot[j][char_num];
            char_num++;
        }
        char_num++;
        w = char_num;
        memset(cv, 0x00, sizeof (cv));
        new_node= addChild(root_element, Node_name, NULL);
        while(1)
        {
            if(row_tot[j][char_num] == '(')
            {
                char_num++;
                if(row_tot[j][char_num] == '1')
                {
                    char_num= 0;
                    while (1)
                    {
                        if(row_tot[j][char_num] != '(')
                        {
                            cv[q]= row_tot[j][char_num];
                            q++;
                            char_num++;
                        }
                        else break;
                    }

                }
                else
                {
                    char_num = w;
                    while (1)
                    {
                        if(row_tot[j][char_num] != '\0')
                        {
                            cv[q]= row_tot[j][char_num];
                            q++;
                            char_num++;
                        }
                        else break;
                    }
                    break;
                }
            }
            else char_num++;


        }
        char_num = 0;
        q = 0;
        while(1)
        {
            if(row_tot[j][char_num] == '(')
            {
                char_num++;
                if(row_tot[j][char_num] == '1')
                {
                    char_num--;
                    while (1)
                    {
                        if(row_tot[j][char_num] != ')')
                        {
                            ct[q]= row_tot[j][char_num];
                            q++;
                            char_num++;
                        }
                        else break;
                    }

                }
            }
            else if(row_tot[j][char_num] == '\0') break;
            else char_num++;
        }
        printf("\n\n\ncv is :%s\n\n\n", cv);
        setElementAttribute(new_node, cv, ct);
        char_num = 0;
        q=0;
        j++;
    }
    save_to_file(doc, "output.xml");
    xmlFreeDoc(doc);
    xmlCleanupParser();


    return 0;
}
